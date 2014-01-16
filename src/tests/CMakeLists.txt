
add_subdirectory(gtest-src)

set(TESTS_SRC
  run.cc
  test_matrix.cc
)

add_executable(libsimple_run_tests ${TESTS_SRC})
target_link_libraries(libsimple_run_tests simple0 gtest gtest_main)

add_test(libsimple_tests libsimple_run_tests)
