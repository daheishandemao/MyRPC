#include "codec/frame_decoder.h"
#include <cstring>
#include <arpa/inet.h>  // for ntohl

FrameDecoder::FrameDecoder()
{}

void FrameDecoder::setFrameCallback(FrameCallback cb) {
    std::lock_guard<std::mutex> lock(mutex_);
    callback_ = std::move(cb);
}

void FrameDecoder::onData(const char* data, size_t len) {
    std::lock_guard<std::mutex> lock(mutex_);

    // 把新数据 append 到 buffer_
    buffer_.insert(buffer_.end(), data, data + len);

    // 处理完整 frame
    while (true) {
        // 判断 buffer 里有没有 4 字节长度
        if (buffer_.size() < sizeof(uint32_t)) {
            return; // 不够，等下次
        }

        // 读前 4 个字节 frame_length
        uint32_t frame_length = 0;
        std::memcpy(&frame_length, buffer_.data(), sizeof(uint32_t));
        frame_length = ntohl(frame_length); // 大端转小端

        // 判断 buffer 里是否有完整 frame
        if (buffer_.size() < sizeof(uint32_t) + frame_length) {
            return; // 还不够
        }

        // 取出完整 frame
        std::string frame(buffer_.begin() + sizeof(uint32_t),
                          buffer_.begin() + sizeof(uint32_t) + frame_length);

        // 回调
        if (callback_) {
            callback_(frame);
        }

        // 删除已处理的 frame
        buffer_.erase(buffer_.begin(),
                      buffer_.begin() + sizeof(uint32_t) + frame_length);
    }
}
