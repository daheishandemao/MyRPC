#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t thread_num = 8);// 构造：线程池线程数，默认 8
    ~ThreadPool();// 析构：停止线程池

    void start();// 启动线程池
    void stop(); // 停止线程池

    void submit(std::function<void()> task);// 投递任务（lambda）

private:
    void workerLoop();// 每个线程的工作循环

    std::vector<std::thread>workers_;// 工作线程
    std::queue<std::function<void()>> tasks_;// 任务队列
    std::mutex mutex_;// 互斥锁
    std::condition_variable cond_;// 条件变量
    std::atomic<bool> running_;// 标志是否运行
};
