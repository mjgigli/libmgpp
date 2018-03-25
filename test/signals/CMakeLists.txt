add_executable(test-signals test_signals.cpp)
target_link_libraries(test-signals ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(test-signals mgpp)
add_test(test-signals test-signals)
