#include "path.hh"

#include <string>
#include <vector>

Path& Path::join(const std::string& tail, bool is_file)
{
    if (!final_)
    {
        path_.push_back(tail);
        final_ = is_file;
    }
    return *this;
}
