#pragma once

#include "trace/trace_context.h"

#include <mysql/mysql.h>
#include <string>
#include <iostream>

class MySQLClient {
public:
    MySQLClient();
    ~MySQLClient();

    bool connect(const std::string& host, uint16_t port,
                 const std::string& user, const std::string& pwd,
                 const std::string& db);

    bool exec(const std::string& sql, TraceContext& trace);

private:
    MYSQL* conn_;
};
