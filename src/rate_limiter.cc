#include "rate_limiter.h"
#include <algorithm>

RateLimiter::RateLimiter(int rate, int burst)
    : capacity_(burst), tokens_(burst), refill_rate_(rate),
      last_refill_time_(std::chrono::steady_clock::now()) {}

bool RateLimiter::allow() {
  std::lock_guard<std::mutex> lock(mutex_);//加锁保证线程安全（多线程时避免同时改 tokens_）。
  auto now = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = now - last_refill_time_;//计算“当前时间”和“上次补令牌时间”之间差了多少秒

  // 根据时间增长令牌
  tokens_ = std::min(capacity_, tokens_ + elapsed.count() * refill_rate_);
  /*
  elapsed.count() 是“秒数”，例如 0.4 秒；
  refill_rate_ 是每秒生成几个令牌，例如 5
  所以 elapsed.count() * refill_rate_ 就是这段时间内应该补多少令牌。
  */
  last_refill_time_ = now;//更新“上次补令牌时间”为现在，为下次计算做准备。

  if (tokens_ >= 1.0) {
    tokens_ -= 1.0;
    return true;//如果当前桶里还有令牌，就消耗一个，返回 true，表示“放行”。
  } else {
    return false;//如果没令牌了，返回 false，请求被限流。
  }
}