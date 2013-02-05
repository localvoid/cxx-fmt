# Enable ExternalProject CMake module

if(DEFINED included_gtest_cmake)
    return()
else()
    set(included_gtest_cmake TRUE)
endif()

include(ExternalProject)

ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.6.0.zip
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/include CACHE PATH "" FORCE)

# Library
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a CACHE FILEPATH "" FORCE)
set(GTEST_MAIN_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a CACHE FILEPATH "" FORCE)

set(GTEST_LIBRARY gtest)
set(GTEST_MAIN_LIBRARY gtest_main)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
add_library(${GTEST_MAIN_LIBRARY} UNKNOWN IMPORTED)
set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARY_PATH})
set_property(TARGET ${GTEST_MAIN_LIBRARY} PROPERTY IMPORTED_LOCATION ${GTEST_MAIN_LIBRARY_PATH})
add_dependencies(${GTEST_LIBRARY} googletest)
add_dependencies(${GTEST_MAIN_LIBRARY} googletest)

set(GTEST_LIBRARIES gtest gtest_main)

mark_as_advanced(
    GTEST_INCLUDE_DIRS
    GTEST_LIBRARIES

    GTEST_LIBRARY_PATH
    GTEST_MAIN_LIBRARY_PATH
    GTEST_LIBRARY
    GTEST_MAIN_LIBRARY
)