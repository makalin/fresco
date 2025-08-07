# FRESCO API Reference

## Version 0.1.0

This document provides a comprehensive reference for the FRESCO library API.

## Table of Contents

- [C API](#c-api)
- [Python API](#python-api)
- [Error Handling](#error-handling)
- [Data Structures](#data-structures)
- [Examples](#examples)

## C API

### Core Functions

#### Version Information

```c
fresco_error_t fresco_get_version(int* major, int* minor, int* patch);
const char* fresco_get_version_string(void);
```

Get library version information.

**Parameters:**
- `major`, `minor`, `patch`: Pointers to store version components
- Returns: Version string (do not free)

**Returns:**
- `FRESCO_OK` on success
- `FRESCO_ERROR_INVALID_PARAMETER` if pointers are null

#### Memory Management

```c
void* fresco_malloc(size_t size);
void fresco_free(void* ptr);
```

Memory allocation functions.

**Parameters:**
- `size`: Number of bytes to allocate
- `ptr`: Pointer to free

**Returns:**
- Allocated memory pointer or NULL on failure

### Encoder API

#### Creating and Destroying Encoders

```c
fresco_error_t fresco_encoder_create(fresco_encoder_t** encoder);
void fresco_encoder_destroy(fresco_encoder_t* encoder);
```

Create and destroy encoder instances.

**Parameters:**
- `encoder`: Pointer to store encoder handle

**Returns:**
- `FRESCO_OK` on success
- `FRESCO_ERROR_INVALID_PARAMETER` if encoder pointer is null
- `FRESCO_ERROR_OUT_OF_MEMORY` if allocation fails

#### Setting Parameters

```c
fresco_error_t fresco_encoder_set_params(fresco_encoder_t* encoder,
                                        const fresco_encode_params_t* params);
```

Set encoding parameters.

**Parameters:**
- `encoder`: Encoder handle
- `params`: Encoding parameters structure

**Returns:**
- `FRESCO_OK` on success
- `FRESCO_ERROR_INVALID_PARAMETER` if parameters are invalid

#### Encoding

```c
fresco_error_t fresco_encoder_encode(fresco_encoder_t* encoder,
                                    const uint8_t* input_data,
                                    size_t input_size,
                                    uint8_t** output_data,
                                    size_t* output_size);
```

Encode image data to FRESCO format.

**Parameters:**
- `encoder`: Encoder handle
- `input_data`: Input image data
- `input_size`: Size of input data
- `output_data`: Pointer to store output data
- `output_size`: Pointer to store output size

**Returns:**
- `FRESCO_OK` on success
- Various error codes on failure

### Decoder API

#### Creating and Destroying Decoders

```c
fresco_error_t fresco_decoder_create(fresco_decoder_t** decoder);
void fresco_decoder_destroy(fresco_decoder_t* decoder);
```

Create and destroy decoder instances.

**Parameters:**
- `decoder`: Pointer to store decoder handle

**Returns:**
- `FRESCO_OK` on success
- `FRESCO_ERROR_INVALID_PARAMETER` if decoder pointer is null
- `FRESCO_ERROR_OUT_OF_MEMORY` if allocation fails

#### Setting Parameters

```c
fresco_error_t fresco_decoder_set_params(fresco_decoder_t* decoder,
                                        const fresco_decode_params_t* params);
```

Set decoding parameters.

**Parameters:**
- `decoder`: Decoder handle
- `params`: Decoding parameters structure

**Returns:**
- `FRESCO_OK` on success
- `FRESCO_ERROR_INVALID_PARAMETER` if parameters are invalid

#### Decoding

```c
fresco_error_t fresco_decoder_decode(fresco_decoder_t* decoder,
                                    const uint8_t* input_data,
                                    size_t input_size,
                                    uint8_t** output_data,
                                    size_t* output_size);
```

Decode FRESCO data to image format.

**Parameters:**
- `decoder`: Decoder handle
- `input_data`: Input FRESCO data
- `input_size`: Size of input data
- `output_data`: Pointer to store output data
- `output_size`: Pointer to store output size

**Returns:**
- `FRESCO_OK` on success
- Various error codes on failure

#### Metadata Extraction

```c
fresco_error_t fresco_get_metadata(const uint8_t* input_data,
                                  size_t input_size,
                                  fresco_metadata_t* metadata);
```

Extract metadata from FRESCO data.

**Parameters:**
- `input_data`: Input FRESCO data
- `input_size`: Size of input data
- `metadata`: Pointer to store metadata

**Returns:**
- `FRESCO_OK` on success
- Various error codes on failure

### Error Handling

```c
const char* fresco_error_string(fresco_error_t error);
```

Get error message for error code.

**Parameters:**
- `error`: Error code

**Returns:**
- Error message string (do not free)

## Python API

### FrescoEncoder Class

```python
class FrescoEncoder:
    def __init__(self, **kwargs):
        """Initialize encoder with optional parameters."""
        
    def set_params(self, mode="lossy", quality=85, effort=5, 
                   max_threads=0, tile_size=256, enable_animation=False,
                   enable_3d=False, enable_vector=False):
        """Set encoding parameters."""
        
    def encode(self, data, format=None):
        """Encode image data to FRESCO format."""
        
    def encode_file(self, input_path, output_path):
        """Encode an image file to FRESCO format."""
        
    def close(self):
        """Close the encoder and free resources."""
```

### FrescoDecoder Class

```python
class FrescoDecoder:
    def __init__(self, **kwargs):
        """Initialize decoder with optional parameters."""
        
    def set_params(self, max_threads=0, enable_progressive=False,
                   enable_metadata=False):
        """Set decoding parameters."""
        
    def decode(self, data):
        """Decode FRESCO data to image format."""
        
    def decode_file(self, input_path, output_path):
        """Decode a FRESCO file to image format."""
        
    def close(self):
        """Close the decoder and free resources."""
```

### Convenience Functions

```python
def encode(data, output_path=None, **kwargs):
    """Convenience function to encode image data."""
    
def decode(data, output_path=None, **kwargs):
    """Convenience function to decode FRESCO data."""
    
def get_metadata(data):
    """Extract metadata from FRESCO data."""
    
def get_version():
    """Get library version information."""
```

## Data Structures

### C Structures

#### fresco_metadata_t

```c
typedef struct {
    uint32_t width;                   // Image width in pixels
    uint32_t height;                  // Image height in pixels
    uint8_t channels;                 // Number of color channels
    uint8_t bit_depth;                // Bits per channel
    fresco_colorspace_t colorspace;   // Color space
    uint32_t frame_count;             // Number of frames (for animations)
    float frame_rate;                 // Frame rate for animations
    uint64_t file_size;               // Total file size in bytes
    uint64_t compressed_size;         // Compressed data size in bytes
} fresco_metadata_t;
```

#### fresco_encode_params_t

```c
typedef struct {
    fresco_compression_t mode;        // Compression mode
    uint8_t quality;                  // Quality setting (1-100)
    uint8_t effort;                   // Encoding effort (1-10)
    uint32_t max_threads;             // Maximum number of threads
    uint32_t tile_size;               // Tile size for tiled encoding
    int enable_animation;             // Enable animation support
    int enable_3d;                    // Enable 3D model support
    int enable_vector;                // Enable vector graphics support
} fresco_encode_params_t;
```

#### fresco_decode_params_t

```c
typedef struct {
    uint32_t max_threads;             // Maximum number of threads
    int enable_progressive;           // Enable progressive decoding
    int enable_metadata;              // Extract metadata only
} fresco_decode_params_t;
```

### Enumerations

#### fresco_error_t

```c
typedef enum {
    FRESCO_OK = 0,                    // Operation completed successfully
    FRESCO_ERROR_INVALID_PARAMETER,   // Invalid parameter provided
    FRESCO_ERROR_OUT_OF_MEMORY,       // Memory allocation failed
    FRESCO_ERROR_IO,                  // Input/output error
    FRESCO_ERROR_UNSUPPORTED_FORMAT,  // Unsupported image format
    FRESCO_ERROR_CORRUPTED_DATA,      // Corrupted or invalid data
    FRESCO_ERROR_ENCODING_FAILED,     // Encoding operation failed
    FRESCO_ERROR_DECODING_FAILED,     // Decoding operation failed
    FRESCO_ERROR_NOT_IMPLEMENTED      // Feature not yet implemented
} fresco_error_t;
```

#### fresco_compression_t

```c
typedef enum {
    FRESCO_COMPRESSION_LOSSY = 0,     // Lossy compression
    FRESCO_COMPRESSION_LOSSLESS       // Lossless compression
} fresco_compression_t;
```

#### fresco_colorspace_t

```c
typedef enum {
    FRESCO_COLORSPACE_RGB = 0,        // RGB color space
    FRESCO_COLORSPACE_RGBA,           // RGBA color space with alpha
    FRESCO_COLORSPACE_YUV420,         // YUV 4:2:0 color space
    FRESCO_COLORSPACE_YUV422,         // YUV 4:2:2 color space
    FRESCO_COLORSPACE_YUV444,         // YUV 4:4:4 color space
    FRESCO_COLORSPACE_GRAY,           // Grayscale
    FRESCO_COLORSPACE_GRAYA           // Grayscale with alpha
} fresco_colorspace_t;
```

## Examples

### C Example

```c
#include "fresco/fresco.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create encoder
    fresco_encoder_t* encoder = NULL;
    fresco_error_t result = fresco_encoder_create(&encoder);
    if (result != FRESCO_OK) {
        fprintf(stderr, "Failed to create encoder: %s\n", 
                fresco_error_string(result));
        return 1;
    }
    
    // Set parameters
    fresco_encode_params_t params = {
        .mode = FRESCO_COMPRESSION_LOSSY,
        .quality = 85,
        .effort = 5,
        .max_threads = 4
    };
    
    result = fresco_encoder_set_params(encoder, &params);
    if (result != FRESCO_OK) {
        fprintf(stderr, "Failed to set parameters: %s\n", 
                fresco_error_string(result));
        fresco_encoder_destroy(encoder);
        return 1;
    }
    
    // Encode image data
    uint8_t* output_data = NULL;
    size_t output_size = 0;
    
    // ... load image data ...
    uint8_t* input_data = /* your image data */;
    size_t input_size = /* image data size */;
    
    result = fresco_encoder_encode(encoder, input_data, input_size,
                                 &output_data, &output_size);
    if (result != FRESCO_OK) {
        fprintf(stderr, "Failed to encode: %s\n", fresco_error_string(result));
        fresco_encoder_destroy(encoder);
        return 1;
    }
    
    // Save encoded data
    FILE* f = fopen("output.fresco", "wb");
    if (f) {
        fwrite(output_data, 1, output_size, f);
        fclose(f);
    }
    
    // Cleanup
    fresco_free(output_data);
    fresco_encoder_destroy(encoder);
    
    return 0;
}
```

### Python Example

```python
import fresco
import numpy as np
from PIL import Image

# Create test image
image = np.random.randint(0, 255, (256, 256, 3), dtype=np.uint8)

# Encode
with fresco.FrescoEncoder(quality=85, effort=5) as encoder:
    encoded_data = encoder.encode(image)
    
    # Save encoded data
    with open("output.fresco", "wb") as f:
        f.write(encoded_data)

# Decode
with fresco.FrescoDecoder() as decoder:
    with open("output.fresco", "rb") as f:
        encoded_data = f.read()
    
    decoded_data = decoder.decode(encoded_data)
    decoded_image = np.frombuffer(decoded_data, dtype=np.uint8)
    decoded_image = decoded_image.reshape(256, 256, 3)
    
    # Save decoded image
    Image.fromarray(decoded_image).save("decoded.png")

# Get metadata
metadata = fresco.get_metadata(encoded_data)
print(f"Image: {metadata.width}x{metadata.height}")
print(f"Channels: {metadata.channels}")
print(f"Compression ratio: {metadata.file_size / metadata.compressed_size:.2f}:1")
```

## Error Handling

### C Error Handling

```c
fresco_error_t result = some_fresco_function();
if (result != FRESCO_OK) {
    fprintf(stderr, "Error: %s\n", fresco_error_string(result));
    // Handle error appropriately
}
```

### Python Error Handling

```python
try:
    with fresco.FrescoEncoder() as encoder:
        encoded_data = encoder.encode(image_data)
except RuntimeError as e:
    print(f"Encoding failed: {e}")
    # Handle error appropriately
```

## Performance Considerations

### Threading

- Set `max_threads` to 0 for auto-detection
- Use appropriate thread count for your system
- Consider memory usage with high thread counts

### Memory Management

- Always free allocated memory in C
- Use context managers in Python
- Monitor memory usage for large images

### Quality vs Speed

- Higher quality settings increase encoding time
- Higher effort settings improve compression but slow encoding
- Balance quality, speed, and file size for your use case

## Platform Support

### Supported Platforms

- Linux (x86_64, ARM64)
- macOS (x86_64, ARM64)
- Windows (x86_64)

### Compiler Support

- GCC 7+
- Clang 6+
- MSVC 2017+

### Python Support

- Python 3.8+
- NumPy 1.21+
- Pillow 9.0+

---

For more information, see the [FRESCO Documentation](https://fresco-format.github.io).
