cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project ####################################################################

project(SKL VERSION 0.1.0)
configure_file(include/skl/config.hpp.in
               "${CMAKE_CURRENT_SOURCE_DIR}/include/skl/config.hpp")

include(cmake/ProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(skl_options INTERFACE)
target_compile_options(skl_options INTERFACE -march=native
)# -save-temps -fno-omit-frame-pointer
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

include(FetchContent)

# Library #######################################################

#[[
message(STATUS "Using boost via FetchContent.")
FetchContent_Declare(
 Boost
 GIT_REPOSITORY https://github.com/boostorg/boost.git
 GIT_TAG boost-1.78.0)

FetchContent_GetProperties(boostorg)
if(NOT boostorg_POPULATED)
 FetchContent_Populate(boostorg)
 add_subdirectory(${boostorg_SOURCE_DIR} ${boostorg_BINARY_DIR})
endif()
include_directories(${boostorg_SOURCE_DIR})
message(STATUS "Using boost via FetchContent.")
FetchContent_Declare(
 Boost
 GIT_REPOSITORY https://github.com/boostorg/boost.git
 GIT_TAG boost-1.78.0
 GIT_SUBMODULES libs/fusion)
]]

set(BoostModules
    fusion
    iterator
    config
    container_hash
    core
    function_types
    mpl
    preprocessor
    static_assert
    tuple
    type_traits
    typeof
    utility
    assert
    throw_exception
    detail
    integer
    predef
    io
    concept_check
    conversion
    optional
    smart_ptr
    move)

add_library(boost_deps INTERFACE)

foreach(MODULE ${BoostModules})
  message(STATUS "Using Boost::${MODULE} via FetchContent.")
  FetchContent_Declare(
    Boost${MODULE}
    GIT_REPOSITORY https://github.com/boostorg/${MODULE}.git
    GIT_TAG boost-1.78.0)

  FetchContent_MakeAvailable(Boost${MODULE})
  target_link_libraries(boost_deps INTERFACE Boost::${MODULE})
endforeach()

#[[
message(STATUS "Using Boost::fusion via FetchContent.")
FetchContent_Declare(
 BoostFusion
 GIT_REPOSITORY https://github.com/boostorg/fusion.git
 GIT_TAG boost-1.78.0)

message(STATUS "Using Boost::iterator via FetchContent.")
FetchContent_Declare(
 BoostIterator
 GIT_REPOSITORY https://github.com/boostorg/iterator.git
 GIT_TAG boost-1.78.0)

FetchContent_MakeAvailable(BoostFusion BoostIterator)
]]

add_library(skl INTERFACE)
target_link_libraries(skl INTERFACE skl_options boost_deps)
target_include_directories(
  skl INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
# $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
# $<INSTALL_INTERFACE:include>

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
