include(FetchContent)

message(STATUS "Using fmt via FetchContent.")
FetchContent_Declare(
 fmt
 GIT_REPOSITORY https://github.com/fmtlib/fmt.git
 GIT_TAG 8.0.1)

message(STATUS "Using googletest via FetchContent.")
FetchContent_Declare(
 googletest
 GIT_REPOSITORY https://github.com/google/googletest.git
 GIT_TAG release-1.11.0)

FetchContent_MakeAvailable(fmt googletest)

set(TEST_LIST map.cpp reduce.cpp fusion.cpp filter.cpp zip.cpp index.cpp)

# Sequential tests
add_executable(seq_tests ${TEST_LIST})
target_link_libraries(seq_tests PRIVATE skl gtest_main fmt::fmt)
add_test(seq_tests seq_tests)

# OMP tests
if(ENABLE_SHARED_MEMORY_LAYER)
 add_executable(omp_tests ${TEST_LIST})
 target_link_libraries(omp_tests PRIVATE skl skl_omp_layer gtest_main fmt::fmt)
 add_test(omp_tests omp_tests)
endif()
