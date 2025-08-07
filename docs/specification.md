# FRESCO Format Specification

## Version 0.1.0

**FRESCO: Fast, Rich, and Efficient Scalable Content Object**

This document specifies the FRESCO image format, a next-generation universal image format designed to surpass the compression efficiency of existing state-of-the-art formats like WebP and AVIF.

## 1. Overview

### 1.1 Design Goals

- **Superior Compression**: Achieve better compression ratios than WebP and AVIF
- **Universal Container**: Support raster images, vector graphics, 3D models, and animations
- **High Performance**: Optimized encoding and decoding speeds
- **Future-Proof**: Support for HDR, wide color gamut, and advanced features
- **Extensible**: Modular architecture for easy extension

### 1.2 Key Features

- State-of-the-art lossy and lossless compression
- Native support for multiple content types
- Advanced neural network-based compression
- Wavelet-based techniques
- Adaptive transform coding
- Progressive decoding support

## 2. File Structure

### 2.1 Container Format

FRESCO uses an ISOBMFF-inspired container format with the following structure:

```
FRESCO File
├── File Type Box (ftyp)
├── Movie Box (moov)
│   ├── Movie Header Box (mvhd)
│   ├── Track Box (trak) - Raster
│   ├── Track Box (trak) - Vector (optional)
│   ├── Track Box (trak) - 3D Model (optional)
│   └── Track Box (trak) - Animation (optional)
└── Media Data Box (mdat)
```

### 2.2 Box Structure

Each box follows the ISOBMFF format:

```
Box Header (8 or 16 bytes)
├── Size (4 bytes) - Box size including header
├── Type (4 bytes) - Box type identifier
└── Extended Size (8 bytes) - If size == 1

Box Data (variable)
└── Box-specific data
```

### 2.3 File Type Box (ftyp)

```
Size: 32 bytes
Type: 'ftyp'
Data:
├── Major Brand (4 bytes): 'fres'
├── Minor Version (4 bytes): 0x00010000
├── Compatible Brands (variable):
    ├── 'fres' (FRESCO)
    ├── 'isom' (ISO Base Media)
    └── 'mif1' (Media Interchange Format)
```

### 2.4 Track Box (trak)

Each track contains metadata and references to media data:

```
Track Box (trak)
├── Track Header Box (tkhd)
├── Media Box (mdia)
│   ├── Media Header Box (mdhd)
│   ├── Handler Box (hdlr)
│   └── Media Information Box (minf)
│       ├── Sample Table Box (stbl)
│       └── Data Information Box (dinf)
└── Track Reference Box (tref) - optional
```

## 3. Compression Techniques

### 3.1 Lossy Compression

#### 3.1.1 Neural Network Compression

- **Architecture**: Learned image compression with hyperpriors
- **Latent Space**: Compact representation using convolutional autoencoders
- **Quantization**: Learned quantization parameters
- **Entropy Coding**: Adaptive arithmetic coding with hyperprior modeling

#### 3.1.2 Wavelet-Based Compression

- **Transform**: Multi-level wavelet decomposition
- **Subbands**: LL, LH, HL, HH at multiple scales
- **Quantization**: Adaptive quantization per subband
- **Prediction**: Inter-subband prediction

#### 3.1.3 Adaptive Transform Coding

- **Block Analysis**: Content-adaptive transform selection
- **Transforms**: DCT, Wavelet, Directional transforms
- **Mode Decision**: Rate-distortion optimized selection
- **Side Information**: Transform mode signaling

### 3.2 Lossless Compression

#### 3.2.1 Advanced Prediction

- **Context Modeling**: Multi-dimensional context analysis
- **Predictors**: Linear, non-linear, and adaptive predictors
- **Residual Coding**: Efficient residual representation
- **Adaptive Selection**: Per-pixel predictor selection

#### 3.2.2 Entropy Coding

- **Arithmetic Coding**: High-precision arithmetic coder
- **ANS**: Asymmetric Numeral Systems for speed
- **Context Adaptation**: Continuous probability model updates
- **Parallel Processing**: Multi-threaded entropy coding

## 4. Content Types

### 4.1 Raster Images

#### 4.1.1 Color Spaces

- **RGB**: 8/10/12/16-bit per channel
- **RGBA**: With alpha channel support
- **YUV**: 4:2:0, 4:2:2, 4:4:4 chroma subsampling
- **Grayscale**: Single channel with optional alpha

#### 4.1.2 Bit Depths

- **Standard**: 8-bit per channel
- **High Bit Depth**: 10/12/16-bit per channel
- **HDR**: 16-bit float (half precision)
- **Wide Gamut**: Extended color space support

### 4.2 Vector Graphics

#### 4.2.1 Path Data

- **Commands**: Move, Line, Curve, Arc, Close
- **Coordinates**: Relative and absolute positioning
- **Transforms**: Matrix transformations
- **Styling**: Stroke, fill, opacity, effects

#### 4.2.2 Compression

- **Differential Encoding**: Delta compression of coordinates
- **Command Optimization**: Run-length encoding of commands
- **Predictive Coding**: Context-based prediction
- **Binary Encoding**: Compact binary representation

### 4.3 3D Models

#### 4.3.1 Geometry

- **Vertices**: Position, normal, texture coordinates
- **Indices**: Triangle/quad face definitions
- **LOD**: Level-of-detail representations
- **Compression**: Quantization and prediction

#### 4.3.2 Materials

- **Textures**: Embedded texture data
- **Shaders**: Material definitions
- **Animations**: Skeletal and morphing data
- **Metadata**: Model information

### 4.4 Animations

#### 4.4.1 Frame Data

- **Keyframes**: Interpolated keyframe data
- **Timing**: Frame timing and duration
- **Interpolation**: Smooth interpolation curves
- **Compression**: Inter-frame prediction

#### 4.4.2 Metadata

- **Frame Rate**: Animation timing
- **Looping**: Loop behavior specification
- **Transitions**: Frame transition effects
- **Audio**: Synchronized audio data

## 5. Metadata

### 5.1 Standard Metadata

- **EXIF**: Camera and image information
- **XMP**: Extensible metadata platform
- **ICC Profiles**: Color management
- **GPS**: Location information

### 5.2 Custom Metadata

- **User Boxes**: Application-specific data
- **Private Data**: Vendor-specific information
- **Extensions**: Future format extensions
- **Compatibility**: Backward compatibility

## 6. Progressive Decoding

### 6.1 Quality Layers

- **Base Layer**: Low-quality preview
- **Enhancement Layers**: Progressive quality improvement
- **Rate Control**: Adaptive bitrate allocation
- **Streaming**: Network-optimized delivery

### 6.2 Spatial Scalability

- **Resolution Levels**: Multiple resolution representations
- **Region of Interest**: Focused quality allocation
- **Tiled Decoding**: Independent tile processing
- **Parallel Processing**: Multi-threaded decoding

## 7. Performance Considerations

### 7.1 Encoding

- **Parallel Processing**: Multi-threaded encoding
- **Memory Management**: Efficient memory usage
- **Optimization**: Profile-guided optimization
- **Hardware Acceleration**: GPU/CPU optimization

### 7.2 Decoding

- **Streaming**: Progressive decoding support
- **Caching**: Intelligent cache management
- **Prefetching**: Predictive data loading
- **Hardware Support**: SIMD and GPU acceleration

## 8. Compatibility

### 8.1 Backward Compatibility

- **Version Management**: Format version handling
- **Feature Detection**: Capability negotiation
- **Fallback Support**: Graceful degradation
- **Migration Path**: Upgrade strategies

### 8.2 Interoperability

- **Standard Compliance**: Industry standard adherence
- **Tool Support**: Third-party tool integration
- **Platform Support**: Cross-platform compatibility
- **Web Integration**: Browser and web standard support

## 9. Security

### 9.1 Data Integrity

- **Checksums**: Data integrity verification
- **Digital Signatures**: Authenticity verification
- **Watermarking**: Content protection
- **Encryption**: Optional content encryption

### 9.2 Privacy

- **Metadata Sanitization**: Privacy-preserving metadata
- **Content Filtering**: Safe content handling
- **Access Control**: Permission-based access
- **Audit Trails**: Usage tracking

## 10. Future Extensions

### 10.1 Planned Features

- **AI Enhancement**: Machine learning improvements
- **Advanced HDR**: Extended dynamic range support
- **Spatial Audio**: 3D audio integration
- **Interactive Content**: User interaction support

### 10.2 Extensibility

- **Plugin Architecture**: Third-party extensions
- **Custom Codecs**: User-defined compression
- **Format Evolution**: Backward-compatible updates
- **Community Development**: Open development model

---

**Note**: This specification is a living document and will be updated as the FRESCO format evolves. For the latest version, please refer to the official FRESCO documentation.
