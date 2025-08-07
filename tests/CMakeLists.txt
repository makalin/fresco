# Tests directory CMakeLists.txt

# Find Google Test
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    # Try to find GTest using pkg-config
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GTEST QUIET gtest gtest_main)
    endif()
endif()

if(NOT GTest_FOUND AND NOT GTEST_FOUND)
    message(WARNING "Google Test not found. Tests will be disabled.")
    return()
endif()

# Test executable
add_executable(fresco_tests
    test_basic.cpp
)

# Link libraries
target_link_libraries(fresco_tests
    fresco
    ${GTEST_LIBRARIES}
)

# Include directories
target_include_directories(fresco_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${GTEST_INCLUDE_DIRS}
)

# Add tests
add_test(NAME BasicTests COMMAND fresco_tests)

# Enable CTest integration
enable_testing()
