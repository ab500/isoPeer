include_directories(include/Dht)
add_executable(DhtTest UniqueIdTest.cpp MessageTest.cpp)
target_link_libraries(DhtTest gtest_main Dht Common)
add_test(NAME DhtTest WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND DhtTest)