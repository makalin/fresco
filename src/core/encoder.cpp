/**
 * @file encoder.cpp
 * @brief FRESCO encoder implementation
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include "encoder.h"
#include "compression.h"
#include "container.h"
#include "utils.h"

#include <memory>
#include <vector>
#include <cstring>
#include <algorithm>

namespace fresco {

class EncoderImpl {
public:
    EncoderImpl() : params_(), container_(), compression_() {
        // Set default parameters
        params_.mode = FRESCO_COMPRESSION_LOSSY;
        params_.quality = 85;
        params_.effort = 5;
        params_.max_threads = 0; // Auto-detect
        params_.tile_size = 256;
        params_.enable_animation = 0;
        params_.enable_3d = 0;
        params_.enable_vector = 0;
    }

    ~EncoderImpl() = default;

    fresco_error_t set_params(const fresco_encode_params_t* params) {
        if (!params) {
            return FRESCO_ERROR_INVALID_PARAMETER;
        }

        // Validate parameters
        if (params->quality < 1 || params->quality > 100) {
            return FRESCO_ERROR_INVALID_PARAMETER;
        }
        if (params->effort < 1 || params->effort > 10) {
            return FRESCO_ERROR_INVALID_PARAMETER;
        }

        params_ = *params;
        return FRESCO_OK;
    }

    fresco_error_t encode(const uint8_t* input_data, size_t input_size,
                         uint8_t** output_data, size_t* output_size) {
        if (!input_data || !output_data || !output_size) {
            return FRESCO_ERROR_INVALID_PARAMETER;
        }

        try {
            // Parse input image format
            ImageInfo image_info;
            fresco_error_t result = parse_image_format(input_data, input_size, image_info);
            if (result != FRESCO_OK) {
                return result;
            }

            // Initialize container
            result = container_.initialize(image_info, params_);
            if (result != FRESCO_OK) {
                return result;
            }

            // Compress image data
            std::vector<uint8_t> compressed_data;
            result = compression_.compress(input_data, input_size, image_info, params_, compressed_data);
            if (result != FRESCO_OK) {
                return result;
            }

            // Create final container
            std::vector<uint8_t> container_data;
            result = container_.finalize(compressed_data, container_data);
            if (result != FRESCO_OK) {
                return result;
            }

            // Allocate output buffer
            *output_size = container_data.size();
            *output_data = static_cast<uint8_t*>(fresco_malloc(*output_size));
            if (!*output_data) {
                return FRESCO_ERROR_OUT_OF_MEMORY;
            }

            // Copy data to output buffer
            std::memcpy(*output_data, container_data.data(), *output_size);

            return FRESCO_OK;
        } catch (const std::exception& e) {
            return FRESCO_ERROR_ENCODING_FAILED;
        }
    }

private:
    fresco_encode_params_t params_;
    Container container_;
    Compression compression_;
};

} // namespace fresco

// C API implementation

extern "C" {

fresco_error_t fresco_encoder_create(fresco_encoder_t** encoder) {
    if (!encoder) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    try {
        *encoder = reinterpret_cast<fresco_encoder_t*>(new fresco::EncoderImpl());
        return FRESCO_OK;
    } catch (const std::exception&) {
        return FRESCO_ERROR_OUT_OF_MEMORY;
    }
}

void fresco_encoder_destroy(fresco_encoder_t* encoder) {
    if (encoder) {
        delete reinterpret_cast<fresco::EncoderImpl*>(encoder);
    }
}

fresco_error_t fresco_encoder_set_params(fresco_encoder_t* encoder,
                                        const fresco_encode_params_t* params) {
    if (!encoder) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    auto* impl = reinterpret_cast<fresco::EncoderImpl*>(encoder);
    return impl->set_params(params);
}

fresco_error_t fresco_encoder_encode(fresco_encoder_t* encoder,
                                    const uint8_t* input_data,
                                    size_t input_size,
                                    uint8_t** output_data,
                                    size_t* output_size) {
    if (!encoder) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    auto* impl = reinterpret_cast<fresco::EncoderImpl*>(encoder);
    return impl->encode(input_data, input_size, output_data, output_size);
}

} // extern "C"
