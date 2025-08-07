/**
 * @file utils.cpp
 * @brief FRESCO utility functions
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include "utils.h"
#include <cstdlib>
#include <cstring>

namespace fresco {

void* fresco_malloc(size_t size) {
    return std::malloc(size);
}

void fresco_free(void* ptr) {
    std::free(ptr);
}

fresco_error_t parse_image_format(const uint8_t* input_data, size_t input_size,
                                 ImageInfo& image_info) {
    // TODO: Implement actual image format detection
    // For now, assume it's raw RGB data
    if (input_size % 3 != 0) {
        return FRESCO_ERROR_UNSUPPORTED_FORMAT;
    }
    
    // Assume square image for now
    size_t pixel_count = input_size / 3;
    size_t side_length = static_cast<size_t>(std::sqrt(pixel_count));
    
    image_info.width = side_length;
    image_info.height = side_length;
    image_info.channels = 3;
    image_info.bit_depth = 8;
    image_info.colorspace = FRESCO_COLORSPACE_RGB;
    
    return FRESCO_OK;
}

fresco_error_t convert_to_output_format(const std::vector<uint8_t>& decompressed_data,
                                       const ContainerInfo& container_info,
                                       std::vector<uint8_t>& output_format_data) {
    // TODO: Implement format conversion
    // For now, just return the decompressed data
    output_format_data = decompressed_data;
    return FRESCO_OK;
}

const char* fresco_error_string(fresco_error_t error) {
    switch (error) {
        case FRESCO_OK:
            return "Operation completed successfully";
        case FRESCO_ERROR_INVALID_PARAMETER:
            return "Invalid parameter provided";
        case FRESCO_ERROR_OUT_OF_MEMORY:
            return "Memory allocation failed";
        case FRESCO_ERROR_IO:
            return "Input/output error";
        case FRESCO_ERROR_UNSUPPORTED_FORMAT:
            return "Unsupported image format";
        case FRESCO_ERROR_CORRUPTED_DATA:
            return "Corrupted or invalid data";
        case FRESCO_ERROR_ENCODING_FAILED:
            return "Encoding operation failed";
        case FRESCO_ERROR_DECODING_FAILED:
            return "Decoding operation failed";
        case FRESCO_ERROR_NOT_IMPLEMENTED:
            return "Feature not yet implemented";
        default:
            return "Unknown error";
    }
}

fresco_error_t fresco_get_version(int* major, int* minor, int* patch) {
    if (!major || !minor || !patch) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }
    
    *major = FRESCO_VERSION_MAJOR;
    *minor = FRESCO_VERSION_MINOR;
    *patch = FRESCO_VERSION_PATCH;
    
    return FRESCO_OK;
}

const char* fresco_get_version_string(void) {
    return FRESCO_VERSION_STRING;
}

} // namespace fresco

// C API functions
extern "C" {

void* fresco_malloc(size_t size) {
    return fresco::fresco_malloc(size);
}

void fresco_free(void* ptr) {
    fresco::fresco_free(ptr);
}

const char* fresco_error_string(fresco_error_t error) {
    return fresco::fresco_error_string(error);
}

fresco_error_t fresco_get_version(int* major, int* minor, int* patch) {
    return fresco::fresco_get_version(major, minor, patch);
}

const char* fresco_get_version_string(void) {
    return fresco::fresco_get_version_string();
}

} // extern "C"
