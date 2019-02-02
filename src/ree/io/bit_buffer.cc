#include "bit_buffer.h"

namespace ree {
namespace io {

BitBuffer::BitBuffer(const uint8_t *buffer, size_t size, BitOrder order,
    size_t begin)
    : buffer_(buffer),
    size_(size),
    order_(order),
    bitPos_(begin),
    val_(0),
    valBits_(0) {
}
uint32_t BitBuffer::ReadBits(size_t size) {
    auto val = NextBits(size);
    val >>= size;
    valBits_ -= size;
    return val;
}
uint32_t BitBuffer::NextBits(size_t size) {
    if (valBits_ < size) {
        FeedVal();
    }
    if (order_ == BitOrder::LeftToRight) {
        uint64_t mask = (1 << size) - 1;
        return val_ & mask;
    } else {
        uint64_t mask = (1 << size) - 1;
        return val_ & mask;
    }
}
void BitBuffer::FeedVal() {
    while (valBits_ <= 56 && 8 * size_ - bitPos_ > 0) {
        if (bitPos_ % 8 != 0) {
            val_ = val_ << 8 | buffer_[bitPos_ / 8];
            bitPos_ = (bitPos_ / 8 + 1) * 8;
            valBits_ = valBits_ + (8 - bitPos_ % 8);
        } else {
            val_ = val_ << 8 | buffer_[bitPos_ / 8];
            bitPos_ += 8;
            valBits_ += 8;
        }
    }
}

}
}
