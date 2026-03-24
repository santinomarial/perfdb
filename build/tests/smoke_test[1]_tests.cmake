add_test([=[SmokeTest.BuildWorks]=]  /Users/santinomarial/perfdb/build/tests/smoke_test [==[--gtest_filter=SmokeTest.BuildWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SmokeTest.BuildWorks]=]  PROPERTIES DEF_SOURCE_LINE /Users/santinomarial/perfdb/tests/smoke_test.cpp:4 WORKING_DIRECTORY /Users/santinomarial/perfdb/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  smoke_test_TESTS SmokeTest.BuildWorks)
