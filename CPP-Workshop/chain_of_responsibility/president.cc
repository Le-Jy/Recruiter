#include "president.hh"

#include <iostream>

void President::handle_request(int level)
{
    if (level <= 9)
        std::cout << "President handles\n";
    else
        forward_request(level);
}
