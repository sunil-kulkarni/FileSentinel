add_library(TUI TUI.cpp)

target_include_directories(TUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TUI PRIVATE ftxui::screen ftxui::dom ftxui::component)
