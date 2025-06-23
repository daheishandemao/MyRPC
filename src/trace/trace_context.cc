#include "trace_context.h"
#include <random>
#include <iomanip>

TraceContext::TraceContext() {
  std::stringstream ss;
  static std::random_device rd;
  static std::mt19937 gen(rd());// 伪随机数生成器
  static std::uniform_int_distribution<> dis(0, 15);// 生成0-15的整数
  for (int i = 0; i < 16; ++i) {// 生成16位十六进制的trace_id
    ss << std::hex << dis(gen);
  }
  trace_id_ = ss.str();
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