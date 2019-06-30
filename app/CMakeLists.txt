file(GLOB_RECURSE sources "../src/*.cpp")
file(GLOB_RECURSE headers "../include/*.h")

include("${PROJECT_SOURCE_DIR}/cmake/config.cmake")
add_executable(${PROJECT_NAME} fishing-time.cpp ${sources} ${headers})
