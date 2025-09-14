#include "stdin_to_file.hh"

#include <fstream>
#include <iostream>
#include <string>

ssize_t stdin_to_file(const std::string& filename)
{
    std::ofstream file_out(filename);
    std::string token;
    ssize_t res = 0;
    if (file_out.is_open())
    {
        while (std::cin >> token)
        {
            res++;
            file_out << token << '\n';
        }
    }
    return res;
}
