include_directories(include)

add_library(yaka src/yaka.cc)

target_include_directories(yaka PUBLIC ./include)

target_compile_options(yaka
    PUBLIC
    -Wall -Wextra -Werror -pedantic -std=c++20 -Wold-style-cast
)

