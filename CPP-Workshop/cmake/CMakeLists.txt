cmake_minimum_required(VERSION 3.21.2)

project(hello_yaka)

add_subdirectory(libyaka)

add_executable(hello_yaka src/main.cc)

target_link_libraries(hello_yaka PUBLIC yaka)

target_compile_options(hello_yaka
    PUBLIC
    -Wall -Wextra -Werror -pedantic -std=c++20 -Wold-style-cast
  )
