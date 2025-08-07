/**
 * @file benchmark_encoding.cpp
 * @brief Encoding performance benchmarks
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void benchmark_encoding() {
    std::cout << "=== FRESCO Encoding Benchmark ===" << std::endl;
    
    // Test different image sizes
    std::vector<std::pair<size_t, size_t>> sizes = {
        {640, 480},   // VGA
        {1280, 720},  // HD
        {1920, 1080}, // Full HD
        {3840, 2160}  // 4K
    };
    
    for (const auto& [width, height] : sizes) {
        std::cout << "\nImage size: " << width << "x" << height << std::endl;
        
        const size_t channels = 3;
        const size_t data_size = width * height * channels;
        
        std::vector<uint8_t> test_data(data_size);
        
        // Fill with test pattern
        for (size_t i = 0; i < data_size; i += 3) {
            test_data[i] = (i / 3) % 256;     // R
            test_data[i + 1] = (i / 3) % 256; // G
            test_data[i + 2] = (i / 3) % 256; // B
        }
        
        // Test different effort levels
        std::vector<int> efforts = {1, 3, 5, 7, 9};
        
        for (int effort : efforts) {
            // Create encoder
            fresco_encoder_t* encoder = nullptr;
            fresco_encoder_create(&encoder);
            
            // Set parameters
            fresco_encode_params_t params = {};
            params.mode = FRESCO_COMPRESSION_LOSSY;
            params.quality = 85;
            params.effort = effort;
            params.max_threads = 0;
            
            fresco_encoder_set_params(encoder, &params);
            
            // Benchmark
            auto start = std::chrono::high_resolution_clock::now();
            
            uint8_t* output_data = nullptr;
            size_t output_size = 0;
            
            fresco_error_t result = fresco_encoder_encode(encoder, test_data.data(), test_data.size(),
                                                        &output_data, &output_size);
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            
            if (result == FRESCO_OK) {
                double speed_mbps = (data_size / 1024.0 / 1024.0) / (duration.count() / 1000.0);
                
                std::cout << "  Effort " << effort << ": " << duration.count() << " ms, " 
                         << speed_mbps << " MB/s" << std::endl;
                
                fresco_free(output_data);
            } else {
                std::cout << "  Effort " << effort << ": Failed - " << fresco_error_string(result) << std::endl;
            }
            
            fresco_encoder_destroy(encoder);
        }
    }
}

// Main function moved to benchmark_main.cpp
