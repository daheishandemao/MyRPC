#pragma once

#include "health_checker.h"
#include <random>
#include <atomic>
#include <map>
#include <vector>
#include <mutex>

// 负载均衡策略枚举
enum class LoadBalanceStrategy {
    ROUND_ROBIN,//轮询
    RANDOM,//随机
    LEAST_CONNECTIONS//最下连接数
};

// LoadBalancer 实现
class AdvancedLoadBalancer {
public:
    AdvancedLoadBalancer(LoadBalanceStrategy strategy = LoadBalanceStrategy::ROUND_ROBIN)// 构造时选策略，默认轮询
        : strategy_(strategy), rr_counter_(0) {}//rr_counter_ 是原子计数器，做轮询计数用

    // 设置策略  外部调用，随时修改策略
    void setStrategy(LoadBalanceStrategy strategy) {
        strategy_ = strategy;
    }

    // 设置健康检查器 外部注入健康检查器 只选择健康节点
    void setHealthChecker(HealthChecker* checker) {
        health_checker_ = checker;
    }

    // 更新连接数（模拟 LEAST_CONNECTIONS）
    void updateConnectionCount(const ServiceEndpoint& ep, int count) {
        //用于 LEAST_CONNECTIONS 策略时，动态更新当前连接数
        std::lock_guard<std::mutex> lock(mutex_);
        //假设业务可以通过监控上报实时连接
        connection_count_[ep.toString()] = count;
    }

    // 选择一个健康 endpoint
    ServiceEndpoint selectEndpoint(const std::string& service_name) {
        std::vector<ServiceEndpoint> healthy_eps;
        if (health_checker_) {
            // 从 health_checker 查询健康 endpoints
            healthy_eps = health_checker_->getHealthyEndpoints(service_name);
        }

        if (healthy_eps.empty()) {
            std::cerr << "[LoadBalancer] No healthy endpoint for service: " << service_name << std::endl;
            return ServiceEndpoint{"", 0};
        }

        if (strategy_ == LoadBalanceStrategy::ROUND_ROBIN) {
            size_t index = rr_counter_.fetch_add(1) % healthy_eps.size();
            return healthy_eps[index];
        }
        else if (strategy_ == LoadBalanceStrategy::RANDOM) {
            static thread_local std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<size_t> dist(0, healthy_eps.size() - 1);
            size_t index = dist(rng);
            return healthy_eps[index];
        }
        else if (strategy_ == LoadBalanceStrategy::LEAST_CONNECTIONS) {
            std::lock_guard<std::mutex> lock(mutex_);
            ServiceEndpoint best_ep = healthy_eps[0];
            int min_conn = INT32_MAX;
            for (const auto& ep : healthy_eps) {
                auto it = connection_count_.find(ep.toString());
                int conn = (it != connection_count_.end()) ? it->second : 0;
                if (conn < min_conn) {
                    min_conn = conn;
                    best_ep = ep;
                }
            }
            return best_ep;
        }
        else {
            // 默认 fallback
            return healthy_eps[0];
        }
    }

private:
    LoadBalanceStrategy strategy_;
    std::atomic<size_t> rr_counter_;
    HealthChecker* health_checker_ = nullptr;

    std::mutex mutex_;
    std::unordered_map<std::string, int> connection_count_;
};
