#include "memory_source.h"

#include <exception>

namespace ree {
namespace io {

MemorySource::MemorySource(const std::vector<uint8_t> &&buffer)
    : buffer_(std::move(buffer)) {
}
MemorySource::MemorySource(const std::vector<uint8_t> &buffer)
    : buffer_(buffer) {
}

void MemorySource::OpenToRead() {
    pos_ = 0;
}
void MemorySource::OpenToWrite() {
    pos_ = 0;
}
void MemorySource::Close() {
}

size_t MemorySource::GetSize() {
    return buffer_.size();
}

size_t MemorySource::CurrentPos() {
    return pos_;
}
void MemorySource::Seek(size_t index) {
    pos_ = index;
}

void MemorySource::Read(uint8_t *data, size_t size) {
    size_t last = pos_ + size;
    if (last > buffer_.size()) {
        throw std::out_of_range("extends to end!");
    }
    std::copy(buffer_.begin() + pos_, buffer_.begin() + last, data);
}
void MemorySource::Write(const uint8_t *data, size_t size) {
    buffer_.insert(buffer_.end(), data, data + size);
}

}
}