/**
 * @file benchmark_main.cpp
 * @brief Main entry point for FRESCO benchmarks
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include <iostream>

// Forward declarations
void benchmark_compression();
void benchmark_encoding();
void benchmark_decoding();

int main() {
    std::cout << "FRESCO Performance Benchmarks\n";
    std::cout << "=============================\n\n";
    
    benchmark_compression();
    std::cout << "\n";
    
    benchmark_encoding();
    std::cout << "\n";
    
    benchmark_decoding();
    std::cout << "\n";
    
    std::cout << "All benchmarks completed.\n";
    return 0;
}
