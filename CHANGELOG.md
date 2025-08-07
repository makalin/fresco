# Changelog

All notable changes to FRESCO will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial project structure and documentation
- Core C++ library with encoder and decoder
- Python bindings with high-level API
- Node.js bindings (planned)
- Command-line interface tool
- Comprehensive test suite
- Build system with CMake
- CI/CD pipeline with GitHub Actions

### Changed
- N/A

### Deprecated
- N/A

### Removed
- N/A

### Fixed
- N/A

### Security
- N/A

## [0.1.0] - 2025-01-XX

### Added
- Initial release of FRESCO format
- Basic encoder and decoder implementation
- Support for lossy and lossless compression
- RGB and RGBA color space support
- Basic metadata extraction
- Command-line interface with encode/decode/info commands
- Python bindings with FrescoEncoder and FrescoDecoder classes
- Comprehensive documentation including format specification
- Build system supporting Linux, macOS, and Windows
- Test suite with basic functionality tests
- MIT license

### Technical Details
- C++17 implementation with modern C++ features
- ISOBMFF-inspired container format
- Neural network-based compression (planned)
- Wavelet-based compression (planned)
- Adaptive transform coding (planned)
- Progressive decoding support (planned)
- Multi-threaded processing support
- Cross-platform compatibility

### Known Issues
- This is an experimental release
- Many advanced features are planned but not yet implemented
- Performance optimizations are ongoing
- Browser support is not yet available

---

## Version History

- **0.1.0**: Initial experimental release with basic functionality
- **Future releases**: Will add advanced compression algorithms, browser support, and performance optimizations

## Contributing

To add entries to this changelog:

1. Add your changes under the appropriate section in [Unreleased]
2. Use the following categories:
   - **Added**: New features
   - **Changed**: Changes in existing functionality
   - **Deprecated**: Soon-to-be removed features
   - **Removed**: Removed features
   - **Fixed**: Bug fixes
   - **Security**: Security-related changes

3. When releasing a new version, move the [Unreleased] entries to the new version section

## Links

- [FRESCO Documentation](https://fresco-format.github.io)
- [GitHub Repository](https://github.com/makalin/fresco)
- [Issue Tracker](https://github.com/makalin/fresco/issues)
