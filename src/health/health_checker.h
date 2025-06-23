#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include <chrono>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h> 

// 枚举健康状态：健康、不健康。
enum class HealthStatus {
    HEALTHY,
    UNHEALTHY
};

// endpoint 信息
struct ServiceEndpoint {
    std::string ip;
    uint16_t port;//定义一个 服务节点，包含 IP 和 port
    std::string toString() const { return ip + ":" + std::to_string(port); }
};

class HealthChecker {
public:
    using ProbeFunc = std::function<bool(const ServiceEndpoint&)>;//定义探针函数类型：传入 ServiceEndpoint，返回 bool：是否健康

    HealthChecker(int interval_ms = 3000, int max_fail_count = 3);
    ~HealthChecker();

    void start();
    void stop();

    void addEndpoint(const std::string& service_name, const ServiceEndpoint& ep);
    void removeEndpoint(const std::string& service_name, const ServiceEndpoint& ep);

    //设置自定义探针函数（默认 TCP ping）
    void setProbeFunc(ProbeFunc func);

    // 查询 endpoint 当前状态 
    HealthStatus getEndpointStatus(const std::string& service_name, const ServiceEndpoint& ep);
    // 获取 service 所有健康的 endpoint
    std::vector<ServiceEndpoint> getHealthyEndpoints(const std::string& service_name);

private:
    void run();//线程循环检查

    std::atomic<bool> running_;
    std::thread thread_;

    int interval_ms_;//interval_ms: 多久检查一次（默认 3 秒）
    int max_fail_count_;//max_fail_count: 连续失败多少次判为不健康

    ProbeFunc probe_func_;//探针

    struct EndpointInfo {//存每个 endpoint 的信息：连续失败多少次、当前是否健康
        HealthStatus status = HealthStatus::HEALTHY;
        int fail_count = 0;// 连续失败次数
    };

    std::mutex mutex_;
    std::unordered_map<std::string, std::unordered_map<std::string, EndpointInfo>> service_ep_status_;//存储 服务名 -> endpoint -> 状态
};
