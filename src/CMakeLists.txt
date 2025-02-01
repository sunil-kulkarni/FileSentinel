cmake_minimum_required(VERSION 3.12)
project(FileSentinel)

add_subdirectory(TUI)

add_executable(FileSentinel main.cpp)

target_link_libraries(FileSentinel PRIVATE TUI)

target_include_directories(FileSentinel PRIVATE
  ${CMAKE_SOURCE_DIR}/src/TUI
)
