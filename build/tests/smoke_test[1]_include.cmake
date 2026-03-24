if(EXISTS "/Users/santinomarial/perfdb/build/tests/smoke_test")
  if(NOT EXISTS "/Users/santinomarial/perfdb/build/tests/smoke_test[1]_tests.cmake" OR
     NOT "/Users/santinomarial/perfdb/build/tests/smoke_test[1]_tests.cmake" IS_NEWER_THAN "/Users/santinomarial/perfdb/build/tests/smoke_test" OR
     NOT "/Users/santinomarial/perfdb/build/tests/smoke_test[1]_tests.cmake" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_FILE}")
    include("/opt/homebrew/share/cmake/Modules/GoogleTestAddTests.cmake")
    gtest_discover_tests_impl(
      TEST_EXECUTABLE [==[/Users/santinomarial/perfdb/build/tests/smoke_test]==]
      TEST_EXECUTOR [==[]==]
      TEST_WORKING_DIR [==[/Users/santinomarial/perfdb/build/tests]==]
      TEST_EXTRA_ARGS [==[]==]
      TEST_PROPERTIES [==[]==]
      TEST_PREFIX [==[]==]
      TEST_SUFFIX [==[]==]
      TEST_FILTER [==[]==]
      NO_PRETTY_TYPES [==[FALSE]==]
      NO_PRETTY_VALUES [==[FALSE]==]
      TEST_LIST [==[smoke_test_TESTS]==]
      CTEST_FILE [==[/Users/santinomarial/perfdb/build/tests/smoke_test[1]_tests.cmake]==]
      TEST_DISCOVERY_TIMEOUT [==[5]==]
      TEST_DISCOVERY_EXTRA_ARGS [==[]==]
      TEST_XML_OUTPUT_DIR [==[]==]
    )
  endif()
  include("/Users/santinomarial/perfdb/build/tests/smoke_test[1]_tests.cmake")
else()
  add_test(smoke_test_NOT_BUILT smoke_test_NOT_BUILT)
endif()
