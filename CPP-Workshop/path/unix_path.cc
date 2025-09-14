#include "unix_path.hh"

#include <sstream>
#include <string>

UnixPath::UnixPath()
    : Path()
{}

std::string UnixPath::to_string() const
{
    std::ostringstream e;
    for (auto& file : path_)
        e << '/' << file;
    if (!final_)
        e << '/';
    return e.str();
}
