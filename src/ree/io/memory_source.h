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

    void OpenToRead() override;
    void OpenToWrite() override;
    void Close() override;

    size_t GetSize() override;

    size_t CurrentPos() override;
    void Seek(size_t index) override;

    void Read(uint8_t *data, size_t size) override;
    void Write(const uint8_t *data, size_t size) override;

private:
    std::vector<uint8_t> buffer_;
    size_t pos_;
};

}
}