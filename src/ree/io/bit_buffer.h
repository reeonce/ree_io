#pragma once

#include <cstdint>
#include <cstdlib>

namespace ree {
namespace io {

template<typename T> 
struct BitsValue {
    BitsValue() : val(0), bits(0) {}

    T val;
    size_t bits;
};

/**
 * the data is not byte aligned, with the right bit is least significant bit
 */
class RLSBBuffer {
public:
    RLSBBuffer(const uint8_t *buffer, size_t size, size_t begin = 0);

    /**
     * read some bits of the buffer and advance the cursor
     *
     * @param size the size of bits to read, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t ReadBits(size_t size);

    /**
     * get the value of next bits in the buffer without advancing the cursor
     *
     * @param size the size of bits to get, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t NextBits(size_t size);
private:
    void FeedVal(BitsValue<uint32_t> &window, size_t size);

    const uint8_t *buffer_;
    size_t size_;
    size_t pos_;
};

/**
 * the data is not byte aligned, with the left bit is least significant bit
 */
class LLSBBuffer {
public:
    LLSBBuffer(const uint8_t *buffer, size_t size, size_t begin = 0);

    /**
     * read some bits of the buffer and advance the cursor
     *
     * @param size the size of bits to read, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t ReadBits(size_t size);

    /**
     * get the value of next bits in the buffer without advancing the cursor
     *
     * @param size the size of bits to get, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t NextBits(size_t size);
private:
    void FeedVal();

    const uint8_t *buffer_;
    size_t size_;
    size_t pos_;
    BitsValue<uint64_t> window_;
};

/**
 * the data is byte aligned, while lower memory bytes are more significant, 
 * and the right bit is least significant bit. Such as ZLIB data format.
 */
class BigEndianRLSBBuffer {
public:
    BigEndianRLSBBuffer(const uint8_t *buffer, size_t size,
        size_t begin = 0);

    /**
     * read some bits of the buffer and advance the cursor
     *
     * @param size the size of bits to read, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t ReadBits(size_t size);

    /**
     * get the value of next bits in the buffer without advancing the cursor
     *
     * @param size the size of bits to get, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t NextBits(size_t size);
private:
    void FeedVal(BitsValue<uint32_t> &window, size_t size);

    const uint8_t *buffer_;
    size_t size_;
    size_t pos_;
};

/**
 * the data is byte aligned, while lower memory bytes are less significant, 
 * and the right bit is least significant bit.
 */
class LittleEndianRLSBBuffer {
public:
    LittleEndianRLSBBuffer(const uint8_t *buffer, size_t size,
        size_t begin = 0);

    /**
     * read some bits of the buffer and advance the cursor
     *
     * @param size the size of bits to read, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t ReadBits(size_t size);

    /**
     * get the value of next bits in the buffer without advancing the cursor
     *
     * @param size the size of bits to get, must be smaller or equals to 32
     * @return the value in the buffer bit order
     */
    uint32_t NextBits(size_t size);
private:
    void FeedVal();

    const uint8_t *buffer_;
    size_t size_;
    size_t pos_;
	BitsValue<uint64_t> window_;
};

}
}
