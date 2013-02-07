function(build_test NAME)
  add_executable(test_${NAME} ${PROJECT_SOURCE_DIR}/tests/${NAME}.cpp)
  target_link_libraries(test_${NAME} ${GTEST_LIBRARIES} ${COVERAGE_LIBRARIES} pthread)
  add_test(test_${NAME} test_${NAME})
endfunction()

build_test(state-machine)
