#pragma once

#include <cstdint>
#include <string>

namespace ree {
namespace io {

class Url {
public:
    static std::shared_ptr<Url> Parse(const std::string &url_string);
    static std::shared_ptr<Url> RelativeUrl(const std::string &relative_path, 
        const Url &base_url);
    static std::shared_ptr<Url> RelativeUrl(const std::string &relative_path, 
        const std::string &base_path);

    Url();
    ~Url();

    bool operator==(const Url& other) const;

    void AppendPathComponent(const std::string &path);

    std::string UrlString() const;
    bool IsHttpUrl() const;
    bool IsFileUrl() const;
    Url ParentUrl() const;
    bool PathIsAbsolute() const;

    std::string FileName() const;
    std::string FileBaseName() const;
    std::string Extension() const;

    std::string path() const;
    void set_path(const std::string &path);

    std::string scheme() const;
    void set_scheme(const std::string &scheme);

    std::string host() const;
    void set_host(const std::string &host);

    uint16_t port() const;
    void set_port(uint16_t port);

    std::string query() const;
    void set_query(const std::string &query);

private:
    std::string scheme_;
    std::string host_;
    uint16_t port_;
    std::string path_;
    std::string query_;

    char separator_;
};

}
}