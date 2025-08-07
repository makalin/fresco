/**
 * @file test_basic.cpp
 * @brief Basic unit tests for FRESCO library
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include <gtest/gtest.h>
#include <vector>
#include <cstring>

class FrescoBasicTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test image data (simple 8x8 RGB image)
        test_image_.resize(8 * 8 * 3);
        for (size_t i = 0; i < test_image_.size(); i += 3) {
            test_image_[i] = (i / 3) % 256;     // R
            test_image_[i + 1] = (i / 3) % 256; // G
            test_image_[i + 2] = (i / 3) % 256; // B
        }
    }

    std::vector<uint8_t> test_image_;
};

TEST_F(FrescoBasicTest, VersionInfo) {
    int major, minor, patch;
    fresco_error_t result = fresco_get_version(&major, &minor, &patch);
    
    EXPECT_EQ(result, FRESCO_OK);
    EXPECT_EQ(major, FRESCO_VERSION_MAJOR);
    EXPECT_EQ(minor, FRESCO_VERSION_MINOR);
    EXPECT_EQ(patch, FRESCO_VERSION_PATCH);
    
    const char* version_string = fresco_get_version_string();
    EXPECT_NE(version_string, nullptr);
    EXPECT_GT(strlen(version_string), 0);
}

TEST_F(FrescoBasicTest, ErrorStrings) {
    EXPECT_STREQ(fresco_error_string(FRESCO_OK), "Operation completed successfully");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_INVALID_PARAMETER), "Invalid parameter provided");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_OUT_OF_MEMORY), "Memory allocation failed");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_IO), "Input/output error");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_UNSUPPORTED_FORMAT), "Unsupported image format");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_CORRUPTED_DATA), "Corrupted or invalid data");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_ENCODING_FAILED), "Encoding operation failed");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_DECODING_FAILED), "Decoding operation failed");
    EXPECT_STREQ(fresco_error_string(FRESCO_ERROR_NOT_IMPLEMENTED), "Feature not yet implemented");
}

TEST_F(FrescoBasicTest, EncoderCreation) {
    fresco_encoder_t* encoder = nullptr;
    fresco_error_t result = fresco_encoder_create(&encoder);
    
    EXPECT_EQ(result, FRESCO_OK);
    EXPECT_NE(encoder, nullptr);
    
    fresco_encoder_destroy(encoder);
}

TEST_F(FrescoBasicTest, EncoderNullPointer) {
    fresco_error_t result = fresco_encoder_create(nullptr);
    EXPECT_EQ(result, FRESCO_ERROR_INVALID_PARAMETER);
}

TEST_F(FrescoBasicTest, EncoderParameters) {
    fresco_encoder_t* encoder = nullptr;
    fresco_error_t result = fresco_encoder_create(&encoder);
    ASSERT_EQ(result, FRESCO_OK);
    
    fresco_encode_params_t params = {};
    params.mode = FRESCO_COMPRESSION_LOSSY;
    params.quality = 85;
    params.effort = 5;
    params.max_threads = 4;
    params.tile_size = 256;
    
    result = fresco_encoder_set_params(encoder, &params);
    EXPECT_EQ(result, FRESCO_OK);
    
    fresco_encoder_destroy(encoder);
}

TEST_F(FrescoBasicTest, EncoderInvalidParameters) {
    fresco_encoder_t* encoder = nullptr;
    fresco_error_t result = fresco_encoder_create(&encoder);
    ASSERT_EQ(result, FRESCO_OK);
    
    fresco_encode_params_t params = {};
    params.quality = 0; // Invalid quality
    
    result = fresco_encoder_set_params(encoder, &params);
    EXPECT_EQ(result, FRESCO_ERROR_INVALID_PARAMETER);
    
    params.quality = 101; // Invalid quality
    result = fresco_encoder_set_params(encoder, &params);
    EXPECT_EQ(result, FRESCO_ERROR_INVALID_PARAMETER);
    
    fresco_encoder_destroy(encoder);
}

TEST_F(FrescoBasicTest, DecoderCreation) {
    fresco_decoder_t* decoder = nullptr;
    fresco_error_t result = fresco_decoder_create(&decoder);
    
    EXPECT_EQ(result, FRESCO_OK);
    EXPECT_NE(decoder, nullptr);
    
    fresco_decoder_destroy(decoder);
}

TEST_F(FrescoBasicTest, DecoderNullPointer) {
    fresco_error_t result = fresco_decoder_create(nullptr);
    EXPECT_EQ(result, FRESCO_ERROR_INVALID_PARAMETER);
}

TEST_F(FrescoBasicTest, DecoderParameters) {
    fresco_decoder_t* decoder = nullptr;
    fresco_error_t result = fresco_decoder_create(&decoder);
    ASSERT_EQ(result, FRESCO_OK);
    
    fresco_decode_params_t params = {};
    params.max_threads = 4;
    params.enable_progressive = 1;
    params.enable_metadata = 0;
    
    result = fresco_decoder_set_params(decoder, &params);
    EXPECT_EQ(result, FRESCO_OK);
    
    fresco_decoder_destroy(decoder);
}

TEST_F(FrescoBasicTest, MemoryAllocation) {
    void* ptr = malloc(1024);
    EXPECT_NE(ptr, nullptr);
    
    free(ptr);
}

TEST_F(FrescoBasicTest, MemoryAllocationZero) {
    void* ptr = malloc(0);
    // Should either return nullptr or a valid pointer
    free(ptr);
}

TEST_F(FrescoBasicTest, MemoryFreeNull) {
    // Should not crash
    fresco_free(nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
