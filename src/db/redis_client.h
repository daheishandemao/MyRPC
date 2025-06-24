#pragma once

#include "trace/trace_context.h"

#include <hiredis/hiredis.h>
#include <string>
#include <iostream>

class RedisClient {
public:
    RedisClient();
    ~RedisClient();

    bool connect(const std::string& host, uint16_t port);
    bool set(const std::string& key, const std::string& value, TraceContext& trace);
    std::string get(const std::string& key, TraceContext& trace);

private:
    redisContext* ctx_;
};
