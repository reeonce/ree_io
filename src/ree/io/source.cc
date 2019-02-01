#include "source.h"

#include <ree/io/url.h>
#include <ree/io/file_source.h>

namespace ree {
namespace io {

std::shared_ptr<Source> Source::SourceByPath(const std::string &path) {
    auto url = Url::Parse(path);
    if (!url) {
        return nullptr;
    }
    if (url->IsFileUrl()) {
        FileSource *source = new FileSource(url);
        return std::shared_ptr<Source>(source);
    }
    return nullptr;
}

}
}
