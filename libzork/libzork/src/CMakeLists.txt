cmake_minimum_required(VERSION 3.21.2)

add_subdirectory(runner)
add_subdirectory(store)
add_subdirectory(story)
add_subdirectory(vars)
target_sources(libzork PRIVATE exceptions.cc)