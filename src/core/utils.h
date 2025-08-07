/**
 * @file utils.h
 * @brief FRESCO utility functions
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#ifndef FRESCO_UTILS_H
#define FRESCO_UTILS_H

#include "fresco/fresco.h"
#include "compression.h"
#include <vector>

namespace fresco {

void* fresco_malloc(size_t size);
void fresco_free(void* ptr);

fresco_error_t parse_image_format(const uint8_t* input_data, size_t input_size,
                                 ImageInfo& image_info);

fresco_error_t convert_to_output_format(const std::vector<uint8_t>& decompressed_data,
                                       const ContainerInfo& container_info,
                                       std::vector<uint8_t>& output_format_data);

const char* fresco_error_string(fresco_error_t error);
fresco_error_t fresco_get_version(int* major, int* minor, int* patch);
const char* fresco_get_version_string(void);

} // namespace fresco

#endif // FRESCO_UTILS_H
