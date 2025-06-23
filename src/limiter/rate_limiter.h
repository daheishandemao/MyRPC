#pragma once

#include <chrono>
#include <mutex>

class RateLimiter {
 public:
  RateLimiter(int rate, int burst);
  bool allow();

 private:
  double capacity_;             // 最大桶容量
  double tokens_;            // 当前令牌数
  double refill_rate_;       // 每秒补充的令牌数
  std::chrono::steady_clock::time_point last_refill_time_;
  std::mutex mutex_;
};
