cmake_minimum_required(VERSION 3.15)
project(SKL CXX)

################################################################################
### Project ####################################################################
################################################################################

include(cmake/ProjectSettings.cmake)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)
target_compile_options(project_options
    INTERFACE
        #-save-temps
        #-fno-omit-frame-pointer
        -march=native)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

################################################################################
### Library ####################################################################
################################################################################


#find_package(Boost 1.71.0 REQUIRED)
find_package(OpenMP REQUIRED)

add_library(SKL INTERFACE)

target_include_directories(SKL
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        #$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        #$<INSTALL_INTERFACE:include>
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(SKL
    INTERFACE
        project_options
        #project_warnings
        OpenMP::OpenMP_CXX
)

if(ENABLE_SHARED_MEMORY_LAYER)
target_compile_definitions(skl
    INTERFACE
        SKL_SM)
endif()


enable_testing()
add_subdirectory(test)

add_subdirectory(examples)
