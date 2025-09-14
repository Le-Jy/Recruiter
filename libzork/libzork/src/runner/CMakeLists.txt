cmake_minimum_required(VERSION 3.21.2)
SET(SRC_FILES
    choice.cc
    choice_impl.cc
    html.cc
    html_impl.cc
    interactive.cc
    runner.cc
    smart.cc
    smart_impl.cc
)

target_sources(libzork PRIVATE ${SRC_FILES})