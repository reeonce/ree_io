#pragma once

#include <string>

#include <ree/io/source.h>
#include <ree/io/url.h>

namespace ree {
namespace io {

class HttpSource: public Source {
public:
    HttpSource(const Url &url);

    int OpenToRead() override;
    int OpenToWrite() override;
    void Close() override;

    int GetSize(size_t &size) override;

    size_t CurrentPos() override;
    int Seek(size_t index) override;

    int Read(uint8_t *data, size_t size) override;
    int Write(const uint8_t *data, size_t size) override;

private:
    Url url_;
};

}
}