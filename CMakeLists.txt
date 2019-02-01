cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(ree_io CXX)

set(REE_IO_SRC
    src/ree/io/url.h
    src/ree/io/url.cc
    src/ree/io/source.h
    src/ree/io/source.cc
    src/ree/io/http_source.h
    src/ree/io/http_source.cc
    src/ree/io/file_source.h
    src/ree/io/file_source.cc
    src/ree/io/memory_source.h
    src/ree/io/memory_source.cc
    src/ree/io/bit_buffer.h
    src/ree/io/bit_buffer.cc
)

add_library(ree_io ${REE_IO_SRC})
target_include_directories(ree_io PUBLIC src/)

set_target_properties(ree_io PROPERTIES
    CMAKE_CXX_STANDARD 11
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF
)

option(REE_IO_ENABLE_TESTS "enable unit tests" OFF)

if(REE_IO_ENABLE_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ree_unittest
        ${CMAKE_CURRENT_BINARY_DIR}/ree_unittest)

    set(REE_IO_TESTS_SRC
        test/ree/io/bit_buffer_tests.cc
    )
    add_executable(test test/main.cc ${REE_IO_TESTS_SRC})
    target_include_directories(test PRIVATE test/)
    target_link_libraries(test PRIVATE ree_io ree_unittest)
endif(REE_IO_ENABLE_TESTS)