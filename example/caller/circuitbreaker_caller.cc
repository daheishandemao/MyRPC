#include "myrpcapplication.h"
#include "myrpcchannel.h"
#include "myrpccontroller.h"
#include "echo.pb.h"
#include <unistd.h> // for sleep
#include "fallback.h" 

int main(int argc, char **argv) {
    // 初始化框架
    MyrpcApplication::Init(argc, argv);

    // 创建channel对象
    auto *channel = new MyrpcChannel();

    // 设置fallback回调函数：当熔断或限流触发时，返回默认值
    channel->setFallback([](const google::protobuf::Message* req,
                            google::protobuf::Message* resp) {
        auto* echo_resp = dynamic_cast<example::EchoResponse*>(resp);
        if (echo_resp) {
            echo_resp->set_msg("[fallback] service unavailable, using default response");
        }
    });

    // 创建stub对象并传入自定义channel
    example::EchoServiceRpc_Stub stub(channel);

    for (int i = 0; i < 20; ++i) {
        example::EchoRequest request;
        request.set_msg("Hello");

        example::EchoResponse response;

        MyrpcController controller;

        // 调用远程方法
        stub.Echo(&controller, &request, &response, nullptr);

        if (controller.Failed()) {
            std::cout << "[FAIL] (" << i << ") " << controller.ErrorText() << " | response: " << response.msg()<< std::endl;
        } else {
            std::cout << "[OK]   (" << i << ") " << response.msg() << std::endl;
        }

        sleep(1);
    }

    return 0;
}
