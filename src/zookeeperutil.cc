#include "zookeeperutil.h"
#include "myrpcapplication.h"

//全局的观察器  zkserver给zkclient的通知
void global_watcher(zhandle_t *zh,int type,int state,const char *path, void *watchercTX)
{
    if(type==ZOO_SESSION_EVENT)//回调的消息类型 和会话相关的消息类型
    {
        if(state==ZOO_CONNECTED_STATE) //zkserver给zkclient连接成功
        {
            sem_t *sem=(sem_t*)zoo_get_context(zh);
            sem_post(sem); 
        }
    }
}

ZkClient::ZkClient():m_zhandle(nullptr)
{
}
ZkClient::~ZkClient()
{
    if(m_zhandle!=nullptr)
    {
        zookeeper_close(m_zhandle);//关闭句柄释放资源
    }
}

//连接zkeeper
void ZkClient::Start()
{
    std::string host=MyrpcApplication::GetInstance().GetConfig().Load("zookeeperip");
    std::string port=MyrpcApplication::GetInstance().GetConfig().Load("zookeeperport");
    std::string connstr=host+":"+port;

    /*
    zookeeper_mt:多线程版本
    zookeeper的API客户端提供了三个线程
    API调用线程
    网络I/O线程  pthread_create poll
    watcher回调线程  pthread_create
    */
   m_zhandle=zookeeper_init(connstr.c_str(),global_watcher,30000,nullptr,nullptr,0);
   if(nullptr==m_zhandle)
   {
        std::cout<<"zookeeper_init error!"<<std::endl;
        exit(EXIT_FAILURE);
   }

   //信号量
   sem_t sem;
   sem_init(&sem,0,0);
   //上下文给句柄传参数，添加额外信息
   zoo_set_context(m_zhandle,&sem);

   //阻塞在这里
   sem_wait(&sem);
   std::cout<<"zookeeper_init success!"<<std::endl;
}

//state是状态：永久/临时
void ZkClient::Create(const char *path,const char *data,int datalen,int state)
{
    char path_buffer[128];
    int bufferlen=sizeof(path_buffer);
    int flag;
    //先判断path表示的znode节点是否存在，如果存在，就不再重复创建了
    flag=zoo_exists(m_zhandle,path,0,nullptr);
    if(ZNONODE==flag)//表示path的znode节点不存在
    {
        //创建指定path的znode节点了
        //默认状态是永久，empthore为1的话就是临时
        flag=zoo_create(m_zhandle,path,data,datalen,&ZOO_OPEN_ACL_UNSAFE,state,path_buffer,bufferlen);
        if(flag==ZOK)
        {
            std::cout<<"znode create success... path:"<<path<<std::endl;
        }
        else{
            std::cout<<"flag"<<flag<<std::endl;
            std::cout<<"znode create error... path:"<<path<<std::endl;
            exit(EXIT_FAILURE); 
        }
    }
}

//根据指定path获取znode节点的值
std::string ZkClient::GetData(const char *path)
{
    char buffer[64];
    int bufferlen=sizeof(buffer);
    int flag =zoo_get(m_zhandle,path,0,buffer,&bufferlen,nullptr);
    if(flag!=ZOK)
    {
        std::cout<<"get znode error... path:"<<path<<std::endl;
        return "";
    }
    else{
        return buffer;
    }
}

// 获取指定 path 路径下的所有子节点名称（用于负载均衡）
std::vector<std::string> ZkClient::GetChildren(const char *path) {
    std::vector<std::string> children;  // 保存子节点名字

    struct String_vector strings;  // Zookeeper 内部结构，保存子节点结果
    int flag = zoo_get_children(m_zhandle, path, 0, &strings);
    // 参数解释：
    // m_zhandle：ZK连接句柄
    // path：你要查找的znode路径
    // 0：不开启watcher
    // &strings：返回的子节点列表结构体

    if (flag != ZOK) {
        std::cout << "get children error... path: " << path << std::endl;
        return children;
    }

    // 将结果添加到 C++ vector 中
    for (int i = 0; i < strings.count; ++i) {
        children.emplace_back(strings.data[i]);
    }

    // 释放 zoo_get_children 分配的内存
    deallocate_String_vector(&strings);

    return children;
}
