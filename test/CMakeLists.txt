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

set(TEST_LIST "main.cpp;map.cpp;reduce.cpp;fusion.cpp;filter.cpp")

add_library(las_test INTERFACE)
target_link_libraries(las_test INTERFACE gtest_main fmt::fmt)

# Default Sequential tests
add_executable(default_seq_tests ${TEST_LIST})
target_link_libraries(default_seq_tests las_test las)
add_test(default_seq_tests default_seq_tests)

# Static Sequential tests
add_executable(static_seq_tests ${TEST_LIST})
target_link_libraries(static_seq_tests las_test las las_static_layers las_cpu_layer)
add_test(static_seq_tests static_seq_tests)

# Static OMP tests
add_executable(static_omp_tests ${TEST_LIST} threads.cpp)
target_link_libraries(static_omp_tests las_test las las_static_layers las_cpu_layer las_omp_layer)
add_test(static_omp_tests static_omp_tests)

# Dynamic Dynamic tests
add_executable(dynamic_tests ${TEST_LIST})
target_link_libraries(dynamic_tests las_test las las_dynamic_layers)
add_test(dynamic_tests dynamic_tests)
