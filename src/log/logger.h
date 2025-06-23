#pragma once
#include "lockqueue.h"
#include <string>

//定义宏
//可变参 参数列表填到这个缓冲区里面了
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \

#define LOG_ERR(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \


enum LogLevel
{
    INFO,//普通信息
    ERROR,//错误信息
};

//Myrpc框架提供的日志系统
class Logger
//单例 把拷贝构造函数和移动构造函数删除但是保留构造函数
{
public:
    //获取日志的单例
    static Logger& GetInstance();
    //设置日志级别
    void SetLogLevel(LogLevel level);
    //写日志
    void Log(std::string msg);
private:
    int m_loglevel;//记录日志级别
    LockQueue<std::string> m_lckQue;//日志缓冲队列

    Logger();
    Logger(const Logger&)=delete;
    Logger(Logger&&)=delete;

};

