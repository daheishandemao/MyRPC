#include <iostream>
#include "myrpcapplication.h"
#include "friend.pb.h"


int main(int argc,char **argv)
{
    //整个程序启动以后，想使用myrpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    //读取配置文件进行初始化
    MyrpcApplication::Init(argc,argv);

    //演示调用远程发布的rpc方法Login
    fixbug::FriendServiceRpc_Stub stub(new MyrpcChannel());//需要传入一个RpcChannel对象
    //rpc方法的请求参数
    fixbug::GetFriendListRequest request;
    request.set_userid(1000);
    //rpc方法的响应
    fixbug::GetFriendListResponse response;
    //发起rpc方法的调用 同步rpc调用过程 MyrpcChannel::callmethod
    MyrpcController controller;
    stub.GetFriendList(&controller,&request,&response,nullptr );//RpcChannel->RpcChannel ::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送 

    //一次rpc调用完成，读调用的结果
    if(controller.Failed())
    {
        //不成功
        std::cout<<controller.ErrorText()<<std::endl;
    }
    else
    {
        //成功
        if(response.result().errcode()==0)
        {
            std::cout<<"rpc GetFriendList response success！"<<std::endl;
            int size=response.friends_size();
            for(int i=0;i<size;i++)
            {
                std::cout<<"index:"<<(i+1)<<" name:"<<response.friends(i)<<std::endl;
            }
        }
        else
        {
            std::cout<<"rpc GetFriendList response error:"<<response.result().errmsg()<<std::endl;
        }

    }
    

    return 0;
}