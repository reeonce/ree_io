#include "bit_buffer.h"

namespace ree {
namespace io {

BitBuffer::BitBuffer(const uint8_t *buffer, BitOrder order, size_t begin)
    : buffer_(buffer),
      order_(order),
      bitPos_(begin),
      val_(0),
      valPos_(sizeof(val_)) {
}
uint32_t BitBuffer::ReadBits(size_t size) {
    auto val = NextBits(size);
    valPos_ += size;
    return val;
}
uint32_t BitBuffer::NextBits(size_t size) {
    if (valPos_ + size > sizeof(val_)) {
        FeedVal();
    }
    uint64_t mask = (1 << size) - 1;
    return val_ & mask;
}
void BitBuffer::FeedVal() {
    
}

}
}