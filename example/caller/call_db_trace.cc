#include "db/mysql_client.h"
#include "db/redis_client.h"
#include "trace/trace_context.h"

int main() {
    TraceContext trace;

    MySQLClient mysql;
    mysql.connect("127.0.0.1", 3306, "root", "root", "test_db");
    mysql.exec("SELECT * FROM test_table", trace);

    RedisClient redis;
    redis.connect("127.0.0.1", 6379);
    redis.set("foo", "bar", trace);
    redis.get("foo", trace);

    std::cout << trace.reportTrace() << std::endl;

    return 0;
}
// ✅ 你看，trace_id 是统一贯穿 mysql + redis + rpc client
// ✅ 这是工业界常用做法，类似于 brpc + zipkin / jaeger trace 方案