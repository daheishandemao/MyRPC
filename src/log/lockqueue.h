#pragma once
#include <queue>
#include <thread>
#include <mutex>//对应linux环境中的pthread_mutex_t 互斥锁
#include <condition_variable>//对应pthread_condition_t 条件变量


//异步写日志的日志队列
template<typename T>
class LockQueue
{
private:
    std::queue<T>m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condvariable;
public:
    //入队从对尾入，框架的日志线程调用
    //多个worker线程都会写日志queue
    void Push(const T &data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_condvariable.notify_one();
    }

    //系统的写日志线程调用
    //一个线程读日志queue，写日志文件
    T Pop()
    {
        std::unique_lock<std::mutex>lock(m_mutex);
        while(m_queue.empty())
        {   
            //日志队列为空，线程进入wait状态
            m_condvariable.wait(lock);
        }

        T data =m_queue.front();
        m_queue.pop();
        return data;
    }
};
