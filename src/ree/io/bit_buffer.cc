#include "bit_buffer.h"

#include <algorithm>

namespace ree {
namespace io {

static uint8_t lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

static uint8_t reverse_bits(uint8_t n) {
   // Reverse the top and bottom nibble then swap them.
   return (lookup[n&0b1111] << 4) | lookup[n>>4];
}

LSigBitBuffer::LSigBitBuffer(const uint8_t *buffer, size_t size, size_t begin)
    : buffer_(buffer),
      size_(size),
      pos_(begin) {
}
uint32_t LSigBitBuffer::ReadBits(size_t size) {
    uint32_t val = NextBits(size);
    pos_ += size;
    return val;
}
uint32_t LSigBitBuffer::NextBits(size_t size) {
	BitsValue<uint32_t> window;
    FeedVal(window, size);
    return static_cast<uint32_t>(window.val);
}
void LSigBitBuffer::FeedVal(BitsValue<uint32_t> &window, size_t size) {
    while (window.bits < size) {
        size_t bitPos = (pos_ + window.bits);
        size_t bytePos = bitPos >> 3;
        if (bytePos >= size_) {
            break;
        }
        uint8_t nextByte = buffer_[bytePos];
        size_t invalidBits = bitPos & 0x07;
        size_t validBits = 8 - invalidBits;
        
        size_t nextBits = std::min(size - window.bits, validBits);
        nextByte = (nextByte << invalidBits) >> (8 - nextBits);
        window.val = (window.val << nextBits) | nextByte;
        window.bits += nextBits;
    }
}

BigEndianLSigBitBuffer::BigEndianLSigBitBuffer(const uint8_t *buffer,
    size_t size, size_t begin)
    : buffer_(buffer),
      size_(size),
      pos_(begin) {
}
uint32_t BigEndianLSigBitBuffer::ReadBits(size_t size) {
    uint32_t val = NextBits(size);
    pos_ += size;
    return val;
}
uint32_t BigEndianLSigBitBuffer::NextBits(size_t size) {
	BitsValue<uint32_t> window;
    FeedVal(window, size);
    return window.val;
}
void BigEndianLSigBitBuffer::FeedVal(BitsValue<uint32_t> &window, size_t size) {
    while (window.bits < size) {
        size_t bitPos = (pos_ + window.bits);
        size_t bytePos = bitPos >> 3;
        if (bytePos >= size_) {
            break;
        }
        uint8_t nextByte = buffer_[bytePos];
        size_t invalidBits = bitPos & 0x07;
        size_t validBits = 8 - invalidBits;
        
        size_t nextBits = std::min(size - window.bits, validBits);
        nextByte = (nextByte >> invalidBits) & ((1 << nextBits) - 1);
        window.val = (window.val << nextBits) | nextByte;
        window.bits += nextBits;
    }
}

LittleEndianLSigBitBuffer::LittleEndianLSigBitBuffer(const uint8_t *buffer,
    size_t size, size_t begin)
    : buffer_(buffer),
      size_(size),
      pos_(begin) {
}
uint32_t LittleEndianLSigBitBuffer::ReadBits(size_t size) {
    uint32_t val = NextBits(size);
    window_.val >>= size;
    window_.bits -= size;
    return val;
}
uint32_t LittleEndianLSigBitBuffer::NextBits(size_t size) {
    if (window_.bits < size) {
        FeedVal();
    }
    return window_.val & ((1 << size) - 1);
}
void LittleEndianLSigBitBuffer::FeedVal() {
    while (window_.bits <= 56 && (pos_ >> 3) < size_) {
        uint8_t nextByte = buffer_[(pos_ >> 3)];
        size_t invalidBits = pos_ & 0x07;
        size_t validBits = 8 - invalidBits;
        nextByte >>= invalidBits;
        window_.val = (window_.val << validBits) | nextByte;
        window_.bits += validBits;
        pos_ += validBits;
    }
}

}
}
