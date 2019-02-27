#include "http_source.h"

#include <exception>

namespace ree {
namespace io {

HttpSource::HttpSource(const Url &url)
    : url_(url) {
}

void HttpSource::OpenToRead() {
    throw std::bad_exception();
}
void HttpSource::OpenToWrite() {
    throw std::bad_exception();
}
void HttpSource::Close() {
    throw std::bad_exception();
}

size_t HttpSource::GetSize() {
    throw std::bad_exception();
}

size_t HttpSource::CurrentPos() {
    return 0;
}
void HttpSource::Seek(size_t index) {
    throw std::bad_exception();
}

void HttpSource::Read(uint8_t *data, size_t size) {
    throw std::bad_exception();
}
void HttpSource::Write(const uint8_t *data, size_t size) {
    throw std::bad_exception();
}

}
}
