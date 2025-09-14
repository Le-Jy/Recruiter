#pragma once
#include <string>

#include "path.hh"

class WindowsPath : public Path
{
public:
    WindowsPath(const char drive);
    ~WindowsPath() = default;
    std::string to_string() const;
    Path& join(const std::string& tail, bool is_file = false);
};
