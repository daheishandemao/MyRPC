#aux_source_directory(. SRC_LIST)
# set(SRC_LIST 
#     myrpcapplication.cc 
#     myrpcconfig.cc 
#     rpcprovider.cc 
#     rpcheader.pb.cc 
#     myrpcchannel.cc
#     myrpccontroller.cc
#     logger.cc
#     lockqueue.cc
#     zookeeperutil.cc
#     trace_context.cc
#     rate_limiter.cc)
file(GLOB_RECURSE MYRPC_SRC
    core/*.cc
    limiter/*.cc
    balance/*.cc
    codec/*.cc
    zk/*.cc
    log/*.cc
    trace/*.cc
    monitor/*.cc
    threadpool/*.cc
)
# add_library(myrpc ${SRC_LIST})#删去SHARED就是静态库，可以生成SHARED的动态库
add_library(myrpc STATIC ${MYRPC_SRC})
# 头文件路径
target_include_directories(myrpc PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
)
target_link_libraries(myrpc muduo_net muduo_base pthread zookeeper_mt)#前后顺序之间的不同库是有依赖关系的，muduo_net是网络的核心库，应该先链接