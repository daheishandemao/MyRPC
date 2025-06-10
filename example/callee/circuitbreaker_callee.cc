#include "myrpcapplication.h"
#include "rpcprovider.h"
#include "echo.pb.h"

class EchoService : public example::EchoServiceRpc {
    void Echo(::google::protobuf::RpcController* controller,
              const ::example::EchoRequest* request,
              ::example::EchoResponse* response,
              ::google::protobuf::Closure* done) override {
        std::string msg = request->msg();
        response->set_msg("Echo: " + msg);
        done->Run();
    }
};

int main(int argc, char **argv) {
    MyrpcApplication::Init(argc, argv);

    RpcProvider provider;
    provider.NotifyService(new EchoService());
    provider.Run();  // 进入事件循环

    return 0;
}
