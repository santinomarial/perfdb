add_executable(common_test config_test.cpp)
target_link_libraries(common_test PRIVATE perfdb_common GTest::gtest_main)
gtest_discover_tests(common_test DISCOVERY_MODE PRE_TEST)
