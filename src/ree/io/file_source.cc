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

int FileSource::OpenToRead() {
    auto urlString = url_->UrlString();
    try {
        rs_.open(urlString, std::ifstream::binary);
    } catch (std::ios_base::failure& e) {
        return e.code().value();
    }
    return 0;
}
int FileSource::OpenToWrite() {
    auto urlString = url_->UrlString();
    try {
        ws_.open(urlString, std::ofstream::binary);
    } catch (std::ios_base::failure& e) {
        return e.code().value();
    }
    return 0;
}
void FileSource::Close() {
    if (rs_.is_open()) {
        rs_.close();
    }
    if (ws_.is_open()) {
        ws_.close();
    }
}

int FileSource::GetSize(size_t &size) {
    try {
        rs_.seekg(0, rs_.end);
        size = rs_.tellg();
    } catch (std::ios_base::failure& e) {
        return e.code().value();
    }
    return 0;
}

size_t FileSource::CurrentPos() {
    return rs_.tellg();
}
int FileSource::Seek(size_t index) {
    try {
        rs_.seekg(index, rs_.beg);
    } catch (std::ios_base::failure& e) {
        return e.code().value();
    }
    return 0;
}

int FileSource::Read(uint8_t *data, size_t size) {
    try {
        rs_.read(reinterpret_cast<char *>(data), size);
    } catch (std::ios_base::failure& e) {
        return e.code().value();
    }
    return 0;
}
int FileSource::Write(const uint8_t *data, size_t size) {
    try {
        ws_.write(reinterpret_cast<const char *>(data), size);
    } catch (std::ios_base::failure& e) {
        return e.code().value();
    }
    return 0;
}

}
}
