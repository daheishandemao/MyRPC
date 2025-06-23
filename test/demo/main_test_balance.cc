#include "balance/advanced_load_balancer.h"
#include "monitor/health_checker.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // 1️⃣ 初始化健康检查模块
    HealthChecker checker(1000);  // 1秒检查一次
    checker.setProbeFunc([](const ServiceEndpoint& ep) -> bool {
        // 简单模拟健康检查逻辑
        if (ep.ip == "127.0.0.2") {
            return false; // 故意模拟 127.0.0.2 不健康
        }
        return true;
    });

    checker.addEndpoint("UserService", {"127.0.0.1", 8000});
    checker.addEndpoint("UserService", {"127.0.0.2", 8001});
    checker.addEndpoint("UserService", {"127.0.0.3", 8002});
    checker.start();

    // 2️⃣ 初始化负载均衡模块
    AdvancedLoadBalancer lb(LoadBalanceStrategy::ROUND_ROBIN);
    lb.setHealthChecker(&checker);

    std::cout << "=== ROUND ROBIN ===" << std::endl;
    for (int i = 0; i < 10; ++i) {
        ServiceEndpoint ep = lb.selectEndpoint("UserService");
        std::cout << "[RR] Selected: " << ep.toString() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "=== RANDOM ===" << std::endl;
    lb.setStrategy(LoadBalanceStrategy::RANDOM);
    for (int i = 0; i < 10; ++i) {
        ServiceEndpoint ep = lb.selectEndpoint("UserService");
        std::cout << "[Random] Selected: " << ep.toString() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "=== LEAST CONNECTIONS ===" << std::endl;
    lb.setStrategy(LoadBalanceStrategy::LEAST_CONNECTIONS);
    // 模拟连接数
    lb.updateConnectionCount({"127.0.0.1", 8000}, 5);
    lb.updateConnectionCount({"127.0.0.3", 8002}, 2);  // 最小连接数

    for (int i = 0; i < 10; ++i) {
        ServiceEndpoint ep = lb.selectEndpoint("UserService");
        std::cout << "[LC] Selected: " << ep.toString() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    checker.stop();

    return 0;
}
