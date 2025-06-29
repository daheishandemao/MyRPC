#include "myrpcchannel.h"
#include <string>
#include "rpcheader.pb.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "myrpcapplication.h"

FallbackFunc fallback_ = nullptr;   // 声明一个可选的降级处理函数
RoundRobinLB round_robin_lb;       // 创建轮询负载均衡器

/*
约定好的数据格式：
header_size+service_name method_name args_size+args_str
*/
//所有通过stub代理对象调用的rpc方法，都走到这里了，统一做rpc方法调用的数据序列化和网络发送
void MyrpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                          google::protobuf::Message* response, google::protobuf::Closure* done)
{
    const google::protobuf::ServiceDescriptor* sd=method->service();
    std::string service_name=sd->name();//service_name
    std::string method_name=method->name();//metod_name

    

    //获取参数的序列化字符串长度 args_size
    uint32_t args_size=0;
    std::string args_str;
    if(request->SerializeToString(&args_str))
    {
        args_size=args_str.size();

    }
    else
    {
        std::cout<<"serialize request error!"<<std::endl;
        controller->SetFailed("serialize request error!");
        return;
    }

    TraceContext trace;
    trace.recordEvent("encode_start");

    //定义rpc的请求header
    myrpc::RpcHeader rpcHeader;
    rpcHeader.set_service_name(service_name);
    rpcHeader.set_method_name(method_name);
    rpcHeader.set_trace_id(trace.getTraceId());  // 新增行
    rpcHeader.set_args_size(args_size);

    uint32_t header_size=0;
    std::string rpc_header_str;
    if(rpcHeader.SerializeToString(&rpc_header_str))
    {
        header_size=rpc_header_str.size();
    }
    else
    {
        std::cout<<"serialize rpc header error!"<<std::endl;
        controller->SetFailed("serialize rpc header error!");
        return;
    }

    //组织待发送的rpc请求的字符串
    std::string send_rpc_str;
    //放header_size;
    send_rpc_str.insert(0,std::string((char*)&header_size,4));
    //放header_str   rpcHeader
    send_rpc_str+=rpc_header_str;
    //放args_str
    send_rpc_str+=args_str;

    //打印调试信息
    std::cout<<"==============myrpcchannel===================="<<std::endl;
    std::cout<<"header_size:"<<header_size<<std::endl;
    std::cout<<"rpc_header_str:"<<rpc_header_str<<std::endl;
    std::cout<<"service_name:"<<service_name<<std::endl;
    std::cout<<"method_name:"<<method_name<<std::endl;
    std::cout<<"args_str:"<<args_str<<std::endl;
    std::cout<<"=================================="<<std::endl;

    //使用tcp编程完成rpc方法的远程调用
    int clientfd=socket(AF_INET, SOCK_STREAM,0);//也可以创建动态指针
    if(-1==clientfd)
    {
        std::cout<<"create socket error! errno:"<<errno<<std::endl;
        char errtxt[512]={0};
        sprintf(errtxt,"create socket error! errno:%d",errno);
        controller->SetFailed(errtxt);
        exit(EXIT_FAILURE);
    }

    //读取ip地址和端口号 配置文件rpcserver的信息
    // std::string ip= MyrpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    // uint16_t port = atoi(MyrpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());

    //rpc调用方想调用service_name的method_name服务，需要查询zk上该服务所在的host信息
    ZkClient zkCli;
    zkCli.Start();
    std::string method_path="/"+service_name+"/"+method_name;
    //只查询一个
    std::string host_data=zkCli.GetData(method_path.c_str());
    if(host_data=="")
    {
        controller->SetFailed(method_path+"is not exit");
        return;
    }
    int idx=host_data.find(":");
    if(idx==-1)
    {
        controller->SetFailed(method_path+"address is invalid!");
        return;
    }
    std::string ip=host_data.substr(0,idx);
    uint16_t port=atoi(host_data.substr(idx+1,host_data.size()-idx).c_str());
    //负载均衡
    // std::vector<std::string> providers = zkCli.GetChildren(method_path.c_str());  // 返回一批 provider 节点
    // std::string peer = round_robin_lb.pick(providers);
    // if (peer.empty()) {
    //     controller->SetFailed("no available provider");
    //     return;
    // }
    // int idx = peer.find(":");
    // std::string ip = peer.substr(0, idx);
    // uint16_t port = std::stoi(peer.substr(idx+1));




    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;//地址家族协议
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip.c_str());

    // === 熔断器预判 ===
    if (!circuit_breaker_.allowRequest()) {
        // LOG_ERROR("Circuit breaker open: RPC request blocked");
        std::cout<<"Circuit breaker open: RPC request blocked"<<std::endl;
        if (fallback_) {
            fallback_(request, response);
            controller->SetFailed("circuit open, fallback used");
        } else {
            controller->SetFailed("circuit open, no fallback");
        }
        return;
    }

    trace.recordEvent("connect_start");
    //连接rpc服务节点
    if(-1==connect(clientfd,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        std::cout<<"connect socket error! errno:"<<errno<<std::endl;
        close(clientfd);//失败关闭文件描述符
        char errtxt[512]={0};
        sprintf(errtxt,"connect socket error! errno:%d",errno);
        circuit_breaker_.recordFailure();
        controller->SetFailed(errtxt);
        // exit(EXIT_FAILURE);
    }

    trace.recordEvent("send_done");
    //通过send先发起rpc请求
    if(-1==send(clientfd,send_rpc_str.c_str(),send_rpc_str.size(),0))
    {
        std::cout<<"send error! errno:"<<errno<<std::endl;
        char errtxt[512]={0};
        sprintf(errtxt,"send error! errno:%d",errno);
        controller->SetFailed(errtxt);
        circuit_breaker_.recordFailure();
        close(clientfd);//失败关闭文件描述符
        return;
    }

    //接收rpc请求的响应值
    char recv_buf[1024]={0};//定义了一k的缓冲区
    int recv_size=0;
    trace.recordEvent("recv_done");
    if(-1==(recv_size=recv(clientfd,recv_buf,1024,0)))
    {
        std::cout<<"recv error! errno:"<<errno<<std::endl;
        char errtxt[512]={0};
        sprintf(errtxt,"recv error! errno:%d",errno);
        controller->SetFailed(errtxt);
        circuit_breaker_.recordFailure();
        close(clientfd);//失败关闭文件描述符
        return;
    }else{
        circuit_breaker_.recordSuccess();
    }
    std::cout << trace.reportTrace() << std::endl;

    std::string response_str(recv_buf,0,recv_size);//recv_buf中遇到\0后面的数据就存不下来了
    //然后进行反序列化rpc调用的响应数据
    // if(!response->ParseFromString(response_str))
    if(!response->ParseFromArray(recv_buf,recv_size))
    {
        std::cout<<"parse error！recv_buf："<<recv_buf<<std::endl;
        char errtxt[512]={0};
        sprintf(errtxt, "parse error! response_str:%s", recv_buf);
        circuit_breaker_.recordFailure();
        close(clientfd);//失败关闭文件描述符
        return;
    }
    close(clientfd);
}