# MyRPC - 轻量高性能 RPC 框架

MyRPC 是一个基于 C++ 开发的轻量级、高性能、模块化的 RPC 框架，支持负载均衡、熔断、限流、健康检查、链路追踪、高并发处理，适合作为学习和中小型分布式系统的基础组件。

## 特性 Features

✅ 支持 protobuf 序列化协议  
✅ TCP 自定义协议防止粘包拆包问题  
✅ 基于 ZooKeeper 实现服务注册与发现  
✅ 轮询 / 随机 / 最小连接数负载均衡  
✅ 令牌桶限流 + 熔断 + 降级策略  
✅ 健康检查（pluggable probe）  
✅ 链路追踪 trace_id 贯穿客户端 / 服务端 / DB  
✅ ThreadPool 优化高并发  
✅ 兼容 MySQL / Redis 等中间件  
✅ OpenTelemetry 集成预留中

## 目录结构

src/ -- 核心实现
core/ -- RPC 框架核心
codec/ -- 协议编码解码
zk/ -- Zookeeper 工具类
limiter/ -- 熔断 / 限流 / 降级
balance/ -- 负载均衡算法
threadpool/ -- 线程池
trace/ -- 链路追踪
monitor/ -- 监控
example/ -- 示例代码 caller / callee
test/ -- 单元测试
lib/ -- 编译生成库文件
bin/ -- 运行产物


## 编译 & 运行

```bash
# 安装依赖
sudo apt install -y protobuf-compiler libprotobuf-dev zookeeper libzookeeper-mt-dev mysql-client libmysqlclient-dev redis

# 编译
mkdir build && cd build
cmake ..
make -j

# 运行示例
cd bin
./provider
./consumer
