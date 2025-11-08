# PVRTC - PowerVR Texture Compression Library

A C++ implementation of PVRTC (PowerVR Texture Compression) encoding and decoding functionality for 4-bit per pixel texture compression.

## Overview

PVRTC is a lossy texture compression format developed by Imagination Technologies. This library provides tools for:
- **Encoding**: Converting RGBA and RGB textures to PVRTC 4-bit format
- **Decoding**: Decompressing PVRTC 4-bit compressed textures back to RGBA format
- **Color Management**: Handling color space conversions and bit-depth reductions
- **Morton Encoding**: Optimized memory layout for texture lookups

## Features

- **4-bit Per Pixel Compression**: Highly efficient texture compression achieving 8:1 compression ratio
- **RGB & RGBA Support**: Encode both opaque and alpha-channel textures
- **Color Quantization**: Intelligent color space reduction with bilinear interpolation
- **Modulation Encoding**: Advanced texture modulation for quality preservation
- **Punch-Through Alpha**: Support for binary alpha transparency

## License

MIT License - See LICENSE.txt for details

## References

- PowerVR Texture Compression format specifications
- Imagination Technologies documentation
- Z-order (Morton code) curve optimization for memory layouts
