#include "windows_path.hh"

#include <sstream>
#include <string>
#include <vector>

#include "path.hh"

WindowsPath::WindowsPath(const char drive)
{
    std::ostringstream e;
    e << drive << ':';
    path_.emplace_back(e.str());
}

std::string WindowsPath::to_string() const
{
    std::ostringstream e;
    int i = 0;
    for (auto& file : path_)
    {
        if (i == 0)
            e << file;
        else
            e << '\\' << file;
        i++;
    }
    if (!final_)
        e << '\\';
    return e.str();
}

Path& WindowsPath::join(const std::string& tail, bool is_file)
{
    if (tail.find(":") != std::string::npos
        || tail.find("\"") != std::string::npos
        || tail.find("|") != std::string::npos
        || tail.find("?") != std::string::npos
        || tail.find("*") != std::string::npos || final_)
        return *this;
    path_.push_back(tail);
    final_ = is_file;
    return *this;
}
