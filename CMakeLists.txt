cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project ####################################################################

project(LAS VERSION 0.2.0)
configure_file(include/las/version/config.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/include/las/version/config.hpp")

include(cmake/ProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(las_options INTERFACE)
target_compile_options(las_options INTERFACE -march=native)
# -save-temps -fno-omit-frame-pointer

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(las_warnings INTERFACE)
set_project_warnings(las_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
# enable_sanitizers(las_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
# enable_doxygen()

# Library #######################################################

add_library(las INTERFACE)
target_link_libraries(las INTERFACE las_options las_warnings)
target_include_directories(las INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>)

add_library(las_cpu_layer INTERFACE)
target_compile_definitions(las_cpu_layer INTERFACE LAS_CPU_LAYER)

find_package(OpenMP REQUIRED)
add_library(las_omp_layer INTERFACE)
target_link_libraries(las_omp_layer INTERFACE OpenMP::OpenMP_CXX)
target_compile_definitions(las_omp_layer INTERFACE LAS_OMP_LAYER)

add_library(las_dynamic_layers INTERFACE)
target_link_libraries(las_dynamic_layers INTERFACE las_cpu_layer las_omp_layer)
target_compile_definitions(las_dynamic_layers INTERFACE LAS_DYNAMIC_LAYERS)

add_library(las_static_layers INTERFACE)
target_link_libraries(las_static_layers INTERFACE)
target_compile_definitions(las_static_layers INTERFACE LAS_STATIC_LAYERS)

enable_testing()
add_subdirectory(test)

# add_subdirectory(examples)
