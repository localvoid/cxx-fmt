# CMake Configuration
cmake_minimum_required(VERSION 2.8)
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

# Project Details
project(fmt)

include(cmake/ExternalGtest.cmake)


# Compilation Details
set(CXX_WARNING_FLAGS "-Wall -Wno-format-extra-args -Wformat-security -Wdelete-non-virtual-dtor -Wformat-nonliteral -Wformat=2 -Wpointer-arith -Wcast-align -Wshadow -Wsign-compare -Wno-variadic-macros -Wno-pmf-conversions")

set(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-rtti -pipe -std=gnu++11 ${CXX_WARNING_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG    "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -g  -DNDEBUG")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--hash-style=gnu")

include_directories(include ${GTEST_INCLUDE_DIRS})

add_library(fmtlib STATIC
  src/format.cpp
  src/itoa.cpp
  src/dtoa.cpp
  )

add_executable(fmt-debugger src/debugger.cpp)
add_executable(fmt src/format-util.cpp)
target_link_libraries(fmt fmtlib)
add_executable(itoa tests/itoa.cpp)
target_link_libraries(itoa fmtlib)
add_executable(test-fmt tests/fmt.cpp)
target_link_libraries(test-fmt fmtlib)

enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmarks)
