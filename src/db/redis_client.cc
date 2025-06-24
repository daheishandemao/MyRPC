#include "redis_client.h"

RedisClient::RedisClient() : ctx_(nullptr) {}

RedisClient::~RedisClient() {
    if (ctx_) redisFree(ctx_);
}

bool RedisClient::connect(const std::string& host, uint16_t port) {
    ctx_ = redisConnect(host.c_str(), port);
    if (ctx_ == nullptr || ctx_->err) {
        std::cerr << "Redis connect failed" << std::endl;
        return false;
    }
    return true;
}

bool RedisClient::set(const std::string& key, const std::string& value, TraceContext& trace) {
    trace.recordEvent("redis_set_start");

    redisReply* reply = (redisReply*)redisCommand(ctx_, "SET %s %s", key.c_str(), value.c_str());
    if (!reply) return false;
    freeReplyObject(reply);

    trace.recordEvent("redis_set_end");
    return true;
//     ✅ redis 操作前后也打 trace 点
// ✅ 贯穿 trace_id → 日志统一串起来分析
}

std::string RedisClient::get(const std::string& key, TraceContext& trace) {
    trace.recordEvent("redis_get_start");

    redisReply* reply = (redisReply*)redisCommand(ctx_, "GET %s", key.c_str());
    std::string res;
    if (reply && reply->type == REDIS_REPLY_STRING) {
        res = reply->str;
    }
    if (reply) freeReplyObject(reply);

    trace.recordEvent("redis_get_end");
    return res;
}
