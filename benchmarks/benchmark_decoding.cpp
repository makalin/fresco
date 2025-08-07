/**
 * @file benchmark_decoding.cpp
 * @brief Decoding performance benchmarks
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void benchmark_decoding() {
    std::cout << "=== FRESCO Decoding Benchmark ===" << std::endl;
    
    // Create test data
    const size_t width = 1920;
    const size_t height = 1080;
    const size_t channels = 3;
    const size_t data_size = width * height * channels;
    
    std::vector<uint8_t> test_data(data_size);
    
    // Fill with test pattern
    for (size_t i = 0; i < data_size; i += 3) {
        test_data[i] = (i / 3) % 256;     // R
        test_data[i + 1] = (i / 3) % 256; // G
        test_data[i + 2] = (i / 3) % 256; // B
    }
    
    // Encode test data first
    fresco_encoder_t* encoder = nullptr;
    fresco_encoder_create(&encoder);
    
    fresco_encode_params_t encode_params = {};
    encode_params.mode = FRESCO_COMPRESSION_LOSSY;
    encode_params.quality = 85;
    encode_params.effort = 5;
    encode_params.max_threads = 0;
    
    fresco_encoder_set_params(encoder, &encode_params);
    
    uint8_t* encoded_data = nullptr;
    size_t encoded_size = 0;
    
    fresco_error_t result = fresco_encoder_encode(encoder, test_data.data(), test_data.size(),
                                                &encoded_data, &encoded_size);
    
    if (result != FRESCO_OK) {
        std::cout << "Failed to encode test data: " << fresco_error_string(result) << std::endl;
        fresco_encoder_destroy(encoder);
        return;
    }
    
    std::cout << "Encoded test data: " << encoded_size << " bytes" << std::endl;
    
    fresco_encoder_destroy(encoder);
    
    // Test decoding with different thread counts
    std::vector<int> thread_counts = {1, 2, 4, 8, 0}; // 0 = auto-detect
    
    for (int threads : thread_counts) {
        std::string thread_desc = (threads == 0) ? "auto" : std::to_string(threads);
        std::cout << "\nThreads: " << thread_desc << std::endl;
        
        // Create decoder
        fresco_decoder_t* decoder = nullptr;
        fresco_decoder_create(&decoder);
        
        // Set parameters
        fresco_decode_params_t decode_params = {};
        decode_params.max_threads = threads;
        decode_params.enable_progressive = 0;
        decode_params.enable_metadata = 0;
        
        fresco_decoder_set_params(decoder, &decode_params);
        
        // Benchmark decoding
        auto start = std::chrono::high_resolution_clock::now();
        
        uint8_t* decoded_data = nullptr;
        size_t decoded_size = 0;
        
        result = fresco_decoder_decode(decoder, encoded_data, encoded_size,
                                     &decoded_data, &decoded_size);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        if (result == FRESCO_OK) {
            double speed_mbps = (decoded_size / 1024.0 / 1024.0) / (duration.count() / 1000.0);
            
            std::cout << "  Decoding time: " << duration.count() << " ms" << std::endl;
            std::cout << "  Decoding speed: " << speed_mbps << " MB/s" << std::endl;
            std::cout << "  Decoded size: " << decoded_size << " bytes" << std::endl;
            
            fresco_free(decoded_data);
        } else {
            std::cout << "  Decoding failed: " << fresco_error_string(result) << std::endl;
        }
        
        fresco_decoder_destroy(decoder);
    }
    
    fresco_free(encoded_data);
}

// Main function moved to benchmark_main.cpp
