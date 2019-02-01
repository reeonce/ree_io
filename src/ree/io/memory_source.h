#pragma once

#include <string>
#include <vector>

#include <ree/io/source.h>

namespace ree {
namespace io {

class MemorySource: public Source {
public:
    MemorySource(const std::vector<uint8_t> &&buffer);
    MemorySource(const std::vector<uint8_t> &buffer);

    int OpenToRead() override;
    int OpenToWrite() override;
    void Close() override;

    int GetSize(size_t &size) override;

    size_t CurrentPos() override;
    int Seek(size_t index) override;

    int Read(uint8_t *data, size_t size) override;
    int Write(const uint8_t *data, size_t size) override;

private:
    std::vector<uint8_t> buffer_;
    size_t pos_;
};

}
}