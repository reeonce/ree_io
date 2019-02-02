#include <ree/unittest.h>

#include <ree/io/bit_buffer.h>

namespace ree {
namespace io {

R_TEST_F(BitBuffer, NextBits) {
    uint8_t buf[] = {0x34, 0x89, 0xef};
    BitBuffer bitBuf(buf, sizeof(buf));

    R_ASSERT_EQ(bitBuf.ReadBits(1), 0);
    R_ASSERT_EQ(bitBuf.ReadBits(2), 1);
}
   
}
}