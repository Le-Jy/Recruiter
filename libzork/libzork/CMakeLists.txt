cmake_minimum_required(VERSION 3.21.2)

project(libzork)
add_compile_options(-Wall -Wextra -Werror -pedantic -std=c++20 -Wold-style-cast)
find_library(YAML-CPP NAMES yaml-cpp libyaml-cpp libyaml-cpp-dev REQUIRED)

add_library(libzork SHARED)


target_include_directories(libzork PUBLIC include)
target_include_directories(libzork PRIVATE src)

target_link_libraries(libzork PRIVATE ${YAML-CPP})
set_property(TARGET libzork PROPERTY CXX_STANDARD 20)

add_subdirectory(src)

add_executable(main_libzork zorkxplorer/src/main.cc zorkxplorer/src/options.cc)
set_property(TARGET main_libzork PROPERTY CXX_STANDARD 20)
target_include_directories(main_libzork PRIVATE src)
target_link_libraries(main_libzork PUBLIC libzork)


set_target_properties(libzork PROPERTIES OUTPUT_NAME zork)