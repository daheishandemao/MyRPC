#pragma once
#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>
#include <vector>

//封装的zk客户端
class ZkClient
{
    public:
    ZkClient();
    ~ZkClient();
    //zkclient启动连接zkserver
    void Start();
    //在zkserver上根据指定的path创建znode节点
    void Create(const char *path,const char *data,int datalen,int state=0);
    //根据参数指定的znode节点路径，或者znode节点的值
    std::string GetData(const char* path);
    std::vector<std::string> GetChildren(const char *path);

    private:
    //zk的客户端句柄，通过句柄操控server
    zhandle_t *m_zhandle;
};