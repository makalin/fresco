/**
 * @file decoder.cpp
 * @brief FRESCO decoder implementation
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include "decoder.h"
#include "compression.h"
#include "container.h"
#include "utils.h"

#include <memory>
#include <vector>
#include <cstring>

namespace fresco {

class DecoderImpl {
public:
    DecoderImpl() : params_(), container_(), compression_() {
        // Set default parameters
        params_.max_threads = 0; // Auto-detect
        params_.enable_progressive = 0;
        params_.enable_metadata = 0;
    }

    ~DecoderImpl() = default;

    fresco_error_t set_params(const fresco_decode_params_t* params) {
        if (!params) {
            return FRESCO_ERROR_INVALID_PARAMETER;
        }

        params_ = *params;
        return FRESCO_OK;
    }

    fresco_error_t decode(const uint8_t* input_data, size_t input_size,
                         uint8_t** output_data, size_t* output_size) {
        if (!input_data || !output_data || !output_size) {
            return FRESCO_ERROR_INVALID_PARAMETER;
        }

        try {
            // Parse FRESCO container
            ContainerInfo container_info;
            fresco_error_t result = container_.parse(input_data, input_size, container_info);
            if (result != FRESCO_OK) {
                return result;
            }

            // Extract compressed data
            std::vector<uint8_t> compressed_data;
            result = container_.extract_data(input_data, input_size, compressed_data);
            if (result != FRESCO_OK) {
                return result;
            }

            // Decompress data
            std::vector<uint8_t> decompressed_data;
            result = compression_.decompress(compressed_data, container_info, params_, decompressed_data);
            if (result != FRESCO_OK) {
                return result;
            }

            // Convert to output format
            std::vector<uint8_t> output_format_data;
            result = convert_to_output_format(decompressed_data, container_info, output_format_data);
            if (result != FRESCO_OK) {
                return result;
            }

            // Allocate output buffer
            *output_size = output_format_data.size();
            *output_data = static_cast<uint8_t*>(fresco_malloc(*output_size));
            if (!*output_data) {
                return FRESCO_ERROR_OUT_OF_MEMORY;
            }

            // Copy data to output buffer
            std::memcpy(*output_data, output_format_data.data(), *output_size);

            return FRESCO_OK;
        } catch (const std::exception& e) {
            return FRESCO_ERROR_DECODING_FAILED;
        }
    }

    fresco_error_t get_metadata(const uint8_t* input_data, size_t input_size,
                               fresco_metadata_t* metadata) {
        if (!input_data || !metadata) {
            return FRESCO_ERROR_INVALID_PARAMETER;
        }

        try {
            // Parse container header only
            ContainerInfo container_info;
            fresco_error_t result = container_.parse_header(input_data, input_size, container_info);
            if (result != FRESCO_OK) {
                return result;
            }

            // Fill metadata structure
            metadata->width = container_info.width;
            metadata->height = container_info.height;
            metadata->channels = container_info.channels;
            metadata->bit_depth = container_info.bit_depth;
            metadata->colorspace = container_info.colorspace;
            metadata->frame_count = container_info.frame_count;
            metadata->frame_rate = container_info.frame_rate;
            metadata->file_size = input_size;
            metadata->compressed_size = container_info.compressed_size;

            return FRESCO_OK;
        } catch (const std::exception& e) {
            return FRESCO_ERROR_DECODING_FAILED;
        }
    }

private:
    fresco_decode_params_t params_;
    Container container_;
    Compression compression_;
};

} // namespace fresco

// C API implementation

extern "C" {

fresco_error_t fresco_decoder_create(fresco_decoder_t** decoder) {
    if (!decoder) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    try {
        *decoder = reinterpret_cast<fresco_decoder_t*>(new fresco::DecoderImpl());
        return FRESCO_OK;
    } catch (const std::exception&) {
        return FRESCO_ERROR_OUT_OF_MEMORY;
    }
}

void fresco_decoder_destroy(fresco_decoder_t* decoder) {
    if (decoder) {
        delete reinterpret_cast<fresco::DecoderImpl*>(decoder);
    }
}

fresco_error_t fresco_decoder_set_params(fresco_decoder_t* decoder,
                                        const fresco_decode_params_t* params) {
    if (!decoder) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    auto* impl = reinterpret_cast<fresco::DecoderImpl*>(decoder);
    return impl->set_params(params);
}

fresco_error_t fresco_decoder_decode(fresco_decoder_t* decoder,
                                    const uint8_t* input_data,
                                    size_t input_size,
                                    uint8_t** output_data,
                                    size_t* output_size) {
    if (!decoder) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    auto* impl = reinterpret_cast<fresco::DecoderImpl*>(decoder);
    return impl->decode(input_data, input_size, output_data, output_size);
}

fresco_error_t fresco_get_metadata(const uint8_t* input_data,
                                  size_t input_size,
                                  fresco_metadata_t* metadata) {
    if (!input_data || !metadata) {
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    try {
        fresco::DecoderImpl decoder;
        return decoder.get_metadata(input_data, input_size, metadata);
    } catch (const std::exception&) {
        return FRESCO_ERROR_DECODING_FAILED;
    }
}

} // extern "C"
