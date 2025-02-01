cmake_minimum_required(VERSION 3.16)

project(FileSentinel VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(ftxui 5 REQUIRED)
find_package(SQLite3 REQUIRED)
add_subdirectory(src)

enable_testing()

install(TARGETS FileSentinel
  RUNTIME DESTINATION /usr/local/bin
)
