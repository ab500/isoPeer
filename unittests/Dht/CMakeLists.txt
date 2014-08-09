include_directories(include/Dht)
add_executable(UniqueIdTest UniqueIdTest.cpp)
target_link_libraries(UniqueIdTest gtest_main Dht)
add_test(NAME UniqueIdTest WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND UniqueIdTest)