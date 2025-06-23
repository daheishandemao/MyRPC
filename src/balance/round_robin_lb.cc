// #include "round_robin_lb.h"

// // 构造函数初始化原子计数器为 0
// RoundRobinLB::RoundRobinLB() : idx_(0) {}

// // 从地址列表中轮询挑选一个地址（通过原子递增实现）
// std::string RoundRobinLB::pick(const std::vector<std::string>& addrs) {
//   if (addrs.empty()) return "";
//   int i = idx_.fetch_add(1);  // 原子操作防止多线程冲突
//   return addrs[i % addrs.size()];
// }