#pragma once

#include <string>

#include <ree/io/source.h>
#include <ree/io/url.h>

namespace ree {
namespace io {

class HttpSource: public Source {
public:
    HttpSource(const Url &url);

    void OpenToRead() override;
    void OpenToWrite() override;
    void Close() override;

    size_t GetSize() override;

    size_t CurrentPos() override;
    void Seek(size_t index) override;

    void Read(uint8_t *data, size_t size) override;
    void Write(const uint8_t *data, size_t size) override;

private:
    Url url_;
};

}
}