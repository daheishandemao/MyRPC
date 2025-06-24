#include "thread_pool.h"

ThreadPool::ThreadPool(size_t thread_num) : running_(false) {
    workers_.reserve(thread_num);// 预留空间，不实际创建线程
}

ThreadPool::~ThreadPool() {
    stop();// 析构时安全停止线程池
}

void ThreadPool::start() {
    running_ = true;
    for (size_t i = 0; i < workers_.capacity(); ++i) {
        workers_.emplace_back(&ThreadPool::workerLoop, this);// 每个线程执行 workerLoop
    }
}

void ThreadPool::stop() {
    running_ = false;// 停止标志
    cond_.notify_all();// 唤醒所有等待线程
    for (auto& t : workers_) {
        if (t.joinable()) {
            t.join();// 等待线程退出
        }
    }
}

void ThreadPool::submit(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.emplace(std::move(task));// 线程安全地把任务压入队列
    }
    cond_.notify_one();// 唤醒一个 worker 执行
}

void ThreadPool::workerLoop() {
    while (running_) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(mutex_);
            cond_.wait(lock, [this] {
                return !running_ || !tasks_.empty();// 条件：停止 or 有任务
            });

            if (!running_ && tasks_.empty()) {
                return;// 退出线程
            }

            task = std::move(tasks_.front());
            tasks_.pop();// 取出任务
        }

        task();  // 执行任务
    }
}
