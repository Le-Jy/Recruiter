#include "read_info.hh"

#include <cstdint>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

DirectoryInfo read_info(std::istream& file)
{
    std::string line;
    std::getline(file, line);
    std::string tokens;
    std::string name;
    std::string owner;
    size_t size;
    uint16_t rights;
    std::istringstream sline(line);
    sline >> name;
    if (!sline.good())
        return DirectoryInfo();
    sline >> size;
    if (!sline.good())
        return DirectoryInfo();
    sline >> std::oct >> rights;
    if (!sline.good())
        return DirectoryInfo();
    sline >> owner;
    if (sline.good())
        return DirectoryInfo();
    return DirectoryInfo(name, size, rights, owner);
}
