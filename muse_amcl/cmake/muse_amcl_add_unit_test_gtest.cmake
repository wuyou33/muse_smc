## use with gtest
enable_testing()
function(add_unit_test_gtest UNIT_TEST_NAME UNIT_TEST_SRCS UNIT_TEST_LIBS)
    catkin_add_gtest(${UNIT_TEST_NAME}
        ${UNIT_TEST_SRCS}
    )

    target_link_libraries(${UNIT_TEST_NAME}
        ${UNIT_TEST_LIBS}
        ${GTEST_LIBRARIES}
    )
endfunction()