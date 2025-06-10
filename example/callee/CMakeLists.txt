#set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST friendservice.cc ../friend.pb.cc)
set(SRC_LIST circuitbreaker_callee.cc ../echo.pb.cc)
add_executable(provider ${SRC_LIST})
target_link_libraries(provider myrpc protobuf)#链接项目内的库