find_package(Git REQUIRED)

foreach(CONFIG "" _DEBUG _RELEASE)
    set("CMAKE_ARCHIVE_OUTPUT_DIRECTORY${CONFIG}" "${PROJECT_BINARY_DIR}/lib")
    set("CMAKE_LIBRARY_OUTPUT_DIRECTORY${CONFIG}" "${PROJECT_BINARY_DIR}/lib")
    set("CMAKE_RUNTIME_OUTPUT_DIRECTORY${CONFIG}" "${PROJECT_BINARY_DIR}/bin")
endforeach()

# Get commit hash
execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse HEAD WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}" OUTPUT_VARIABLE commit_hash)
string(STRIP ${commit_hash} commit_hash)
add_definitions(-DCOMMIT_HASH=${commit_hash})

if (DEBUG)
    message(STATUS "[-DDEBUG] Debug mode is enabled")
    set (CMAKE_BUILD_TYPE Debug)
endif (DEBUG)

if (NO_ASSERTS)
    message(STATUS "[-DNO_ASSERTS] Assertions have been disabled")
    add_definitions(-DFT_IGNORE_ASSERTS=1)
endif (NO_ASSERTS)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /wd4127 /wd5054 /wd4996 /wd5240")
    # disabled warning C4127: conditional expression is constant
    # disabled warning C5054: operator *: deprecated between enumerations of different types
    # disabled warning C4996: deprecated declarations
    # disabled warning C5240: 'nodiscard': attribute is ignored in this syntactic position
    if (NOT DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
    endif (NOT DEBUG)
else(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Wconversion -Wno-deprecated-declarations")
    if (DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -ggdb3")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif (DEBUG)
endif(MSVC)
