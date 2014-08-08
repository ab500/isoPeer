cmake_minimum_required(VERSION 2.8)

project(IsoPeer)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include(CTest)
set(gtest_force_shared_crt 1)

add_subdirectory(lib)
add_subdirectory(utils)

include_directories(${gtest_SOURCE_DIR}/include)
include_directories(include)
add_subdirectory(unittests)
