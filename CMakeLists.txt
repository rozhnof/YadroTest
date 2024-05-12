cmake_minimum_required(VERSION 3.16)

project(
    computer-clab-manager
    LANGUAGES CXX
    VERSION 0.1
)

include(cmake/CheckCompiler.cmake)
include(cmake/CompileOptions.cmake)
include(cmake/Sanitize.cmake)
include(cmake/Dependencies.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILE_LIST CONFIGURE_DEPENDS
    "src/*.cc"
)

file(GLOB_RECURSE HEADER_FILE_LIST CONFIGURE_DEPENDS
    "include/*.h"
)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS 
    "tests/*.cc"
)

add_library(core ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PUBLIC core)


if(BUILD_TESTS)
    add_executable(${PROJECT_NAME}-test ${TEST_FILES})
    target_link_libraries(${PROJECT_NAME}-test PUBLIC core gtest gtest_main)
endif()