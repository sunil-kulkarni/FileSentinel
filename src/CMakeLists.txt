cmake_minimum_required(VERSION 3.12)
project(FileSentinel)

add_subdirectory(TUI)
add_subdirectory(config)
add_subdirectory(checksum)
add_subdirectory(database)

add_executable(FileSentinel main.cpp)

target_link_libraries(FileSentinel PRIVATE TUI config checksum database)

target_include_directories(FileSentinel PRIVATE
  ${CMAKE_SOURCE_DIR}/src/TUI
  ${CMAKE_SOURCE_DIR}/src/config
  ${CMAKE_SOURCE_DIR}/src/checksum
)
