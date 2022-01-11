# add_subdirectory(axpy) add_subdirectory(kmeans) add_subdirectory(matrix-multiplication)

add_executable(axpy axpy/src/main.cpp axpy/src/axpy.cpp)

target_link_libraries(axpy SKL)
