#include "http_source.h"

namespace ree {
namespace io {

HttpSource::HttpSource(const Url &url)
    : url_(url) {
}

int HttpSource::OpenToRead() {
    return -1;
}
int HttpSource::OpenToWrite() {
    return -1;
}
void HttpSource::Close() {
}

int HttpSource::GetSize(size_t &size) {
    return -1;
}

size_t HttpSource::CurrentPos() {
    return 0;
}
int HttpSource::Seek(size_t index) {
    return -1;
}

int HttpSource::Read(uint8_t *data, size_t size) {
    return -1;
}
int HttpSource::Write(const uint8_t *data, size_t size) {
    return -1;
}

}
}
