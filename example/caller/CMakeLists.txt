#set(SRC_LIST calluserservice.cc ../user.pb.cc)
set(SRC_LIST callfriendservice.cc ../friend.pb.cc)
set(SRC_LIST circuitbreaker_caller.cc ../echo.pb.cc)
add_executable(consumer ${SRC_LIST})
target_link_libraries(consumer myrpc protobuf)#链接项目内的库