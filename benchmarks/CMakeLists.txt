# Benchmarks directory CMakeLists.txt

# Benchmark executable
add_executable(fresco_benchmarks
    benchmark_main.cpp
    benchmark_compression.cpp
    benchmark_encoding.cpp
    benchmark_decoding.cpp
)

# Link libraries
target_link_libraries(fresco_benchmarks
    fresco
    ${CMAKE_THREAD_LIBS_INIT}
)

# Include directories
target_include_directories(fresco_benchmarks PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Install benchmark executable
install(TARGETS fresco_benchmarks
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
