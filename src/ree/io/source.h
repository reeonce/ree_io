#pragma once

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>

namespace ree {
namespace io {

class Source {
public:
    static std::shared_ptr<Source> SourceByPath(const std::string &path);
    
    virtual ~Source();
    
    virtual void OpenToRead() = 0;
    virtual void OpenToWrite() = 0;
    virtual void Close() = 0;

    virtual size_t GetSize() = 0;

    virtual size_t CurrentPos() = 0;
    virtual void Seek(size_t index) = 0;

    virtual void Read(uint8_t *data, size_t size) = 0;
    virtual void Write(const uint8_t *data, size_t size) = 0;
};

}
}
