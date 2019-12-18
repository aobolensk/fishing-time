cmake_minimum_required(VERSION 3.0)
project(fishing-time)

set(CMAKE_AUTOMOC ON)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0043 NEW)
if(${CMAKE_VERSION} VERSION_GREATER "3.13.0")
    cmake_policy(SET CMP0079 NEW)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets Test)

include_directories(include)

include("${PROJECT_SOURCE_DIR}/cmake/config.cmake")

add_subdirectory(src)
add_subdirectory(app)
