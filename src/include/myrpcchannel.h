#pragma once
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "circuitbreaker.h"
#include "trace_context.h"
#include "round_robin_lb.h"
#include "fallback.h"

class MyrpcChannel:public google::protobuf::RpcChannel
{
    public:
    //所有通过stub代理对象调用的rpc方法，都走到这里了，统一做rpc方法调用的数据序列化和网络发送
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                          google::protobuf::Message* response, google::protobuf::Closure* done);
    void setFallback(FallbackFunc f) { fallback_ = f; }
    private:
    CircuitBreaker circuit_breaker_;
    FallbackFunc fallback_;
};