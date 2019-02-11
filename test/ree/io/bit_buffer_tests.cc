#include <ree/unittest.h>

#include <ree/io/bit_buffer.h>

namespace ree {
namespace io {

R_TEST_F(LSigBitBuffer, NextBits) {
    uint8_t buf[] = {0x34, 0x89, 0xef};
    {
        LSigBitBuffer bitBuf(buf, sizeof(buf));
        R_ASSERT_EQ(bitBuf.NextBits(1), 0);
        R_ASSERT_EQ(bitBuf.NextBits(2), 0);
        R_ASSERT_EQ(bitBuf.NextBits(3), 0x01);
        R_ASSERT_EQ(bitBuf.NextBits(4), 0x03);
        R_ASSERT_EQ(bitBuf.NextBits(5), 0x06);
        R_ASSERT_EQ(bitBuf.NextBits(6), 0x0d);
        R_ASSERT_EQ(bitBuf.NextBits(7), 0x1a);
        R_ASSERT_EQ(bitBuf.NextBits(8), 0x34);
        R_ASSERT_EQ(bitBuf.NextBits(9), 0x69);
        R_ASSERT_EQ(bitBuf.NextBits(10), 0xd2);
        R_ASSERT_EQ(bitBuf.NextBits(11), 0x1a4);
        R_ASSERT_EQ(bitBuf.NextBits(12), 0x348);
        R_ASSERT_EQ(bitBuf.NextBits(23), 0x1a44f7);
        R_ASSERT_EQ(bitBuf.NextBits(24), 0x3489ef);
    }
    {
        LSigBitBuffer bitBuf(buf, sizeof(buf), 2);
        R_ASSERT_EQ(bitBuf.NextBits(1), 0x01);
        R_ASSERT_EQ(bitBuf.NextBits(2), 0x03);
        R_ASSERT_EQ(bitBuf.NextBits(3), 0x06);
        R_ASSERT_EQ(bitBuf.NextBits(4), 0x0d);
        R_ASSERT_EQ(bitBuf.NextBits(5), 0x1a);
        R_ASSERT_EQ(bitBuf.NextBits(6), 0x34);
        R_ASSERT_EQ(bitBuf.NextBits(7), 0x69);
        R_ASSERT_EQ(bitBuf.NextBits(8), 0xd2);
        R_ASSERT_EQ(bitBuf.NextBits(9), 0x1a4);
        R_ASSERT_EQ(bitBuf.NextBits(10), 0x348);
        R_ASSERT_EQ(bitBuf.NextBits(11), 0x691);
        R_ASSERT_EQ(bitBuf.NextBits(12), 0xd22);
        R_ASSERT_EQ(bitBuf.NextBits(21), 0x1a44f7);
        R_ASSERT_EQ(bitBuf.NextBits(22), 0x3489ef);
    }
}
    
R_TEST_F(BigEndianLSigBitBuffer, NextBits) {
    uint8_t buf[] = {0x34, 0x89, 0xef};
    {
        BigEndianLSigBitBuffer bitBuf(buf, sizeof(buf));
        R_ASSERT_EQ(bitBuf.NextBits(1), 0);
        R_ASSERT_EQ(bitBuf.NextBits(2), 0);
        R_ASSERT_EQ(bitBuf.NextBits(3), 0x04);
        R_ASSERT_EQ(bitBuf.NextBits(4), 0x04);
        R_ASSERT_EQ(bitBuf.NextBits(5), 0x14);
        R_ASSERT_EQ(bitBuf.NextBits(6), 0x34);
        R_ASSERT_EQ(bitBuf.NextBits(7), 0x34);
        R_ASSERT_EQ(bitBuf.NextBits(8), 0x34);
        R_ASSERT_EQ(bitBuf.NextBits(9), 0x69);
        R_ASSERT_EQ(bitBuf.NextBits(10), 0xd1);
        R_ASSERT_EQ(bitBuf.NextBits(11), 0x1a1);
        R_ASSERT_EQ(bitBuf.NextBits(12), 0x349);
        R_ASSERT_EQ(bitBuf.NextBits(23), 0x1a44ef);
        R_ASSERT_EQ(bitBuf.NextBits(24), 0x3489ef);
    }
    {
        BigEndianLSigBitBuffer bitBuf(buf, sizeof(buf), 2);
        R_ASSERT_EQ(bitBuf.NextBits(1), 0x01);
        R_ASSERT_EQ(bitBuf.NextBits(2), 0x01);
        R_ASSERT_EQ(bitBuf.NextBits(3), 0x05);
        R_ASSERT_EQ(bitBuf.NextBits(4), 0x0d);
        R_ASSERT_EQ(bitBuf.NextBits(5), 0x0d);
        R_ASSERT_EQ(bitBuf.NextBits(6), 0x0d);
        R_ASSERT_EQ(bitBuf.NextBits(7), 0x1b);
        R_ASSERT_EQ(bitBuf.NextBits(8), 0x35);
        R_ASSERT_EQ(bitBuf.NextBits(9), 0x69);
        R_ASSERT_EQ(bitBuf.NextBits(10), 0xd9);
        R_ASSERT_EQ(bitBuf.NextBits(11), 0x1a9);
        R_ASSERT_EQ(bitBuf.NextBits(12), 0x349);
        R_ASSERT_EQ(bitBuf.NextBits(21), 0x6c4ef);
        R_ASSERT_EQ(bitBuf.NextBits(22), 0xd89ef);
    }
}
   
}
}
