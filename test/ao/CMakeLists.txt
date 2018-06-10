add_executable(test-hsm test_hsm.cpp)
target_link_libraries(test-hsm ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(test-hsm ao)
add_test(test-hsm test-hsm)
