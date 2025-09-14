#include "director.hh"

#include <iostream>

void Director::handle_request(int level)
{
    if (level <= 3)
        std::cout << "Director handles\n";
    else
        forward_request(level);
}
