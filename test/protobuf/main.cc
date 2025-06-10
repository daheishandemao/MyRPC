//为了测试protobuf的代码
#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main(){
    LoginResponse lrsp;
    ResultCode *rc=lrsp.mutable_result();
    rc->set_errcode(1);
    rc->set_errmsg("error");
    lrsp.set_success(false);
    //序列化
    std::string send_str;
    if(lrsp.SerializePartialToString(& send_str)){
        std::cout<<send_str<<std::endl;
    }
    LoginResponse lrspB;
    ResultCode *rc2=lrsp.mutable_result();//用成员变量指针去读取成员类型
    if(lrspB.ParseFromString(send_str)){
        std::cout<<lrspB.success()<<std::endl;
        std::cout<<rc2->errcode()<<std::endl;
        std::cout<<rc2->errmsg()<<std::endl;
    }
}
int main1(){
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");

    //序列化
    //1、将req转换成string，同样也可以转换成字节数组的字节流和文件等
    //2、返回值是bool，所有需要判断是否序列化成功；并且用一个string保存输出
    std::string send_str;
    if(req.SerializeToString(& send_str)){
        std::cout<<send_str<<std::endl;
    }
    //反序列化
    LoginRequest reqB; 
    if(reqB.ParseFromString(send_str)){
        std::cout<<reqB.name()<<std::endl;
        std::cout<<reqB.pwd()<<std::endl;
    }
    return 0;
}