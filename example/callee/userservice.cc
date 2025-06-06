#include <iostream>
#include <string>
#include "user.pb.h"
#include "myrpcapplication.h"
#include "rpcprovider.h"
/*
UserService原本是一个本地服务，提供了两个进程内的本地方法。Login和GetFriendLists
*/
class UserService : public fixbug::UserServiceRpc//①注意命名空间是使用 fixbug②使用在rpc服务提供端
{
    public:
    bool Login(std::string name,std::string pwd)
    {
        std::cout<<"doing local service: Login"<<std::endl;
        std::cout<<"name:"<<name<<" pwd:"<<pwd<<std::endl;
        return true;
    }

    bool Register(uint32_t id,std::string name,std::string pwd)
    {
        std::cout<<"doing local service: Register"<<std::endl;
        std::cout<<"id:"<<id<<"name:"<<name<<"pwd:"<<pwd<<std::endl;
        return true;
    }

    /*
    重写基类UserServiceRpc的虚函数 下面这些方法是直接调用框架的
    1.caller  ===> Login(LoginRequest) ===> muduo ===>  callee
    2.callee  ===> Login(LoginRequest) ===> 交到重写的Login方法上了
    */
    void Login(::google::protobuf::RpcController* controller,
        const ::fixbug::LoginRequest* request,
        ::fixbug::LoginResponse* response,
        ::google::protobuf::Closure* done)
    {
        //框架给业务上报了请求参数LoginRequest， 应用获取相应数据做本地业务
        std::string name=request->name();
        std::string pwd=request->pwd();
        //对name和pwd做有效性检查
        //然后开始根据数据做本地业务
        bool login_result=Login(name,pwd);

        //写入响应 包括错误码、错误消息、返回值
        fixbug::ResultCode *code=response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);
        //如果login_result有异常就要try爆出来

        //执行回调操作  执行响应对象数据的序列化和网络发送（由框架完成）
        done->Run();
    }

    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t id=request->id();
        std::string name=request->name();
        std::string pwd=request->pwd();

        bool ret =Register(id,name,pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        //执行回调  把调好的response进行序列化并通过网络发回客户端
        done->Run();
    }
};

int main(int argc,char **argv)
{
    //调用框架的初始化操作 配置日志
    MyrpcApplication::Init(argc,argv);

    //把UserService对象发布到rpc节点上
    RpcProvider provider;//定义发布服务的对象provider专门在框架上发布服务
    //多方调用，provider要基于muduo库实现高并发
    provider.NotifyService(new UserService());//UserService继承自protobuf为我们提供的UserServiceRpc类，UserServiceRpc类又是从protobuf的Service继承而来
    //这里可以多次发布服务 

    //启动一个rpc服务发布节点 Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;

}