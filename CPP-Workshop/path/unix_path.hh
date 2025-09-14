#pragma once

#include <string>

#include "path.hh"
class UnixPath : public Path
{
public:
    UnixPath();
    ~UnixPath() = default;
    std::string to_string() const;
};
