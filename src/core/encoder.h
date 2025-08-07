/**
 * @file encoder.h
 * @brief FRESCO encoder interface
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#ifndef FRESCO_ENCODER_H
#define FRESCO_ENCODER_H

#include "fresco/fresco.h"
#include "compression.h"
#include "container.h"
#include <vector>

namespace fresco {

class Encoder {
public:
    Encoder() = default;
    ~Encoder() = default;

    // This is a placeholder for the encoder interface
    // The actual implementation is in the EncoderImpl class
};

} // namespace fresco

#endif // FRESCO_ENCODER_H
