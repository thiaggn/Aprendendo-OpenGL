cmake_minimum_required(VERSION 3.27)

project(DragonSlayer CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

add_executable(dragonslayer
    src/glad.cpp
    src/main.cpp
    src/shader.cpp
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(dragonslayer "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")