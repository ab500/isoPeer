include_directories(include/Common)
add_executable(CommonTest Base64EncoderTest.cpp)
target_link_libraries(CommonTest gtest_main Common)
add_test(NAME CommonTest WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND CommonTest)