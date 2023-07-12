cmake_minimum_required(VERSION 3.25)
project(Antlandia VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/builds")

set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")


add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

find_package(SFML COMPONENTS system window graphics)

target_link_libraries(${PROJECT_NAME} PRIVATE src sfml-system sfml-graphics sfml-window )