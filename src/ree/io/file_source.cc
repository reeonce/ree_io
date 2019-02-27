#include "file_source.h"

namespace ree {
namespace io {

FileSource::FileSource(const std::shared_ptr<Url> &url)
    : url_(url) {
    auto rExceptionMask = rs_.exceptions() | std::ios::failbit;
    rs_.exceptions(rExceptionMask);
    auto wExceptionMask = ws_.exceptions() | std::ios::failbit;
    ws_.exceptions(wExceptionMask);
}

FileSource::~FileSource() {
}

void FileSource::OpenToRead() {
    auto urlString = url_->UrlString();
    rs_.open(urlString, std::ifstream::binary);
}
void FileSource::OpenToWrite() {
    auto urlString = url_->UrlString();
    ws_.open(urlString, std::ofstream::binary);
}
void FileSource::Close() {
    if (rs_.is_open()) {
        rs_.close();
    }
    if (ws_.is_open()) {
        ws_.close();
    }
}

size_t FileSource::GetSize() {
    size_t pos = rs_.tellg();
    rs_.seekg(0, rs_.end);
    size_t size = rs_.tellg();
    rs_.seekg(pos);
    return size;
}

size_t FileSource::CurrentPos() {
    return rs_.tellg();
}
void FileSource::Seek(size_t index) {
    rs_.seekg(index, rs_.beg);
}

void FileSource::Read(uint8_t *data, size_t size) {
    rs_.read(reinterpret_cast<char *>(data), size);
}
void FileSource::Write(const uint8_t *data, size_t size) {
    ws_.write(reinterpret_cast<const char *>(data), size);
}

}
}
