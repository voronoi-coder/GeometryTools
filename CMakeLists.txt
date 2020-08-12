cmake_minimum_required(VERSION 3.6)
project(geometry_tools LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mason.cmake)

# configure optimization
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPTIMIZATION_FLAGS "-O0 -DDEBUG")
    message("-- Configuring debug build")
else()
    set(OPTIMIZATION_FLAGS "-O3 -DNDEBUG")
    message("-- Configuring release build")
endif()

# Enable extra warnings to adhere to https://github.com/mapbox/cpp/issues/37
set(DESIRED_WARNINGS "-Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable -Wshadow -Wfloat-equal -Weffc++")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Wmost")
endif()

# Note: -D_GLIBCXX_USE_CXX11_ABI=0 is needed to support mason packages that are precompiled libs
# Currently we only depend on a header only library, but this will help avoid issues when more libs are added via mason
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0 ${DESIRED_WARNINGS}")

mason_use(variant VERSION 1.1.6 HEADER_ONLY)
include_directories(SYSTEM ${MASON_PACKAGE_variant_INCLUDE_DIRS})
mason_use(geometry VERSION 1.0.0 HEADER_ONLY)
include_directories(SYSTEM ${MASON_PACKAGE_geometry_INCLUDE_DIRS})
mason_use(wagyu VERSION 0.5.0 HEADER_ONLY)
include_directories(SYSTEM ${MASON_PACKAGE_wagyu_INCLUDE_DIRS})
mason_use(jni.hpp VERSION 4.0.1 HEADER_ONLY)
include_directories(SYSTEM ${MASON_PACKAGE_jni.hpp_INCLUDE_DIRS})

add_library(geotools SHARED src/main.cpp src/wagyu.cpp)
target_include_directories(geotools PUBLIC ./include
                            PUBLIC ./openjdk)

# if(APPLE)
#   SET_TARGET_PROPERTIES(geotools PROPERTIES PREFIX "lib" SUFFIX ".jnilib")
# endif(APPLE)

add_executable(test test/test.cpp)

