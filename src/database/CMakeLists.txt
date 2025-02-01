add_library(database database.cpp)

target_include_directories(database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(database ${SQLite3_LIBRARIES})
