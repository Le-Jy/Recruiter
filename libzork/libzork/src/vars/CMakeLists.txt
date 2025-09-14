cmake_minimum_required(VERSION 3.21.2)
SET(SRC_FILES
    action.cc
    action_impl.cc
    condition.cc
    condition_impl.cc
)

target_sources(libzork PUBLIC ${SRC_FILES})