#include "health_checker.h"
#include <iostream>
#include <thread>

int main() {
    HealthChecker checker(2000, 2);

    checker.setProbeFunc([](const ServiceEndpoint& ep) -> bool {
        std::cout << "Probing " << ep.toString() << std::endl;
        // 模拟失败
        return false;
    });

    checker.addEndpoint("TestService", {"127.0.0.1", 9999});
    checker.start();

    for (int i = 0; i < 10; ++i) {
        auto status = checker.getEndpointStatus("TestService", {"127.0.0.1", 9999});
        std::cout << "Health status: "
                  << (status == HealthStatus::HEALTHY ? "HEALTHY" : "UNHEALTHY")
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    checker.stop();
    return 0;
}
