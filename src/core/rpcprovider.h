//基于muduo库实现高并发
#pragma once//防止多次接入文件
#include "google/protobuf/service.h"
#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include <google/protobuf/descriptor.h>
#include <functional>
#include <unordered_map>//用于创建映射表
#include "../log/logger.h"
#include "../zk/zookeeperutil.h"
#include "../trace/trace_context.h"
#include "../limiter/rate_limiter.h"


//框架提供的专门负责发布rpc服务的网络对象类
class RpcProvider
{
public:
    //这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);//因为我们写的是一个框架，所以不能局限于某一个业务，
                    //所以这里的参数要能满足所有的rpc调用的服务，
                    //所以这里的入参应该是google中的protobuf的抽象类service
                    //记得包含响应的头文件

    //启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();
private:
    //组合了TcpServer
    std::unique_ptr<muduo::net::TcpServer> m_tcpserverPtr;//未初始化的智能指针
    //组合EvectLoop
    muduo::net::EventLoop m_eventLoop;

    //限流模块
    RateLimiter rate_limiter_{5, 10}; // 每秒5个请求，最大突发10个

    //定义成员变量用于接收service服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service;//保存服务对象
        std::unordered_map<std::string,const google::protobuf::MethodDescriptor*> m_methodMap;//保存服务方法对象 
    };
    //建立服务名和服务类型信息的映射表
    //存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string,ServiceInfo>m_serviceMap;//保存服务方法对象 

    //新socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    //已建立连接用户的读写事件回调,muduo库如果发现有读写的消息发生就会给上层主动调用这个函数
    void OnMessage(const muduo::net::TcpConnectionPtr&,muduo::net::Buffer*,muduo::Timestamp);
    //Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&,google::protobuf::Message*);
};