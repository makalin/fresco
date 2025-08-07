/**
 * @file fresco.h
 * @brief Main header file for the FRESCO library
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#ifndef FRESCO_H
#define FRESCO_H

#include <stdint.h>
#include <stddef.h>

// Export declarations
#ifdef _WIN32
    #ifdef FRESCO_EXPORTS
        #define FRESCO_API __declspec(dllexport)
    #else
        #define FRESCO_API __declspec(dllimport)
    #endif
#else
    #define FRESCO_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief FRESCO library version information
 */
#define FRESCO_VERSION_MAJOR 0
#define FRESCO_VERSION_MINOR 1
#define FRESCO_VERSION_PATCH 0
#define FRESCO_VERSION_STRING "0.1.0"

/**
 * @brief Error codes returned by FRESCO functions
 */
typedef enum {
    FRESCO_OK = 0,                    ///< Operation completed successfully
    FRESCO_ERROR_INVALID_PARAMETER,   ///< Invalid parameter provided
    FRESCO_ERROR_OUT_OF_MEMORY,       ///< Memory allocation failed
    FRESCO_ERROR_IO,                  ///< Input/output error
    FRESCO_ERROR_UNSUPPORTED_FORMAT,  ///< Unsupported image format
    FRESCO_ERROR_CORRUPTED_DATA,      ///< Corrupted or invalid data
    FRESCO_ERROR_ENCODING_FAILED,     ///< Encoding operation failed
    FRESCO_ERROR_DECODING_FAILED,     ///< Decoding operation failed
    FRESCO_ERROR_NOT_IMPLEMENTED      ///< Feature not yet implemented
} fresco_error_t;

/**
 * @brief Image color space
 */
typedef enum {
    FRESCO_COLORSPACE_RGB = 0,        ///< RGB color space
    FRESCO_COLORSPACE_RGBA,           ///< RGBA color space with alpha
    FRESCO_COLORSPACE_YUV420,         ///< YUV 4:2:0 color space
    FRESCO_COLORSPACE_YUV422,         ///< YUV 4:2:2 color space
    FRESCO_COLORSPACE_YUV444,         ///< YUV 4:4:4 color space
    FRESCO_COLORSPACE_GRAY,           ///< Grayscale
    FRESCO_COLORSPACE_GRAYA           ///< Grayscale with alpha
} fresco_colorspace_t;

/**
 * @brief Compression mode
 */
typedef enum {
    FRESCO_COMPRESSION_LOSSY = 0,     ///< Lossy compression
    FRESCO_COMPRESSION_LOSSLESS       ///< Lossless compression
} fresco_compression_t;

/**
 * @brief Image metadata structure
 */
typedef struct {
    uint32_t width;                   ///< Image width in pixels
    uint32_t height;                  ///< Image height in pixels
    uint8_t channels;                 ///< Number of color channels
    uint8_t bit_depth;                ///< Bits per channel
    fresco_colorspace_t colorspace;   ///< Color space
    uint32_t frame_count;             ///< Number of frames (for animations)
    float frame_rate;                 ///< Frame rate for animations
    uint64_t file_size;               ///< Total file size in bytes
    uint64_t compressed_size;         ///< Compressed data size in bytes
} fresco_metadata_t;

/**
 * @brief Encoding parameters
 */
typedef struct {
    fresco_compression_t mode;        ///< Compression mode
    uint8_t quality;                  ///< Quality setting (1-100)
    uint8_t effort;                   ///< Encoding effort (1-10)
    uint32_t max_threads;             ///< Maximum number of threads
    uint32_t tile_size;               ///< Tile size for tiled encoding
    int enable_animation;             ///< Enable animation support
    int enable_3d;                    ///< Enable 3D model support
    int enable_vector;                ///< Enable vector graphics support
} fresco_encode_params_t;

/**
 * @brief Decoding parameters
 */
typedef struct {
    uint32_t max_threads;             ///< Maximum number of threads
    int enable_progressive;           ///< Enable progressive decoding
    int enable_metadata;              ///< Extract metadata only
} fresco_decode_params_t;

/**
 * @brief FRESCO encoder handle
 */
typedef struct fresco_encoder fresco_encoder_t;

/**
 * @brief FRESCO decoder handle
 */
typedef struct fresco_decoder fresco_decoder_t;

/**
 * @brief Get library version information
 * @param major Pointer to store major version
 * @param minor Pointer to store minor version
 * @param patch Pointer to store patch version
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_get_version(int* major, int* minor, int* patch);

/**
 * @brief Get version string
 * @return Version string (do not free)
 */
FRESCO_API const char* fresco_get_version_string(void);

/**
 * @brief Create a new encoder
 * @param encoder Pointer to store encoder handle
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_encoder_create(fresco_encoder_t** encoder);

/**
 * @brief Destroy an encoder
 * @param encoder Encoder handle to destroy
 */
FRESCO_API void fresco_encoder_destroy(fresco_encoder_t* encoder);

/**
 * @brief Set encoding parameters
 * @param encoder Encoder handle
 * @param params Encoding parameters
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_encoder_set_params(fresco_encoder_t* encoder,
                                        const fresco_encode_params_t* params);

/**
 * @brief Encode image data to FRESCO format
 * @param encoder Encoder handle
 * @param input_data Input image data
 * @param input_size Size of input data
 * @param output_data Pointer to store output data
 * @param output_size Pointer to store output size
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_encoder_encode(fresco_encoder_t* encoder,
                                    const uint8_t* input_data,
                                    size_t input_size,
                                    uint8_t** output_data,
                                    size_t* output_size);

/**
 * @brief Create a new decoder
 * @param decoder Pointer to store decoder handle
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_decoder_create(fresco_decoder_t** decoder);

/**
 * @brief Destroy a decoder
 * @param decoder Decoder handle to destroy
 */
FRESCO_API void fresco_decoder_destroy(fresco_decoder_t* decoder);

/**
 * @brief Set decoding parameters
 * @param decoder Decoder handle
 * @param params Decoding parameters
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_decoder_set_params(fresco_decoder_t* decoder,
                                        const fresco_decode_params_t* params);

/**
 * @brief Decode FRESCO data to image format
 * @param decoder Decoder handle
 * @param input_data Input FRESCO data
 * @param input_size Size of input data
 * @param output_data Pointer to store output data
 * @param output_size Pointer to store output size
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_decoder_decode(fresco_decoder_t* decoder,
                                    const uint8_t* input_data,
                                    size_t input_size,
                                    uint8_t** output_data,
                                    size_t* output_size);

/**
 * @brief Get metadata from FRESCO data
 * @param input_data Input FRESCO data
 * @param input_size Size of input data
 * @param metadata Pointer to store metadata
 * @return FRESCO_OK on success
 */
FRESCO_API fresco_error_t fresco_get_metadata(const uint8_t* input_data,
                                  size_t input_size,
                                  fresco_metadata_t* metadata);

/**
 * @brief Allocate memory using FRESCO's memory manager
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory or NULL on failure
 */
FRESCO_API void* fresco_malloc(size_t size);

/**
 * @brief Free memory allocated by FRESCO functions
 * @param ptr Pointer to free
 */
FRESCO_API void fresco_free(void* ptr);

/**
 * @brief Get error message for error code
 * @param error Error code
 * @return Error message string (do not free)
 */
FRESCO_API const char* fresco_error_string(fresco_error_t error);

#ifdef __cplusplus
}
#endif

#endif // FRESCO_H
