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

    int OpenToRead() override;
    int OpenToWrite() override;
    void Close() override;

    int GetSize(size_t &size) override;

    size_t CurrentPos() override;
    int Seek(size_t index) override;

    int Read(uint8_t *data, size_t size) override;
    int Write(const uint8_t *data, size_t size) override;

private:
    std::shared_ptr<Url> url_;
    std::ifstream rs_;
    std::ofstream ws_;
};

}
}
