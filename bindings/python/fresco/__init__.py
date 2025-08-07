"""
FRESCO: Fast, Rich, and Efficient Scalable Content Object

A next-generation universal image format designed to surpass the compression
efficiency of existing state-of-the-art formats like WebP and AVIF.
"""

from ._fresco import *

__version__ = "0.1.0"
__author__ = "Mehmet T. AKALIN"
__license__ = "MIT"

# Import main classes and functions
from .encoder import FrescoEncoder
from .decoder import FrescoDecoder
from .metadata import FrescoMetadata

__all__ = [
    'FrescoEncoder',
    'FrescoDecoder', 
    'FrescoMetadata',
    'encode',
    'decode',
    'get_metadata',
    'get_version',
    'FRESCO_OK',
    'FRESCO_ERROR_INVALID_PARAMETER',
    'FRESCO_ERROR_OUT_OF_MEMORY',
    'FRESCO_ERROR_IO',
    'FRESCO_ERROR_UNSUPPORTED_FORMAT',
    'FRESCO_ERROR_CORRUPTED_DATA',
    'FRESCO_ERROR_ENCODING_FAILED',
    'FRESCO_ERROR_DECODING_FAILED',
    'FRESCO_ERROR_NOT_IMPLEMENTED',
    'FRESCO_COMPRESSION_LOSSY',
    'FRESCO_COMPRESSION_LOSSLESS',
    'FRESCO_COLORSPACE_RGB',
    'FRESCO_COLORSPACE_RGBA',
    'FRESCO_COLORSPACE_YUV420',
    'FRESCO_COLORSPACE_YUV422',
    'FRESCO_COLORSPACE_YUV444',
    'FRESCO_COLORSPACE_GRAY',
    'FRESCO_COLORSPACE_GRAYA',
]
