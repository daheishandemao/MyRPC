#include "mysql_client.h"

MySQLClient::MySQLClient() : conn_(mysql_init(nullptr)) {}

MySQLClient::~MySQLClient() {
    if (conn_) mysql_close(conn_);
}

bool MySQLClient::connect(const std::string& host, uint16_t port,
                          const std::string& user, const std::string& pwd,
                          const std::string& db) {
    if (!mysql_real_connect(conn_, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), port, nullptr, 0)) {
        std::cerr << "MySQL connect failed: " << mysql_error(conn_) << std::endl;
        return false;
    }
    return true;
}

bool MySQLClient::exec(const std::string& sql, TraceContext& trace) {
    trace.recordEvent("mysql_start");

    if (mysql_query(conn_, sql.c_str()) != 0) {
        std::cerr << "MySQL query failed: " << mysql_error(conn_) << std::endl;
        return false;
    }

    MYSQL_RES* res = mysql_store_result(conn_);
    if (res) {
        mysql_free_result(res);
    }

    trace.recordEvent("mysql_end");
    return true;
}
// ✅ 在执行 mysql_query 前后，记录 trace event
// ✅ 后面 reportTrace 会自动打印这个阶段的耗时