include(FetchContent)

message(STATUS "Using fmt via FetchContent.")
FetchContent_Declare(
 fmt
 GIT_REPOSITORY https://github.com/fmtlib/fmt.git
 GIT_TAG 8.0.1)
FetchContent_MakeAvailable(fmt)

# set(TEST_LIST "zip;adapter;map;fusion;reduce")
set(TEST_LIST "map;reduce;fusion;filter")

foreach(TEST ${TEST_LIST})
 # Sequential tests
 add_executable(${TEST} ${TEST}.cpp)
 target_link_libraries(${TEST} PRIVATE skl fmt::fmt)
 add_test(SEQ_${TEST} ${TEST})
 # OMP tests add_executable(omp_${TEST} ${TEST}.cpp) target_link_libraries(omp_${TEST} PRIVATE skl skl_omp_layer fmt::fmt) add_test(OMP_${TEST} omp_${TEST})
endforeach()
