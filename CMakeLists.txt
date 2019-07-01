cmake_minimum_required(VERSION 3.0)
project(fishing-time)

set(CMAKE_AUTOMOC ON)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0043 NEW)
if(${CMAKE_VERSION} VERSION_GREATER "3.13.0") 
    cmake_policy(SET CMP0079 NEW)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(include)

file(GLOB_RECURSE headers "include/*.h")
file(GLOB_RECURSE sources "src/*.cpp")

include("${PROJECT_SOURCE_DIR}/cmake/config.cmake")
add_executable(${PROJECT_NAME} app/fishing-time.cpp ${sources} ${headers})

qt5_use_modules(${PROJECT_NAME} Widgets)
