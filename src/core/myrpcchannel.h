#pragma once
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "../limiter/circuitbreaker.h"
#include "../trace/trace_context.h"
#include "../balance/round_robin_lb.h"
#include "../limiter/fallback.h"
#include "../zk/zookeeperutil.h"
#include "../health/health_checker.h"
#include "../balance/advanced_load_balancer.h"
#include "../threadpool/thread_pool.h"

class MyrpcChannel:public google::protobuf::RpcChannel
{
    public:
    //所有通过stub代理对象调用的rpc方法，都走到这里了，统一做rpc方法调用的数据序列化和网络发送
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                          google::protobuf::Message* response, google::protobuf::Closure* done);
    void setFallback(FallbackFunc f) { fallback_ = f; }
    // void MyrpcChannel(zk_client_(std::make_shared<ZkClient>()),
    //   load_balancer_(std::make_shared<AdvancedLoadBalancer>(AdvancedLoadBalancer::Type::ROUND_ROBIN)),
    //   health_checker_(std::make_shared<HealthChecker>())){}
    private:
    
    std::shared_ptr<ZkClient> zk_client_;

    //熔断器
    CircuitBreaker circuit_breaker_;
    //回调降级
    FallbackFunc fallback_;
    //健康检查
    std::shared_ptr<HealthChecker> health_checker_;
    //负载均衡
    std::shared_ptr<AdvancedLoadBalancer> load_balancer_;

};