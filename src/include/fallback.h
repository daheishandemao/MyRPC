#pragma once
#include <functional>
// #include <google/protobuf/Message>？
#include "google/protobuf/service.h"

using FallbackFunc = std::function<void(const google::protobuf::Message*, google::protobuf::Message*)>;