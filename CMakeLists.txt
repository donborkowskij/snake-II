cmake_minimum_required(VERSION 3.19)
project(FirstProg)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(FirstProg src/main.cpp src/Engine.cpp headers/Engine.h src/draw.cpp src/input.cpp src/Snake.cpp headers/Snake.h src/update.cpp src/Apple.cpp headers/Apple.h src/Wall.cpp headers/Wall.h)

include_directories(headers)

set(SFML_ROOT "SFML-2.4.2")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED graphics network audio window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

#Copy dlls to build directory
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()