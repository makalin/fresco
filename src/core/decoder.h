/**
 * @file decoder.h
 * @brief FRESCO decoder interface
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#ifndef FRESCO_DECODER_H
#define FRESCO_DECODER_H

#include "fresco/fresco.h"
#include "compression.h"
#include "container.h"
#include <vector>

namespace fresco {

class Decoder {
public:
    Decoder() = default;
    ~Decoder() = default;

    // This is a placeholder for the decoder interface
    // The actual implementation is in the DecoderImpl class
};

} // namespace fresco

#endif // FRESCO_DECODER_H
