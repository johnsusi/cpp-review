add_executable(null_test json/null_test.cpp)
target_link_libraries(null_test PRIVATE json)
add_test(NAME null_test COMMAND null_test)