#include <array>
#include <iostream>
#include <libyaka/yaka.hh>
#include <string>

namespace yaka
{
    void greet_cpp_respos()
    {
        const size_t NB_RESPOS = 6;
        const auto cpp_respos = std::array<std::string, NB_RESPOS>{
            "Clara ROSSI-CARIGNANO", "Jules WIRIATH", "Léa MARGERY",
            "Maxence MICHOT",        "Sacha HIBON",   "Théo GARDET"
        };

        for (const auto& respo : cpp_respos)
        {
            std::cout << "Hello, " << respo << "!\n";
        }
    }
} // namespace yaka
