# FRESCO: Fast, Rich, and Efficient Scalable Content Object

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://github.com/makalin/fresco/workflows/CI/badge.svg)](https://github.com/makalin/fresco/actions)
[![Documentation](https://img.shields.io/badge/docs-latest-brightgreen.svg)](https://fresco-format.github.io)

FRESCO is an experimental, next-generation universal image format designed to surpass the compression efficiency of existing state-of-the-art formats like WebP and AVIF. It delivers smaller file sizes without compromising visual fidelity while supporting a wide range of content types including raster images, vector graphics, 3D models, and animations.

## 🚀 Key Features

- **Advanced Compression**: State-of-the-art lossy and lossless compression using learned neural networks and wavelet-based techniques
- **Universal Container**: Native support for raster images, vector graphics, 3D models, and animations in a single file
- **High Performance**: Optimized encoding and decoding speeds for real-time applications
- **Future-Proof**: Support for HDR, wide color gamut, and full transparency
- **Extensible**: Modular architecture allowing for easy extension and customization

## 📊 Performance Comparison

| Feature | FRESCO | AVIF | WebP | JPEG XL |
|---------|--------|------|------|---------|
| **Lossy Compression** | **State-of-the-art** | Excellent | Good | Very Good |
| **Lossless Compression** | **State-of-the-art** | Good | Good | Excellent |
| **Transparency** | Yes | Yes | Yes | Yes |
| **Animation** | Yes (efficient) | Yes | Yes | Yes |
| **HDR/WCG Support** | Yes | Yes | No | Yes |
| **3D Model Support** | **Yes (native)** | No | No | No |
| **Vector Graphics** | **Yes (native)** | No | No | No |
| **Encoding Speed** | Optimized | Slow | Fast | Moderate |

## 🛠️ Installation

### Prerequisites

- Python 3.8+ (for Python bindings)
- C++17 compatible compiler (for core library)
- CMake 3.15+
- Git

### Building from Source

```bash
# Clone the repository
git clone https://github.com/makalin/fresco.git
cd fresco

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make -j$(nproc)

# Install (optional)
sudo make install
```

### Python Package

```bash
# Install Python dependencies
pip install -r requirements.txt

# Install FRESCO Python bindings
pip install -e .
```

### Node.js Package

```bash
# Install Node.js dependencies
npm install

# Build the package
npm run build
```

## 📖 Usage

### Command Line Interface

```bash
# Encode an image to FRESCO format
fresco encode input.png output.fresco --quality 85

# Decode a FRESCO file
fresco decode input.fresco output.png

# Convert between formats
fresco convert input.jpg output.fresco --lossless

# Get information about a FRESCO file
fresco info input.fresco
```

### Python API

```python
import fresco

# Encode an image
with open('input.png', 'rb') as f:
    image_data = f.read()

fresco_data = fresco.encode(image_data, quality=85)
with open('output.fresco', 'wb') as f:
    f.write(fresco_data)

# Decode a FRESCO file
with open('input.fresco', 'rb') as f:
    fresco_data = f.read()

image_data = fresco.decode(fresco_data)
with open('output.png', 'wb') as f:
    f.write(image_data)
```

### JavaScript/TypeScript API

```typescript
import { FrescoEncoder, FrescoDecoder } from '@fresco/core';

// Encode an image
const encoder = new FrescoEncoder();
const frescoData = await encoder.encode(imageData, { quality: 85 });

// Decode a FRESCO file
const decoder = new FrescoDecoder();
const imageData = await decoder.decode(frescoData);
```

## 🏗️ Project Structure

```
fresco/
├── src/                    # Core C++ implementation
│   ├── core/              # Core compression algorithms
│   ├── container/         # File format container
│   ├── codecs/           # Codec implementations
│   └── utils/            # Utility functions
├── bindings/              # Language bindings
│   ├── python/           # Python bindings
│   ├── nodejs/           # Node.js bindings
│   └── wasm/             # WebAssembly bindings
├── tools/                 # Command-line tools
├── tests/                 # Test suite
├── benchmarks/            # Performance benchmarks
├── docs/                  # Documentation
├── examples/              # Example code
└── scripts/               # Build and utility scripts
```

## 🧪 Testing

```bash
# Run all tests
make test

# Run specific test suites
make test-unit
make test-integration
make test-benchmarks

# Run Python tests
python -m pytest tests/python/

# Run Node.js tests
npm test
```

## 📈 Benchmarks

```bash
# Run performance benchmarks
make benchmark

# Compare with other formats
python scripts/benchmark_compare.py
```

## 📚 Documentation

- [Format Specification](docs/specification.md)
- [API Reference](docs/api.md)
- [Performance Guide](docs/performance.md)
- [Contributing Guide](docs/contributing.md)

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guide](docs/contributing.md) for details on how to:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests
5. Submit a pull request

### Development Setup

```bash
# Install development dependencies
pip install -r requirements-dev.txt
npm install

# Set up pre-commit hooks
pre-commit install

# Run code formatting
make format

# Run linting
make lint
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by modern image formats like WebP, AVIF, and JPEG XL
- Built on research in learned image compression and neural networks
- Uses ISOBMFF container format as a foundation

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/makalin/fresco/issues)
- **Discussions**: [GitHub Discussions](https://github.com/makalin/fresco/discussions)
- **Documentation**: [Project Wiki](https://github.com/makalin/fresco/wiki)

## 🔮 Roadmap

- [ ] Browser support and WebAssembly implementation
- [ ] GPU acceleration for encoding/decoding
- [ ] Advanced animation features
- [ ] 3D model compression improvements
- [ ] Vector graphics optimization
- [ ] Mobile SDKs (iOS/Android)

---

**Note**: FRESCO is currently in experimental development. The format specification and API may change as the project evolves.
