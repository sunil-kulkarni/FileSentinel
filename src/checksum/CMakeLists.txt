add_library(checksum STATIC checksum.cpp)

target_include_directories(checksum PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(checksum OpenSSL::SSL config)
