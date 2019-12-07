add_executable(${PROJECT_NAME} fishing-time.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

file(GLOB_RECURSE test_headers "../test/*.h")
file(GLOB_RECURSE test_sources "../test/*.cpp")

add_executable(${PROJECT_NAME}_test test.cpp ${test_headers} ${test_sources})
target_include_directories(${PROJECT_NAME}_test PUBLIC ../test)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_test Qt5::Test)
