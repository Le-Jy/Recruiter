cmake_minimum_required(VERSION 3.21.2)
SET(SRC_FILES
    store.cc
    store_impl.cc
)

target_sources(libzork PUBLIC ${SRC_FILES})