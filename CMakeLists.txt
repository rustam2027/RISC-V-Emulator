cmake_minimum_required (VERSION 3.11)
project(RISC-V-Emulator
  LANGUAGES CXX
  VERSION 1.0.0
)
set(CMAKE_CXX_STANDARD 20)


include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG "origin/main"
)
 
FetchContent_GetProperties(ftxui)

if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(${PROJECT_NAME} main.cpp 
    interpreter/Interpreter.cpp 
    frontend/Lexer.cpp 
    frontend/Parser.cpp 
    frontend/Preprocessor.cpp 
    instructions/instructions_impl.cpp 
    interpreter/Interpreter.cpp
    tests/simple_instructions_test.cpp
    UI/UI.cpp
    UI/padding.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE src)
 
target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component

)