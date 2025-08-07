/**
 * @file container.h
 * @brief FRESCO container interface
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#ifndef FRESCO_CONTAINER_H
#define FRESCO_CONTAINER_H

#include "fresco/fresco.h"
#include "compression.h"
#include <vector>

namespace fresco {

class Container {
public:
    Container() = default;
    ~Container() = default;

    fresco_error_t initialize(const ImageInfo& image_info,
                             const fresco_encode_params_t& params);

    fresco_error_t finalize(const std::vector<uint8_t>& compressed_data,
                           std::vector<uint8_t>& container_data);

    fresco_error_t parse(const uint8_t* input_data, size_t input_size,
                        ContainerInfo& container_info);

    fresco_error_t parse_header(const uint8_t* input_data, size_t input_size,
                               ContainerInfo& container_info);

    fresco_error_t extract_data(const uint8_t* input_data, size_t input_size,
                               std::vector<uint8_t>& compressed_data);
};

} // namespace fresco

#endif // FRESCO_CONTAINER_H
