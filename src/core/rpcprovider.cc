#include "rpcprovider.h"
#include "myrpcapplication.h"
#include "../codec/rpcheader.pb.h"
#include "../health/health_checker.h"

static HealthChecker health_checker;

void start_health_checker() {
    health_checker.setProbeFunc([](const ServiceEndpoint& ep) -> bool {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(ep.port);
        inet_pton(AF_INET, ep.ip.c_str(), &addr.sin_addr);

        int ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
        close(sock);
        return (ret == 0);
    });

    health_checker.addEndpoint("UserService", {"127.0.0.1", 8000});
    health_checker.addEndpoint("FriendService", {"127.0.0.1", 8000});
    health_checker.start();
}

/*
service_name=>service描述
                =>service*记录服务对象
                method_name=>method方法对象

json存储键值对，基于文本存储
protobuf基于二进制存储，存储效率更高，占用带宽更少，同样带宽的数据量更大。紧密存储，不包括除数据外其他信息
        不仅提供了类型的序列化和反序列化，还可以从抽象层面描述服务对象和服务方法
*/
//因为我们写的是一个框架，所以不能局限于某一个业务，所以这里的参数要能满足所有的rpc调用的服务
//所以这里的入参应该是google中的protobuf的抽象类service,记得包含响应的头文件
void RpcProvider::NotifyService(google::protobuf::Service *service)//服务不一定只给UserService提供，所有这里的框架使用的是基类Service指针
{
    //创建接收服务类型的结构体
    ServiceInfo service_info;

    //获取了服务对象的描述信息
    const google::protobuf::ServiceDescriptor *pserviceDesc=service->GetDescriptor();
    //从服务描述里面得到服务的信息
    //获取服务的名字
    std::string service_name= pserviceDesc->name();
    //获取服务对象service的方法的数量
    int methodCnt=pserviceDesc->method_count();

    //打印信息
    std::cout<<"service_name:"<<service_name<<std::endl;
    LOG_INFO("service_name:%s",service_name.c_str());

    for(int i=0;i<methodCnt;i++)
    {
        //获取了服务对象指定下标的服务方法的描述（抽象描述）
        const google::protobuf::MethodDescriptor* pmethodDesc=pserviceDesc->method(i);
        std::string method_name=pmethodDesc->name();
        service_info.m_methodMap.insert({method_name,pmethodDesc});

        LOG_INFO("method_name:%s",method_name.c_str());
        std::cout<<"method_name:"<<method_name<<std::endl;
    }
    service_info.m_service=service;
    m_serviceMap.insert({service_name,service_info});
}
                    
                    

//启动rpc服务节点，开始提供rpc远程网络调用服务
void RpcProvider::Run()
{

    //读取ip地址和端口号 配置文件rpcserver的信息
    std::string ip= MyrpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MyrpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress address(ip,port);
    //创建TcpServer对象
    muduo::net::TcpServer server(&m_eventLoop,address,"RpcProvider");
    //绑定连接回调和消息读写回调方法   分离了网络代码和业务代码
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection,this,std::placeholders::_1));
    //
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

    //设置mudo库的线程数量
    server.setThreadNum(4);//一个IO线程三个工作线程的Reactor模式

    //把当前rpc节点上要发布的服务全部注册到zk上，让rpc client可以从zk上发现服务
    //session timeout 30s   zkclient 的网络I/O线程 以1/3*timeout事件发送ping消息
    ZkClient zkCli;
    zkCli.Start();
    //service_name为永久性节点     method_name为临时性节点
    for(auto& sp:m_serviceMap)
    {
        //
        std::string service_path="/"+sp.first;
        zkCli.Create(service_path.c_str(),nullptr,0);
        for(auto &mp:sp.second.m_methodMap)
        {
            //
            std::string method_path=service_path+"/"+mp.first;
            char method_path_data[128]={0};
            sprintf(method_path_data,"%s:%d",ip.c_str(),port);
            //ZOO_EPHEMERAL表示znode是一个临时性节点
            zkCli.Create(method_path.c_str(),method_path_data,strlen(method_path_data),ZOO_EPHEMERAL);
        }
    }


    //启动网络服务
    std::cout<<"RpcProvider start service at ip:"<<ip<<"port:"<<port<<std::endl;
    server.start();
    m_eventLoop.loop();//以阻塞的方式等待远程的连接
}

//新socket连接回调      普通方法，实例方法需要绑定一个当前RPC对象
void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr&conn)
{
    //RPC请求是短链接请求， 服务端响应完就会断开连接
    if(!conn->connected())
    {
        //和rpc client的连接断开=>关闭文件描述符
        conn->shutdown();//对应socket就是调用close
        
    }
}

/*
①在框架内部，RpcProvider和RpcConsumer协商好之间通信用的protobuf数据类型
service_name method_name args
②在框架中定义proto的message类型，进行数据头的序列化和反序列化
③因为要知道服务名和方法名的长度所以要设置header_size
④要考虑tcp粘包问题所以要定义参数的字符串长度，所以在header_size里面还要记录args_size
⑤所以总体结构为header_size（4个字节，表示除了方法参数之前的所有的名字）+header_str(service_name method_name args_size)+args_str

*/
//已建立连接用户的读写事件回调,muduo库如果发现有读写的消息发生就会给上层主动调用这个函数
//如果远端有一个rpc服务的调用请求，那么OnMessage方法就会响应
void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr&conn,muduo::net::Buffer *buffer,muduo::Timestamp)
{
    //顶部限流判断
    if (!rate_limiter_.allow()) {
        std::cout << "[RateLimiter] Request dropped due to QPS limit." << std::endl;
        return;
    }

    //网络上接收的远程rpc调用请求的字节流
    //包含方法名、参数
    std::string recv_buf=buffer->retrieveAllAsString();
     
    //从字符流中读取前4个字节的内容
    uint32_t header_size=0;
    recv_buf.copy((char*)&header_size,4,0);

    //根据header_size读取数据头的原始字符流
    std::string rpc_header_str=recv_buf.substr(4,header_size);
    //然后反序列化数据，得到rpc请求的详细信息
    myrpc::RpcHeader rpcHeader;
    std::string service_name;
    std::string method_name;
    uint32_t args_size;
    std::string trace_id;
    if(rpcHeader.ParseFromString(rpc_header_str))
    {
        //数据头反序列化成功
        service_name=rpcHeader.service_name();
        method_name=rpcHeader.method_name();
        args_size=rpcHeader.args_size();
        trace_id=rpcHeader.trace_id();
    }
    else
    {
        //数据头反序列化失败，需要打印日志
        std::cout<<"rpc_header_str:"<<rpc_header_str<<"parse error!"<<std::endl;
        return ;
    }

    TraceContext trace;
    trace.overrideTraceId(rpcHeader.trace_id()); // 新增函数：手动设置 trace_id
    trace.recordEvent("recv_start");
    //获取rpc方法参数的字符流数据
    std::string args_str=recv_buf.substr(4+header_size,args_size);

    //打印调试信息
    std::cout<<"==========rpcprovider=============="<<std::endl;
    std::cout<<"header_size:"<<header_size<<std::endl;
    std::cout<<"rpc_header_str:"<<rpc_header_str<<std::endl;
    std::cout<<"service_name:"<<service_name<<std::endl;
    std::cout<<"method_name:"<<method_name<<std::endl;
    std::cout<<"args_str:"<<args_str<<std::endl;
    std::cout<<"=================================="<<std::endl;

    //获取service对象和method对象
    auto it=m_serviceMap.find(service_name);
    if(it==m_serviceMap.end())
    {
        //这个节点没有该服务名
        std::cout<<service_name<<"is not exist!"<<std::endl;
        return ;
    }

    //根据服务名寻找方法名，判断方法名是否存在
    auto mit=it->second.m_methodMap.find(method_name);
    if(mit==it->second.m_methodMap.end())
    {
        //这个服务没有该方法名
        std::cout<<service_name<<":"<<method_name<<"is not exist!"<<std::endl;
        return ;
    }

    //获取service服务对象   UserService
    google::protobuf::Service *service=it->second.m_service;
    //获取method方法对象  Login
    const google::protobuf::MethodDescriptor* method=mit->second;

    //生成rpc方法调用的请求request和响应response参数
    google::protobuf::Message *request=service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str))//反序列化了
    {
        std::cout<<"request parse error, content:"<<args_str<<std::endl;
        return;
    }

    google::protobuf::Message *response=service->GetResponsePrototype(method).New();

    //给下面的method方法的调用，绑定一个Closure的回调函数
    google::protobuf::Closure *done=google::protobuf::NewCallback<RpcProvider,const muduo::net::TcpConnectionPtr&,google::protobuf::Message*>(this, &RpcProvider::SendRpcResponse,conn,response);


    trace.recordEvent("handler_begin");
    //在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
    //相当于UserService().Login(controller,request,response,done)
    service->CallMethod(method,nullptr,request,response,done);//done是Closuer抽象类的回调函数
    trace.recordEvent("handler_end");
    trace.recordEvent("send");
    std::cout << trace.reportTrace() << std::endl;
}


    //Closure的回调操作，用于序列化rpc的响应和网络发送。普通方法的调用需要绑定对象
    void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr&conn,google::protobuf::Message* response)
    {

        
        std::string response_str;
        //response_str进行序列化
        if(response->SerializeToString(&response_str))
        {
            //response_str序列化成功后，通过网络把rpc方法执行的结果发送回给rpc的调用方
            conn->send(response_str);
        }
        else
        {
            //本地打印错误日志 
            std::cout<<"serialize response_str error!"<<std::endl;
        }
        conn->shutdown();//模拟http的短链接服务，由rpcprovider主动断开连接
    }