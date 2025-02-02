cmake_minimum_required(VERSION 3.12)
project(FileSentinel)

add_subdirectory(TUI)
add_subdirectory(config)
add_subdirectory(checksum)
add_subdirectory(database)

add_executable(FileSentinel main.cpp)

include(FetchContent)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.83.0
)

FetchContent_MakeAvailable(Boost)

target_include_directories(FileSentinel PRIVATE ${Boost_SOURCE_DIR})

target_link_libraries(FileSentinel PRIVATE TUI config checksum database)

target_include_directories(FileSentinel PRIVATE
  ${CMAKE_SOURCE_DIR}/src/TUI
  ${CMAKE_SOURCE_DIR}/src/config
  ${CMAKE_SOURCE_DIR}/src/checksum
)
