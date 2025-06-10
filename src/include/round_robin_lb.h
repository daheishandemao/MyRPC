#pragma once
#include "load_balancer.h"
#include <atomic>

class RoundRobinLB : public LoadBalancer {
 public:
  RoundRobinLB() : idx_(0) {}

  std::string pick(const std::vector<std::string>& addrs) override {
    if (addrs.empty()) return "";
    int i = idx_.fetch_add(1);
    return addrs[i % addrs.size()];
  }

 private:
  std::atomic<int> idx_;
};