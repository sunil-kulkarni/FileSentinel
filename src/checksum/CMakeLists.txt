cmake_minimum_required(VERSION 3.10)

# Project name
project(ChecksumLibrary)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add the checksum library
add_library(checksum STATIC checksum.cpp)

# Include directories
target_include_directories(checksum PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link OpenSSL to the checksum library
target_link_libraries(checksum OpenSSL::SSL)
