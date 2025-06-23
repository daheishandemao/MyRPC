#pragma once
#include <string>
#include <vector>

class LoadBalancer {
 public:
  virtual ~LoadBalancer() = default;
  virtual std::string pick(const std::vector<std::string>& addrs) = 0;
};
