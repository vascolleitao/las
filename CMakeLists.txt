cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project ####################################################################

project(SKL VERSION 0.1.0)
configure_file(include/skl/config.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/include/skl/config.hpp")

include(cmake/ProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(skl_options INTERFACE)
target_compile_options(skl_options INTERFACE -march=native) # -save-temps -fno-omit-frame-pointer
# target_compile_features(skl_options INTERFACE cxx_std_2b)

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
enable_doxygen()

# Library #######################################################

add_library(skl INTERFACE)
target_link_libraries(skl INTERFACE skl_options skl_warnings)
target_include_directories(skl INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
# $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>

if(ENABLE_SHARED_MEMORY_LAYER)
 find_package(OpenMP REQUIRED)
 add_library(skl_omp_layer INTERFACE)
 target_link_libraries(skl_omp_layer INTERFACE OpenMP::OpenMP_CXX)
 target_compile_definitions(skl_omp_layer INTERFACE SKL_OMP)
 target_link_libraries(skl INTERFACE skl_omp_layer)
endif()

enable_testing()
add_subdirectory(test)

# add_subdirectory(examples)
