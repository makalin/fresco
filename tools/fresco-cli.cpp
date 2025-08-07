/**
 * @file fresco-cli.cpp
 * @brief FRESCO command-line interface
 * @author Mehmet T. AKALIN
 * @date 2025
 * @license MIT
 */

#include "fresco/fresco.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

void print_usage(const char* program_name) {
    std::cout << "FRESCO: Fast, Rich, and Efficient Scalable Content Object\n";
    std::cout << "Usage: " << program_name << " <command> [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  encode <input> <output> [options]  Encode image to FRESCO format\n";
    std::cout << "  decode <input> <output> [options]  Decode FRESCO file to image\n";
    std::cout << "  convert <input> <output> [options] Convert between formats\n";
    std::cout << "  info <input>                       Show file information\n";
    std::cout << "  version                            Show version information\n\n";
    std::cout << "Options:\n";
    std::cout << "  --quality <1-100>                  Quality setting (default: 85)\n";
    std::cout << "  --effort <1-10>                    Encoding effort (default: 5)\n";
    std::cout << "  --lossless                         Use lossless compression\n";
    std::cout << "  --lossy                            Use lossy compression (default)\n";
    std::cout << "  --tile-size <size>                 Tile size for encoding\n";
    std::cout << "  --threads <count>                  Number of threads\n";
    std::cout << "  --help                             Show this help message\n";
}

void print_version() {
    int major, minor, patch;
    fresco_get_version(&major, &minor, &patch);
    std::cout << "FRESCO version " << major << "." << minor << "." << patch << "\n";
    std::cout << "Library: " << fresco_get_version_string() << "\n";
}

fresco_error_t read_file(const std::string& filename, std::vector<uint8_t>& data) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return FRESCO_ERROR_IO;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    data.resize(size);
    file.read(reinterpret_cast<char*>(data.data()), size);

    return file.good() ? FRESCO_OK : FRESCO_ERROR_IO;
}

fresco_error_t write_file(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return FRESCO_ERROR_IO;
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    return file.good() ? FRESCO_OK : FRESCO_ERROR_IO;
}

fresco_error_t encode_command(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Error: encode command requires input and output files\n";
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    std::string input_file = args[0];
    std::string output_file = args[1];

    // Parse options
    fresco_encode_params_t params = {};
    params.mode = FRESCO_COMPRESSION_LOSSY;
    params.quality = 85;
    params.effort = 5;
    params.max_threads = 0;
    params.tile_size = 256;

    for (size_t i = 2; i < args.size(); i++) {
        if (args[i] == "--quality" && i + 1 < args.size()) {
            params.quality = std::stoi(args[++i]);
        } else if (args[i] == "--effort" && i + 1 < args.size()) {
            params.effort = std::stoi(args[++i]);
        } else if (args[i] == "--lossless") {
            params.mode = FRESCO_COMPRESSION_LOSSLESS;
        } else if (args[i] == "--lossy") {
            params.mode = FRESCO_COMPRESSION_LOSSY;
        } else if (args[i] == "--tile-size" && i + 1 < args.size()) {
            params.tile_size = std::stoi(args[++i]);
        } else if (args[i] == "--threads" && i + 1 < args.size()) {
            params.max_threads = std::stoi(args[++i]);
        }
    }

    // Read input file
    std::vector<uint8_t> input_data;
    fresco_error_t result = read_file(input_file, input_data);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to read input file: " << fresco_error_string(result) << "\n";
        return result;
    }

    // Create encoder
    fresco_encoder_t* encoder = nullptr;
    result = fresco_encoder_create(&encoder);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to create encoder: " << fresco_error_string(result) << "\n";
        return result;
    }

    // Set parameters
    result = fresco_encoder_set_params(encoder, &params);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to set encoder parameters: " << fresco_error_string(result) << "\n";
        fresco_encoder_destroy(encoder);
        return result;
    }

    // Encode
    uint8_t* output_data = nullptr;
    size_t output_size = 0;
    result = fresco_encoder_encode(encoder, input_data.data(), input_data.size(),
                                 &output_data, &output_size);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to encode: " << fresco_error_string(result) << "\n";
        fresco_encoder_destroy(encoder);
        return result;
    }

    // Write output file
    std::vector<uint8_t> output_vector(output_data, output_data + output_size);
    result = write_file(output_file, output_vector);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to write output file: " << fresco_error_string(result) << "\n";
        fresco_free(output_data);
        fresco_encoder_destroy(encoder);
        return result;
    }

    // Cleanup
    fresco_free(output_data);
    fresco_encoder_destroy(encoder);

    std::cout << "Successfully encoded " << input_file << " to " << output_file << "\n";
    std::cout << "Input size: " << input_data.size() << " bytes\n";
    std::cout << "Output size: " << output_size << " bytes\n";
    std::cout << "Compression ratio: " << (double)input_data.size() / output_size << ":1\n";

    return FRESCO_OK;
}

fresco_error_t decode_command(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Error: decode command requires input and output files\n";
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    std::string input_file = args[0];
    std::string output_file = args[1];

    // Parse options
    fresco_decode_params_t params = {};
    params.max_threads = 0;

    for (size_t i = 2; i < args.size(); i++) {
        if (args[i] == "--threads" && i + 1 < args.size()) {
            params.max_threads = std::stoi(args[++i]);
        } else if (args[i] == "--progressive") {
            params.enable_progressive = 1;
        }
    }

    // Read input file
    std::vector<uint8_t> input_data;
    fresco_error_t result = read_file(input_file, input_data);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to read input file: " << fresco_error_string(result) << "\n";
        return result;
    }

    // Create decoder
    fresco_decoder_t* decoder = nullptr;
    result = fresco_decoder_create(&decoder);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to create decoder: " << fresco_error_string(result) << "\n";
        return result;
    }

    // Set parameters
    result = fresco_decoder_set_params(decoder, &params);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to set decoder parameters: " << fresco_error_string(result) << "\n";
        fresco_decoder_destroy(decoder);
        return result;
    }

    // Decode
    uint8_t* output_data = nullptr;
    size_t output_size = 0;
    result = fresco_decoder_decode(decoder, input_data.data(), input_data.size(),
                                 &output_data, &output_size);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to decode: " << fresco_error_string(result) << "\n";
        fresco_decoder_destroy(decoder);
        return result;
    }

    // Write output file
    std::vector<uint8_t> output_vector(output_data, output_data + output_size);
    result = write_file(output_file, output_vector);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to write output file: " << fresco_error_string(result) << "\n";
        fresco_free(output_data);
        fresco_decoder_destroy(decoder);
        return result;
    }

    // Cleanup
    fresco_free(output_data);
    fresco_decoder_destroy(decoder);

    std::cout << "Successfully decoded " << input_file << " to " << output_file << "\n";
    std::cout << "Input size: " << input_data.size() << " bytes\n";
    std::cout << "Output size: " << output_size << " bytes\n";

    return FRESCO_OK;
}

fresco_error_t info_command(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "Error: info command requires input file\n";
        return FRESCO_ERROR_INVALID_PARAMETER;
    }

    std::string input_file = args[0];

    // Read input file
    std::vector<uint8_t> input_data;
    fresco_error_t result = read_file(input_file, input_data);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to read input file: " << fresco_error_string(result) << "\n";
        return result;
    }

    // Get metadata
    fresco_metadata_t metadata;
    result = fresco_get_metadata(input_data.data(), input_data.size(), &metadata);
    if (result != FRESCO_OK) {
        std::cerr << "Error: Failed to get metadata: " << fresco_error_string(result) << "\n";
        return result;
    }

    // Print information
    std::cout << "File: " << input_file << "\n";
    std::cout << "Format: FRESCO\n";
    std::cout << "Dimensions: " << metadata.width << "x" << metadata.height << "\n";
    std::cout << "Channels: " << (int)metadata.channels << "\n";
    std::cout << "Bit depth: " << (int)metadata.bit_depth << "\n";
    std::cout << "Color space: " << (int)metadata.colorspace << "\n";
    std::cout << "Frames: " << metadata.frame_count << "\n";
    if (metadata.frame_count > 1) {
        std::cout << "Frame rate: " << metadata.frame_rate << " fps\n";
    }
    std::cout << "File size: " << metadata.file_size << " bytes\n";
    std::cout << "Compressed size: " << metadata.compressed_size << " bytes\n";
    if (metadata.compressed_size > 0) {
        std::cout << "Compression ratio: " << (double)metadata.file_size / metadata.compressed_size << ":1\n";
    }

    return FRESCO_OK;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    std::string command = argv[1];

    if (command == "version") {
        print_version();
        return 0;
    }

    if (command == "help" || command == "--help") {
        print_usage(argv[0]);
        return 0;
    }

    // Parse remaining arguments
    std::vector<std::string> args;
    for (int i = 2; i < argc; i++) {
        args.push_back(argv[i]);
    }

    fresco_error_t result = FRESCO_ERROR_INVALID_PARAMETER;

    if (command == "encode") {
        result = encode_command(args);
    } else if (command == "decode") {
        result = decode_command(args);
    } else if (command == "convert") {
        // For now, convert is the same as encode
        result = encode_command(args);
    } else if (command == "info") {
        result = info_command(args);
    } else {
        std::cerr << "Error: Unknown command '" << command << "'\n";
        print_usage(argv[0]);
        return 1;
    }

    if (result != FRESCO_OK) {
        std::cerr << "Error: " << fresco_error_string(result) << "\n";
        return 1;
    }

    return 0;
}
