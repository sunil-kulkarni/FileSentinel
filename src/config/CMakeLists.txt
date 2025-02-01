add_library(config config.cpp)

target_include_directories(config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(config PUBLIC yaml-cpp::yaml-cpp)

