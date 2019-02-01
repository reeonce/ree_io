#include "memory_source.h"

namespace ree {
namespace io {

MemorySource::MemorySource(const std::vector<uint8_t> &&buffer)
    : buffer_(std::move(buffer)) {
}
MemorySource::MemorySource(const std::vector<uint8_t> &buffer)
    : buffer_(buffer) {
}

int MemorySource::OpenToRead() {
    pos_ = 0;
    return 0;
}
int MemorySource::OpenToWrite() {
    pos_ = 0;
    return 0;
}
void MemorySource::Close() {
}

int MemorySource::GetSize(size_t &size) {
    return buffer_.size();
}

size_t MemorySource::CurrentPos() {
    return pos_;
}
int MemorySource::Seek(size_t index) {
    pos_ = index;
    return 0;
}

int MemorySource::Read(uint8_t *data, size_t size) {
    size_t last = pos_ + size;
    if (last > buffer_.size()) {
        return -1;
    }
    std::copy(buffer_.begin() + pos_, buffer_.begin() + last, data);
    return 0;
}
int MemorySource::Write(const uint8_t *data, size_t size) {
    buffer_.insert(buffer_.end(), data, data + size);
    return 0;
}

}
}