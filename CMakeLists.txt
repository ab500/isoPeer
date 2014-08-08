cmake_minimum_required(VERSION 2.8)

project(IsoPeer)

include(CTest)

set(gtest_force_shared_crt 1)

add_subdirectory(lib)
add_subdirectory(utils)

include_directories(${gtest_SOURCE_DIR}/include)
add_subdirectory(unittests)
