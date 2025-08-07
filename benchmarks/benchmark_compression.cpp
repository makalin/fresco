/**
 * @file benchmark_compression.cpp
 * @brief Compression performance benchmarks
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void benchmark_compression() {
    std::cout << "=== FRESCO Compression Benchmark ===" << std::endl;
    
    // Create test data
    const size_t width = 1920;
    const size_t height = 1080;
    const size_t channels = 3;
    const size_t data_size = width * height * channels;
    
    std::vector<uint8_t> test_data(data_size);
    
    // Fill with random data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    
    for (auto& pixel : test_data) {
        pixel = dis(gen);
    }
    
    std::cout << "Test image: " << width << "x" << height << "x" << channels << std::endl;
    std::cout << "Data size: " << data_size << " bytes" << std::endl;
    
    // Test different quality settings
    std::vector<int> qualities = {50, 75, 85, 95};
    
    for (int quality : qualities) {
        std::cout << "\nQuality: " << quality << std::endl;
        
        // Create encoder
        fresco_encoder_t* encoder = nullptr;
        fresco_encoder_create(&encoder);
        
        // Set parameters
        fresco_encode_params_t params = {};
        params.mode = FRESCO_COMPRESSION_LOSSY;
        params.quality = quality;
        params.effort = 5;
        params.max_threads = 0; // Auto-detect
        
        fresco_encoder_set_params(encoder, &params);
        
        // Benchmark encoding
        auto start = std::chrono::high_resolution_clock::now();
        
        uint8_t* output_data = nullptr;
        size_t output_size = 0;
        
        fresco_error_t result = fresco_encoder_encode(encoder, test_data.data(), test_data.size(),
                                                    &output_data, &output_size);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        if (result == FRESCO_OK) {
            double compression_ratio = static_cast<double>(data_size) / output_size;
            double speed_mbps = (data_size / 1024.0 / 1024.0) / (duration.count() / 1000.0);
            
            std::cout << "  Compression ratio: " << compression_ratio << ":1" << std::endl;
            std::cout << "  Compressed size: " << output_size << " bytes" << std::endl;
            std::cout << "  Encoding time: " << duration.count() << " ms" << std::endl;
            std::cout << "  Encoding speed: " << speed_mbps << " MB/s" << std::endl;
            
            fresco_free(output_data);
        } else {
            std::cout << "  Encoding failed: " << fresco_error_string(result) << std::endl;
        }
        
        fresco_encoder_destroy(encoder);
    }
}

// Main function moved to benchmark_main.cpp
