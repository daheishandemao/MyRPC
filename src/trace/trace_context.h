#pragma once

#include <string>
#include <unordered_map>
#include <chrono>
#include <sstream>


// 设置trace_id的方案：
//trace_id = 时间戳毫秒 + 机器 id (ip hash) + 随机数

class TraceContext {
 public:
  TraceContext();

  void recordEvent(const std::string &event);
  std::string reportTrace() const;
  std::string getTraceId() const;
  void overrideTraceId(const std::string& id);

 private:
  std::string trace_id_;
  std::unordered_map<std::string, std::chrono::steady_clock::time_point> timestamps_;

  //生成trace_Id，更符合工业界
  std::string genTraceId();


};