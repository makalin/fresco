/**
 * @file compression.h
 * @brief FRESCO compression interface
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#ifndef FRESCO_COMPRESSION_H
#define FRESCO_COMPRESSION_H

#include "fresco/fresco.h"
#include <vector>

namespace fresco {

struct ImageInfo {
    uint32_t width;
    uint32_t height;
    uint8_t channels;
    uint8_t bit_depth;
    fresco_colorspace_t colorspace;
};

struct ContainerInfo {
    uint32_t width;
    uint32_t height;
    uint8_t channels;
    uint8_t bit_depth;
    fresco_colorspace_t colorspace;
    uint32_t frame_count;
    float frame_rate;
    uint64_t compressed_size;
};

class Compression {
public:
    Compression() = default;
    ~Compression() = default;

    fresco_error_t compress(const uint8_t* input_data, size_t input_size,
                           const ImageInfo& image_info,
                           const fresco_encode_params_t& params,
                           std::vector<uint8_t>& compressed_data);

    fresco_error_t decompress(const std::vector<uint8_t>& compressed_data,
                             const ContainerInfo& container_info,
                             const fresco_decode_params_t& params,
                             std::vector<uint8_t>& decompressed_data);
};

} // namespace fresco

#endif // FRESCO_COMPRESSION_H
