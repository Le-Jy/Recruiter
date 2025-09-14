cmake_minimum_required(VERSION 3.21.2)
SET(SRC_FILES
    node.cc
    node_impl.cc
    story.cc
    story_impl.cc
)

target_sources(libzork PUBLIC ${SRC_FILES})