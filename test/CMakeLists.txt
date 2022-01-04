
set(TEST_LIST "zip;adapter;map;fusion;reduce")

foreach(TEST ${TEST_LIST})
    # Sequential tests
    add_executable(${TEST} test_${TEST}.cpp)
    target_link_libraries(${TEST} PRIVATE SKL)
    add_test(SEQ_${TEST} ${TEST})
    # OMP tests
    add_executable(omp_${TEST} test_${TEST}.cpp)
    target_link_libraries(omp_${TEST} PRIVATE SKL)
    target_compile_definitions(omp_${TEST} PRIVATE SKL_OMP)
    add_test(OMP_${TEST} omp_${TEST})
endforeach()

