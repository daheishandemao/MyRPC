// src/health/health_checker.cc
#include "health_checker.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

HealthChecker::HealthChecker(int interval_ms, int max_fail_count)
    : interval_ms_(interval_ms), max_fail_count_(max_fail_count), running_(false) {}// 默认 not running

HealthChecker::~HealthChecker() {
    stop();//析构时自动停掉线程。
}

void HealthChecker::start() {//启动线程，跑 run() 方法
    running_ = true;
    thread_ = std::thread(&HealthChecker::run, this);
}

void HealthChecker::stop() {//停止线程
    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

void HealthChecker::addEndpoint(const std::string& service_name, const ServiceEndpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);//加 endpoint，线程安全
    service_ep_status_[service_name][ep.toString()] = EndpointInfo{};
}

void HealthChecker::removeEndpoint(const std::string& service_name, const ServiceEndpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);//删 endpoint，线程安全
    auto it = service_ep_status_.find(service_name);
    if (it != service_ep_status_.end()) {
        it->second.erase(ep.toString());
    }
}

void HealthChecker::setProbeFunc(ProbeFunc func) {
    probe_func_ = func;//设置自定义探针逻辑（可换成 ping，http 等）
}

HealthStatus HealthChecker::getEndpointStatus(const std::string& service_name, const ServiceEndpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);//返回单个 endpoint 的当前健康状态。
    auto it = service_ep_status_.find(service_name);
    if (it != service_ep_status_.end()) {
        auto ep_it = it->second.find(ep.toString());
        if (ep_it != it->second.end()) {
            return ep_it->second.status;
        }
    }
    return HealthStatus::UNHEALTHY; // 不存在视为不健康
}

std::vector<ServiceEndpoint> HealthChecker::getHealthyEndpoints(const std::string& service_name) {
    std::vector<ServiceEndpoint> healthy;//返回 service 所有健康 endpoint 列表
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = service_ep_status_.find(service_name);
    if (it != service_ep_status_.end()) {
        for (const auto& ep_pair : it->second) {
            if (ep_pair.second.status == HealthStatus::HEALTHY) {
                std::string ep_str = ep_pair.first;
                size_t idx = ep_str.find(":");
                if (idx != std::string::npos) {
                    ServiceEndpoint ep;
                    ep.ip = ep_str.substr(0, idx);
                    ep.port = static_cast<uint16_t>(std::stoi(ep_str.substr(idx + 1)));
                    healthy.push_back(ep);
                }
            }
        }
    }
    return healthy;
}

void HealthChecker::run() {
    while (running_) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto& svc_pair : service_ep_status_) {
                for (auto& ep_pair : svc_pair.second) {
                    
                    // 解析 endpoint
                    ServiceEndpoint ep;
                    size_t idx = ep_pair.first.find(":");
                    ep.ip = ep_pair.first.substr(0, idx);
                    ep.port = static_cast<uint16_t>(std::stoi(ep_pair.first.substr(idx + 1)));

                    // 调用探针
                    bool ok = probe_func_ ? probe_func_(ep) : false;
                    if (ok) {
                        ep_pair.second.fail_count = 0;
                        ep_pair.second.status = HealthStatus::HEALTHY;
                    } else {
                        ep_pair.second.fail_count++;
                        if (ep_pair.second.fail_count >= max_fail_count_) {
                            ep_pair.second.status = HealthStatus::UNHEALTHY;//失败次数 >= max_fail_count，标记 UNHEALTHY
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms_));
    }
}
