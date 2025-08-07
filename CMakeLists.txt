cmake_minimum_required(VERSION 3.15)
project(FRESCO VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTS "Build test suite" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)
option(BUILD_TOOLS "Build command-line tools" ON)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)
option(BUILD_NODEJS_BINDINGS "Build Node.js bindings" OFF)
option(USE_OPENMP "Use OpenMP for parallel processing" ON)
option(USE_AVX2 "Use AVX2 instructions" ON)
option(USE_NEON "Use ARM NEON instructions" OFF)

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

# Optional dependencies
find_package(OpenMP)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 QUIET)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Architecture-specific flags
if(USE_AVX2 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mfma")
endif()

if(USE_NEON AND CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=neon")
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()

if(BUILD_PYTHON_BINDINGS AND pybind11_FOUND)
    add_subdirectory(bindings/python)
endif()

if(BUILD_NODEJS_BINDINGS)
    add_subdirectory(bindings/nodejs)
endif()

# Install configuration
include(GNUInstallDirs)

# Install headers
install(DIRECTORY include/fresco
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

# Install libraries
install(TARGETS fresco
        EXPORT frescoTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fresco)

# Install tools
if(BUILD_TOOLS)
    install(TARGETS fresco-cli
            EXPORT frescoTargets
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

# Export targets
install(EXPORT frescoTargets
        FILE frescoTargets.cmake
        NAMESPACE fresco::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fresco)

# Create config file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/frescoConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/frescoConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fresco
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/frescoConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/frescoConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/frescoConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fresco
)

# Print configuration summary
message(STATUS "FRESCO Configuration:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Shared libraries: ${BUILD_SHARED_LIBS}")
message(STATUS "  Tests: ${BUILD_TESTS}")
message(STATUS "  Benchmarks: ${BUILD_BENCHMARKS}")
message(STATUS "  Tools: ${BUILD_TOOLS}")
message(STATUS "  Python bindings: ${BUILD_PYTHON_BINDINGS}")
message(STATUS "  Node.js bindings: ${BUILD_NODEJS_BINDINGS}")
message(STATUS "  OpenMP: ${OpenMP_CXX_FOUND}")
message(STATUS "  AVX2: ${USE_AVX2}")
message(STATUS "  NEON: ${USE_NEON}")
