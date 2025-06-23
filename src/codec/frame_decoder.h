#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <string>
#include <mutex>

class FrameDecoder {
public:
    // onFrame 回调，收到完整 frame 时调用
    using FrameCallback = std::function<void(const std::string& frame)>;

    FrameDecoder();

    // 设置回调
    void setFrameCallback(FrameCallback cb);

    // 外部调用这个函数，喂入 TCP 流数据
    void onData(const char* data, size_t len);

private:
    std::vector<char> buffer_; // 内部 buffer
    FrameCallback callback_;
    std::mutex mutex_;
};
