#include "../../src/threadpool/thread_pool.h"
#include <iostream>
#include <chrono>
#include <thread>


/*ThreadPool pool(8); → 开 8 个 worker 线程

提交 100 个任务 → lambda 闭包

每个任务 sleep 100ms → 模拟工作负载

pool.stop() → 退出线程池


*/
int main() {
    ThreadPool pool(8);    // 开 8 个线程
    pool.start();

    for (int i = 0; i < 100; ++i) {
        pool.submit([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Task " << i << " running in thread "
                      << std::this_thread::get_id() << std::endl;
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));   // 等一会
    pool.stop();
    return 0;
}
