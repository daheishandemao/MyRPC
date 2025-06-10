#pragma once

#include <chrono>
#include <mutex>

class CircuitBreaker {
 public:
  enum class State { CLOSED, OPEN, HALF_OPEN };

  CircuitBreaker(int threshold = 5, int success_threshold = 2,
                 int open_timeout_ms = 5000)
      : state_(State::CLOSED),
        failure_count_(0),
        success_count_(0),
        threshold_(threshold),
        success_threshold_(success_threshold),
        open_timeout_(std::chrono::milliseconds(open_timeout_ms)) {}

  // 是否允许请求
  bool allowRequest() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (state_ == State::OPEN) {
      auto now = std::chrono::steady_clock::now();
      if (now - last_open_time_ > open_timeout_) {
        state_ = State::HALF_OPEN;
        success_count_ = 0;
        return true; // 尝试放一个请求
      }
      return false;
    }
    return true;
  }

  void recordSuccess() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (state_ == State::HALF_OPEN) {
      if (++success_count_ >= success_threshold_) {
        state_ = State::CLOSED;
        failure_count_ = 0;
      }
    } else if (state_ == State::CLOSED) {
      failure_count_ = 0; // 正常成功则清空
    }
  }

  void recordFailure() {
    std::lock_guard<std::mutex> lock(mutex_);
    failure_count_++;
    if (state_ == State::HALF_OPEN || (state_ == State::CLOSED && failure_count_ >= threshold_)) {
      state_ = State::OPEN;
      last_open_time_ = std::chrono::steady_clock::now();
    }
  }

  State currentState() const {
    return state_;
  }

 private:
  mutable std::mutex mutex_;
  State state_;
  int failure_count_;
  int success_count_;
  int threshold_;            // 熔断触发失败数
  int success_threshold_;    // 半开状态恢复成功数
  std::chrono::steady_clock::time_point last_open_time_;
  std::chrono::milliseconds open_timeout_;
};
