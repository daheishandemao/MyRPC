#pragma once
#include "myrpcchannel.h"
#include "myrpccontroller.h"
#include "myrpcconfig.h"
#include "zookeeperutil.h"
//myrpc框架的基础类，负责框架的一些初始化操作
class MyrpcApplication//使用单例模式来设计它
{
public:
    //读取网络地址和端口号，以及zk的地址和端口号  config.conf
    static void Init(int argc,char **argv);
    static MyrpcApplication& GetInstance();
    static MyrpcConfig& GetConfig();
private:
    static MyrpcConfig m_config;
    //单例模式设计
    MyrpcApplication(){}
    MyrpcApplication(const MyrpcApplication&)=delete;
    MyrpcApplication(MyrpcApplication&&)=delete;
};