include(GoogleTest)
enable_testing()

add_executable(smoke_test smoke_test.cpp)
target_link_libraries(smoke_test PRIVATE GTest::gtest_main spdlog::spdlog)
gtest_discover_tests(smoke_test DISCOVERY_MODE PRE_TEST)

add_subdirectory(storage)
add_subdirectory(buffer)
add_subdirectory(index)
add_subdirectory(log)
add_subdirectory(txn)
add_subdirectory(integration)
