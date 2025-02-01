cmake_minimum_required(VERSION 3.10)

project(ChecksumLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)
add_library(checksum STATIC checksum.cpp)

target_include_directories(checksum PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(checksum OpenSSL::SSL)
