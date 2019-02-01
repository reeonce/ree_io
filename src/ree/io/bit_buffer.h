#pragma once

#include <cstdint>
#include <cstdlib>

namespace ree {
namespace io {

enum class BitOrder {
    LeftToRight = 0,
    RightToLeft = 1
};

class BitBuffer {
public:
    BitBuffer(const uint8_t *buffer, BitOrder order = BitOrder::LeftToRight,
        size_t begin = 0);

    uint32_t ReadBits(size_t size);
    uint32_t NextBits(size_t size);

private:
    void FeedVal();

    const uint8_t *buffer_;
    BitOrder order_;
    size_t bitPos_;

    uint64_t val_;
    size_t valPos_;
};

}
}