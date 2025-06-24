#include "trace_context.h"
#include <random>
#include <iomanip>
#include <unistd.h>


TraceContext::TraceContext() {
  trace_id_ = genTraceId();
}

// 用于外部记录某一阶段的时间戳
void TraceContext::recordEvent(const std::string &event) {
  timestamps_[event] = std::chrono::steady_clock::now();
}

// 生成 trace 报告：trace_id + 各阶段耗时
std::string TraceContext::reportTrace() const {
  std::ostringstream oss;
  oss << "[TRACE] trace_id=" << trace_id_;
  if (timestamps_.size() <= 1) return oss.str();

  auto it = timestamps_.begin();
  auto prev = it++;
  while (it != timestamps_.end()) {
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(prev->second - it->second);
    oss << " | " << prev->first << "→" << it->first << "=" << dur.count() / 1000.0 << "ms";
    prev = it++;
  }
  return oss.str();
}

// 获取 trace_id 的 getter 函数
std::string TraceContext::getTraceId() const {
    return trace_id_;
}

//手动设置 trace_id
void TraceContext::overrideTraceId(const std::string& id) {
  trace_id_ = id;
}

// 设置trace_id的方案：
//trace_id = 时间戳毫秒 + 机器 id (ip hash) + 随机数
std::string TraceContext::genTraceId() {
    using namespace std::chrono;
    auto now = system_clock::now();//system_clock::now() 拿到当前系统时间（1970 年以来的时间点）
    /*time_since_epoch() 返回从 1970 年 1 月 1 日到现在的时间长度。
      duration_cast<milliseconds>(...) 转换成毫秒单位。
      .count() 返回整数值，类型是 long long，表示当前的毫秒数（时间戳）
    */
    auto ts = duration_cast<milliseconds>(now.time_since_epoch()).count();

    char ip_buf[64] = {0};
    gethostname(ip_buf, sizeof(ip_buf));//取出当前机器的主机名，存到 ip_buf 里
    size_t ip_hash = std::hash<std::string>{}(ip_buf);//计算这个主机名的 hash 值，结果是一个 size_t 整数

    //定义了一个线程本地的随机数生成器 gen，类型是 std::mt19937，这是 Mersenne Twister 算法，质量非常高。
    static thread_local std::mt19937 gen(std::random_device{}());//std::random_device{}() 用来给随机引擎做种子（seed）
    /*
    为什么要 thread_local？
    避免多线程竞争，提高性能。
    每个线程有独立的随机数生成器
    */
    static thread_local std::uniform_int_distribution<> dis(0, 99999);

    std::ostringstream oss;
    oss << ts << "-" << (ip_hash % 10000) << "-" << dis(gen);//定义了一个 [0, 99999] 之间的均匀分布 dis，即每次生成一个 0 到 99999 之间的整数
    return oss.str();
}