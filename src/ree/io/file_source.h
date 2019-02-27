#pragma once

#include <string>
#include <memory>
#include <fstream>

#include <ree/io/source.h>
#include <ree/io/url.h>

namespace ree {
namespace io {

class FileSource: public Source {
public:
    FileSource(const std::shared_ptr<Url> &url);
    ~FileSource();

    void OpenToRead() override;
    void OpenToWrite() override;
    void Close() override;

    size_t GetSize() override;

    size_t CurrentPos() override;
    void Seek(size_t index) override;

    void Read(uint8_t *data, size_t size) override;
    void Write(const uint8_t *data, size_t size) override;

private:
    std::shared_ptr<Url> url_;
    std::ifstream rs_;
    std::ofstream ws_;
};

}
}
