cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project ####################################################################

project(LAS VERSION 0.2.0)
configure_file(include/las/version/config.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/include/las/version/config.hpp")

include(cmake/ProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(skl_options INTERFACE)
target_compile_options(skl_options INTERFACE -march=native)
# -save-temps -fno-omit-frame-pointer

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(skl_warnings INTERFACE)
set_project_warnings(skl_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
# enable_sanitizers(skl_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
# enable_doxygen()

# Library #######################################################

add_library(las INTERFACE)
target_link_libraries(las INTERFACE skl_options skl_warnings)
target_include_directories(las INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>)

add_library(skl_cpu_layer INTERFACE)
target_compile_definitions(skl_cpu_layer INTERFACE SKL_CPU_LAYER)

find_package(OpenMP REQUIRED)
add_library(skl_omp_layer INTERFACE)
target_link_libraries(skl_omp_layer INTERFACE OpenMP::OpenMP_CXX)
target_compile_definitions(skl_omp_layer INTERFACE SKL_OMP_LAYER)

add_library(skl_dynamic_layers INTERFACE)
target_link_libraries(skl_dynamic_layers INTERFACE skl_cpu_layer skl_omp_layer)
target_compile_definitions(skl_dynamic_layers INTERFACE SKL_DYNAMIC_LAYERS)

add_library(skl_static_layers INTERFACE)
target_link_libraries(skl_static_layers INTERFACE)
target_compile_definitions(skl_static_layers INTERFACE SKL_STATIC_LAYERS)

enable_testing()
add_subdirectory(test)

# add_subdirectory(examples)
