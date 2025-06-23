#pragma once

#include <string>
#include <unordered_map>
#include <chrono>
#include <sstream>

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
};