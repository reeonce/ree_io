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
    
    virtual int OpenToRead() = 0;
    virtual int OpenToWrite() = 0;
    virtual void Close() = 0;

    virtual int GetSize(size_t &size) = 0;

    virtual size_t CurrentPos() = 0;
    virtual int Seek(size_t index) = 0;

    virtual int Read(uint8_t *data, size_t size) = 0;
    virtual int Write(const uint8_t *data, size_t size) = 0;
};

}
}
