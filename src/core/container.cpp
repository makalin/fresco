/**
 * @file container.cpp
 * @brief FRESCO container implementation
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include "container.h"
#include <vector>
#include <cstring>

namespace fresco {

fresco_error_t Container::initialize(const ImageInfo& image_info,
                                   const fresco_encode_params_t& params) {
    // TODO: Initialize container with image info
    return FRESCO_OK;
}

fresco_error_t Container::finalize(const std::vector<uint8_t>& compressed_data,
                                  std::vector<uint8_t>& container_data) {
    // TODO: Create final container with proper ISOBMFF structure
    // For now, just return the compressed data
    container_data = compressed_data;
    return FRESCO_OK;
}

fresco_error_t Container::parse(const uint8_t* input_data, size_t input_size,
                               ContainerInfo& container_info) {
    // TODO: Parse ISOBMFF container structure
    // For now, assume it's just raw image data
    container_info.width = 1920;  // Default values
    container_info.height = 1080;
    container_info.channels = 3;
    container_info.bit_depth = 8;
    container_info.colorspace = FRESCO_COLORSPACE_RGB;
    container_info.frame_count = 1;
    container_info.frame_rate = 0.0f;
    container_info.compressed_size = input_size;
    return FRESCO_OK;
}

fresco_error_t Container::parse_header(const uint8_t* input_data, size_t input_size,
                                      ContainerInfo& container_info) {
    // TODO: Parse only the container header
    return parse(input_data, input_size, container_info);
}

fresco_error_t Container::extract_data(const uint8_t* input_data, size_t input_size,
                                      std::vector<uint8_t>& compressed_data) {
    // TODO: Extract compressed data from container
    // For now, assume the entire input is compressed data
    compressed_data.assign(input_data, input_data + input_size);
    return FRESCO_OK;
}

} // namespace fresco
