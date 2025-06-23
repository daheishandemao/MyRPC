#include <iostream>
#include "myrpcapplication.h"
#include "user.pb.h"
#include "myrpcchannel.h"

int main(int argc,char **argv)
{
    //整个程序启动以后，想使用myrpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    //读取配置文件进行初始化
    MyrpcApplication::Init(argc,argv);

    start_health_checker();  //启动健康检查
    //演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MyrpcChannel());//需要传入一个RpcChannel对象
    //rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    //rpc方法的响应
    fixbug::LoginResponse response;
    //发起rpc方法的调用 同步rpc调用过程 MyrpcChannel::callmethod
    stub.Login(nullptr,&request,&response,nullptr );//RpcChannel->RpcChannel ::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送 

    //一次rpc调用完成，读调用的结果
    if(response.result().errcode()==0)
    {
        std::cout<<"rpc login response success:"<<response.success()<<std::endl;
    }
    else
    {
        std::cout<<"rpc login response error:"<<response.result().errmsg()<<std::endl;
    }

    //演示调用远程发布的rpc方法Register
    fixbug::RegisterRequest register_request;
    register_request.set_id(2000);
    register_request.set_name("myrpc");
    register_request.set_pwd("666666");

    //定义一个response
    fixbug::RegisterResponse register_response;

    //以同步的方式发起rpc调用请求，等待返回结果
    stub.Register(nullptr,&register_request,&register_response,nullptr);
    //一次rpc调用完成，读调用的结果
    if(register_response.result().errcode()==0)
    {
        std::cout<<"rpc register response success:"<<register_response.success()<<std::endl;
    }
    else
    {
        std::cout<<"rpc register response error:"<<register_response.result().errmsg()<<std::endl;
    }

    return 0;
}