cmake_minimum_required(VERSION 3.1)

project(Snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

file(GLOB SOURCES "src/*.cpp")
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
add_executable(snake ${SOURCES}
        headers/State.h
        headers/StateManager.h
        src/StateManager.cpp
        headers/Game.h
        src/Game.cpp)

target_link_libraries(snake PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_options(snake PRIVATE -g -Wall -Wextra -pedantic )
target_include_directories(snake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)