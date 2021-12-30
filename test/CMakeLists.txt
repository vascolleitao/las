find_package(Boost 1.71.0 REQUIRED)

#test_filter
foreach(TEST test_simple test_map test_reduce test_zip)
    add_executable(${TEST} ${TEST}.cpp)
    target_link_libraries(${TEST}
        PRIVATE
            ${LIBRARY_SKL3}
    )
endforeach()

foreach(TEST test_simple test_map test_reduce test_zip)
    add_executable(sm_${TEST} ${TEST}.cpp)
    target_link_libraries(sm_${TEST}
        PRIVATE
            ${LIBRARY_SKL3}
    )
    target_compile_definitions(sm_${TEST} PRIVATE SKL_OMP)
endforeach()
