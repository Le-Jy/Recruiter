#include "replace.hh"

#include <fstream>
#include <iostream>
#include <string>

void replace(const std::string& input_filename,
             const std::string& output_filename, const std::string& src_token,
             const std::string& dst_token)
{
    std::ifstream ip_file(input_filename);
    if (!ip_file)
    {
        std::cerr << "Cannot open input file" << '\n';
        return;
    }
    std::ofstream op_file(output_filename);
    if (!op_file)
    {
        std::cerr << "Cannot write output file" << '\n';
        return;
    }
    std::string tokens;
    size_t len_dst = dst_token.length();
    size_t len_src = src_token.length();
    while (std::getline(ip_file, tokens))
    {
        size_t index = 0;
        while ((index = tokens.find(src_token, index)) != std::string::npos)
        {
            tokens = tokens.replace(index, len_src, dst_token);
            index += len_dst;
        }
        op_file << tokens << '\n';
    }
}
