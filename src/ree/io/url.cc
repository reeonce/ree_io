#include "url.h"

#include <sstream>
#include <vector>
#include <algorithm>

namespace ree {
namespace io {

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::shared_ptr<Url> Url::Parse(const std::string &url_string) {
    Url *url = new Url();

    size_t win_separator = url_string.find('\\');
    url->separator_ = win_separator == std::string::npos ? '/' : '\\';
    
    std::string win_disk_flag = ":\\";
    size_t win_disk_end = url_string.find(win_disk_flag);
    // windows path
    if (win_disk_end != std::string::npos) {
        url->path_.assign(url_string, 0, url_string.length());
        return std::shared_ptr<Url>(url);
    }
    
    size_t cursor = 0;

    std::string scheme_flag = ":";
    scheme_flag += url->separator_;
    scheme_flag += url->separator_;
    
    size_t scheme_end = url_string.find(scheme_flag);
    
    if (scheme_end != std::string::npos) {
        url->scheme_.assign(url_string, cursor, scheme_end - cursor);
        std::transform(url->scheme_.begin(), url->scheme_.end(),
            url->scheme_.begin(), ::tolower);
        cursor = scheme_end + 3;
    }

    // invalid url
    if (cursor >= url_string.length()) {
        return nullptr;
    }

    if (!url->scheme_.empty()) {
        size_t host_port_end = url_string.find('/', cursor);
        std::string host_port;
        if (host_port_end == std::string::npos) {
            host_port.assign(url_string, cursor, url_string.length() - cursor);
        } else {
            host_port.assign(url_string, cursor, host_port_end - cursor);
        }
        size_t colon_pos = host_port.find(':');
        if (colon_pos == std::string::npos) {
            url->host_ = host_port;
            cursor = host_port_end;
        } else {
            // only if port does exist after :, we can tell it is host:port. otherwise, it should be c:/xxx
            if (colon_pos + 1 < host_port.length()) {
                url->host_.assign(host_port, 0, colon_pos);
                auto port_string = host_port.substr(colon_pos + 1,
                                                    host_port.length() - colon_pos - 1);
                std::stringstream ss(port_string, std::ios_base::in);
                ss >> url->port_;
                cursor = host_port_end;
            }
        }
    }

    size_t path_end = url_string.find('?', cursor);
    if (path_end == std::string::npos) {
        url->path_.assign(url_string, cursor, url_string.length() - cursor);
    } else {
        url->path_.assign(url_string, cursor, path_end - cursor);
        url->query_.assign(url_string, path_end + 1,
            url_string.length() - path_end - 1);
    }
    return std::shared_ptr<Url>(url);
}

std::shared_ptr<Url> Url::RelativeUrl(const std::string &relative_path, 
    const Url &base_url) {
    Url *url = new Url(base_url);
    url->AppendPathComponent(relative_path);
    return std::shared_ptr<Url>(url);
}

std::shared_ptr<Url> Url::RelativeUrl(const std::string &relative_path, 
    const std::string &base_path) {
    auto url = Parse(base_path);
    if (url) {
        url->AppendPathComponent(relative_path);
    }
    return url;
}


Url::Url()
    : port_(0) {
}

Url::~Url() {
}

bool Url::operator==(const Url &other) const {
    return UrlString() == other.UrlString();
}

void Url::AppendPathComponent(const std::string &path_component) {
    bool path_end_with_sep = path_.length() > 0 && path_.back() == separator_;
    bool comp_beg_with_sep = path_component.length() > 0 && 
        path_component.front() == separator_;

    if (path_end_with_sep && comp_beg_with_sep) {
        path_.append(path_component, 1, path_component.length() - 1);
    } else if (!path_end_with_sep && !comp_beg_with_sep) {
        path_ += separator_;
        path_ += path_component;
    } else {
        path_ += path_component;
    }
}

std::string Url::UrlString() const {
    std::string url_string = "";
    if (!scheme_.empty()) {
        url_string += (scheme_ + ':' + separator_ + separator_);
    }
    if (!host_.empty()) {
        url_string += host_;

        if (port_ > 0) {
            url_string += ':';
            url_string += std::to_string(port_);
        }
    }

    if (!path_.empty()) {
        url_string += path_;
    }

    if (!query_.empty()) {
        url_string += '?';
        url_string += query_;
    }

    return url_string;
}

bool Url::IsHttpUrl() const {
    return scheme_ == "http" || scheme_ == "https";
}

bool Url::IsFileUrl() const {
    return scheme_ == "file" || scheme_.empty();
}

bool Url::PathIsAbsolute() const {
    if (separator_ == '/') {
        return path_.length() > 0 && path_[0] == separator_;
    } else {
        return path_.length() > 3 && path_[1] == ':' && 
            path_[2] == separator_ && path_[3] == separator_ &&
            ((path_[0] >= 'a' && path_[0] <= 'z') || 
                (path_[0] >= 'A' && path_[0] <= 'Z'));
    }
}

Url Url::ParentUrl() const {
    Url url(*this);
    if (!url.path_.empty()) {
        char separator[] = {separator_, '\0'};

        size_t search_pos = url.path_.length();
        if (url.path_.length() > 2) {
            // skip the ending separator
            search_pos = url.path_.length() - 2;
        }

        auto last_sep_pos = url.path_.rfind(separator, search_pos);
        if (last_sep_pos == std::string::npos) {
            url.path_ = std::string();
        } else {
            url.path_.resize(last_sep_pos + 1);
        }
    }
    return url;
}

std::string Url::FileName() const {
    std::vector<std::string> components;
    split(path_, separator_, std::back_inserter(components));

    return components.size() > 0 ? components.back() : std::string();
}

std::string Url::FileBaseName() const {
    std::string file_name = FileName();
    auto dot_pos = file_name.find_last_of('.');
    if (dot_pos != std::string::npos) {
        file_name.resize(dot_pos);
    }
    return file_name;
}

std::string Url::Extension() const {
    std::string file_name = FileName();
    auto dot_pos = file_name.find_last_of('.');
    if (dot_pos == std::string::npos) {
        return std::string();
    }
    return file_name.substr(dot_pos + 1);
}

std::string Url::path() const {
    return path_;
}
void Url::set_path(const std::string &path) {
    path_ = path;
}

std::string Url::scheme() const {
    return scheme_;
}
void Url::set_scheme(const std::string &scheme) {
    scheme_ = scheme;
}

std::string Url::host() const {
    return host_;
}
void Url::set_host(const std::string &host) {
    host_ = host;
}

uint16_t Url::port() const {
    return port_;
}
void Url::set_port(uint16_t port) {
    port_ = port;
}


std::string Url::query() const {
    return query_;
}
void Url::set_query(const std::string &query) {
    query_ = query;
}

}
}