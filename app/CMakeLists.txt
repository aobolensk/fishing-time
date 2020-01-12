add_executable(${PROJECT_NAME} fishing-time.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

file(GLOB_RECURSE test_headers "../test/*.h")
file(GLOB_RECURSE test_sources "../test/*.cpp")

if (NOT DEBUG)
    if (WIN32)
        if (MSVC)
            set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE YES
                LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
        elseif(CMAKE_COMPILER_IS_GNUCXX)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
        endif (MSVC)
    endif (WIN32)
endif (NOT DEBUG)

add_executable(${PROJECT_NAME}_test test.cpp ${test_headers} ${test_sources})
target_include_directories(${PROJECT_NAME}_test PUBLIC ../test)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_test Qt5::Test)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
    target_compile_options(${PROJECT_NAME}_test PRIVATE "/MP")
endif (MSVC)
