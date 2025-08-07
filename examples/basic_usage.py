#!/usr/bin/env python3
"""
Basic usage example for FRESCO Python bindings

This example demonstrates how to use the FRESCO library to encode and decode images.
"""

import numpy as np
from PIL import Image
import fresco

def create_test_image(width=256, height=256):
    """Create a simple test image."""
    # Create a gradient image
    x = np.linspace(0, 1, width)
    y = np.linspace(0, 1, height)
    X, Y = np.meshgrid(x, y)
    
    # Create RGB channels
    r = (X * 255).astype(np.uint8)
    g = (Y * 255).astype(np.uint8)
    b = ((X + Y) * 127).astype(np.uint8)
    
    # Combine channels
    image = np.stack([r, g, b], axis=2)
    return image

def encode_example():
    """Example of encoding an image to FRESCO format."""
    print("=== FRESCO Encoding Example ===")
    
    # Create a test image
    image = create_test_image(512, 512)
    print(f"Created test image: {image.shape}")
    
    # Convert to PIL Image for saving
    pil_image = Image.fromarray(image)
    pil_image.save("test_input.png")
    print("Saved test image as test_input.png")
    
    # Encode with different quality settings
    qualities = [50, 75, 90]
    
    for quality in qualities:
        print(f"\nEncoding with quality {quality}...")
        
        # Create encoder
        encoder = fresco.FrescoEncoder(
            mode="lossy",
            quality=quality,
            effort=5,
            max_threads=4
        )
        
        # Encode image
        encoded_data = encoder.encode(image)
        
        # Save encoded data
        output_filename = f"test_output_q{quality}.fresco"
        with open(output_filename, 'wb') as f:
            f.write(encoded_data)
        
        # Calculate compression ratio
        original_size = image.nbytes
        compressed_size = len(encoded_data)
        compression_ratio = original_size / compressed_size
        
        print(f"  Original size: {original_size:,} bytes")
        print(f"  Compressed size: {compressed_size:,} bytes")
        print(f"  Compression ratio: {compression_ratio:.2f}:1")
        print(f"  Saved as: {output_filename}")
        
        encoder.close()

def decode_example():
    """Example of decoding a FRESCO file."""
    print("\n=== FRESCO Decoding Example ===")
    
    # Decode the highest quality file
    input_filename = "test_output_q90.fresco"
    
    try:
        with open(input_filename, 'rb') as f:
            encoded_data = f.read()
        
        print(f"Loading encoded data from {input_filename}")
        print(f"Encoded data size: {len(encoded_data):,} bytes")
        
        # Get metadata
        metadata = fresco.get_metadata(encoded_data)
        print(f"Image dimensions: {metadata.width}x{metadata.height}")
        print(f"Channels: {metadata.channels}")
        print(f"Bit depth: {metadata.bit_depth}")
        
        # Create decoder
        decoder = fresco.FrescoDecoder(
            max_threads=4,
            enable_progressive=True
        )
        
        # Decode image
        print("Decoding image...")
        decoded_data = decoder.decode(encoded_data)
        
        # Convert to numpy array
        decoded_image = np.frombuffer(decoded_data, dtype=np.uint8)
        decoded_image = decoded_image.reshape(metadata.height, metadata.width, metadata.channels)
        
        # Save decoded image
        pil_image = Image.fromarray(decoded_image)
        pil_image.save("test_decoded.png")
        print("Saved decoded image as test_decoded.png")
        
        decoder.close()
        
    except FileNotFoundError:
        print(f"Error: {input_filename} not found. Run encode_example() first.")

def lossless_example():
    """Example of lossless encoding."""
    print("\n=== FRESCO Lossless Encoding Example ===")
    
    # Create a test image with sharp edges (good for lossless)
    image = create_test_image(256, 256)
    
    # Add some text-like features
    image[100:150, 100:150] = [255, 0, 0]  # Red square
    image[50:100, 200:250] = [0, 255, 0]   # Green square
    
    print("Created test image with sharp features")
    
    # Save original
    pil_image = Image.fromarray(image)
    pil_image.save("test_lossless_input.png")
    
    # Encode losslessly
    encoder = fresco.FrescoEncoder(
        mode="lossless",
        effort=8,
        max_threads=4
    )
    
    encoded_data = encoder.encode(image)
    
    # Save encoded data
    with open("test_lossless.fresco", 'wb') as f:
        f.write(encoded_data)
    
    # Calculate compression ratio
    original_size = image.nbytes
    compressed_size = len(encoded_data)
    compression_ratio = original_size / compressed_size
    
    print(f"Original size: {original_size:,} bytes")
    print(f"Compressed size: {compressed_size:,} bytes")
    print(f"Compression ratio: {compression_ratio:.2f}:1")
    print("Saved as: test_lossless.fresco")
    
    # Decode and verify losslessness
    decoder = fresco.FrescoDecoder()
    decoded_data = decoder.decode(encoded_data)
    decoded_image = np.frombuffer(decoded_data, dtype=np.uint8)
    decoded_image = decoded_image.reshape(image.shape)
    
    # Check if images are identical
    is_identical = np.array_equal(image, decoded_image)
    print(f"Lossless verification: {'PASS' if is_identical else 'FAIL'}")
    
    encoder.close()
    decoder.close()

def metadata_example():
    """Example of extracting metadata from FRESCO files."""
    print("\n=== FRESCO Metadata Example ===")
    
    # Try to get metadata from all generated files
    files_to_check = [
        "test_output_q50.fresco",
        "test_output_q75.fresco", 
        "test_output_q90.fresco",
        "test_lossless.fresco"
    ]
    
    for filename in files_to_check:
        try:
            with open(filename, 'rb') as f:
                data = f.read()
            
            metadata = fresco.get_metadata(data)
            
            print(f"\n{filename}:")
            print(f"  Dimensions: {metadata.width}x{metadata.height}")
            print(f"  Channels: {metadata.channels}")
            print(f"  Bit depth: {metadata.bit_depth}")
            print(f"  Color space: {metadata.colorspace}")
            print(f"  File size: {metadata.file_size:,} bytes")
            print(f"  Compressed size: {metadata.compressed_size:,} bytes")
            
            if metadata.compressed_size > 0:
                ratio = metadata.file_size / metadata.compressed_size
                print(f"  Compression ratio: {ratio:.2f}:1")
                
        except FileNotFoundError:
            print(f"{filename}: Not found")
        except Exception as e:
            print(f"{filename}: Error - {e}")

def main():
    """Run all examples."""
    print("FRESCO Python Bindings - Basic Usage Examples")
    print("=" * 50)
    
    try:
        # Show version info
        major, minor, patch = fresco.get_version()
        print(f"FRESCO version: {major}.{minor}.{patch}")
        print()
        
        # Run examples
        encode_example()
        decode_example()
        lossless_example()
        metadata_example()
        
        print("\n" + "=" * 50)
        print("Examples completed successfully!")
        print("Generated files:")
        print("  - test_input.png (original image)")
        print("  - test_output_q*.fresco (encoded files)")
        print("  - test_decoded.png (decoded image)")
        print("  - test_lossless.fresco (lossless encoded)")
        print("  - test_lossless_input.png (lossless input)")
        
    except Exception as e:
        print(f"Error running examples: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()
