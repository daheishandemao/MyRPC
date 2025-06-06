#include <iostream>
#include <string>
#include "friend.pb.h"
#include "myrpcapplication.h"
#include "rpcprovider.h"
#include <vector>
#include "logger.h"

class FriendService:public fixbug::FriendServiceRpc
{
    public:
    std::vector<std::string>GetFriendList(uint32_t userid)
    {
        std::cout<<"do GetFriendList service! userid:"<<userid<<std::endl;
        std::vector<std::string>vec;
        vec.push_back("gao yang");
        vec.push_back("liu hong");
        vec.push_back("wang shuo");
        return vec;
    }

    //重写基类方法
    void GetFriendList(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendListRequest* request,
                       ::fixbug::GetFriendListResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t userid=request->userid();

        std::vector<std::string>friendList=GetFriendList(userid);
        
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for(std::string& name:friendList)
        {
            std::string *p=response->add_friends();
            *p=name;
        }
        
        done->Run();
    }

};

int main(int argc,char **argv)
{

    LOG_INFO("first log message!\n");
    LOG_ERROR("%s:%s:%d",__FILE__,__FUNCTION__,__LINE__);

    //调用框架的初始化操作 配置日志
    MyrpcApplication::Init(argc,argv);

    //把FriendService对象发布到rpc节点上
    RpcProvider provider;//定义发布服务的对象provider专门在框架上发布服务
    //多方调用，provider要基于muduo库实现高并发
    provider.NotifyService(new FriendService());//FriendService继承自protobuf为我们提供的FriendServiceRpc类，FriendServiceRpc类又是从protobuf的Service继承而来
    //这里可以多次发布服务 

    //启动一个rpc服务发布节点 Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;

}