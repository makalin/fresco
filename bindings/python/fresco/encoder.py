"""
FRESCO Encoder Python wrapper
"""

from typing import Optional, Dict, Any, Union
import numpy as np
from ._fresco import *


class FrescoEncoder:
    """
    FRESCO encoder for converting images to FRESCO format.
    
    This class provides a high-level interface for encoding images
    to the FRESCO format with various compression options.
    """
    
    def __init__(self, **kwargs):
        """
        Initialize the FRESCO encoder.
        
        Args:
            **kwargs: Encoding parameters (see set_params for details)
        """
        self._encoder = None
        self._create_encoder()
        
        if kwargs:
            self.set_params(**kwargs)
    
    def _create_encoder(self):
        """Create the underlying C encoder."""
        result = fresco_encoder_create(self._encoder)
        if result != FRESCO_OK:
            raise RuntimeError(f"Failed to create encoder: {fresco_error_string(result)}")
    
    def set_params(self, 
                   mode: str = "lossy",
                   quality: int = 85,
                   effort: int = 5,
                   max_threads: int = 0,
                   tile_size: int = 256,
                   enable_animation: bool = False,
                   enable_3d: bool = False,
                   enable_vector: bool = False) -> None:
        """
        Set encoding parameters.
        
        Args:
            mode: Compression mode ("lossy" or "lossless")
            quality: Quality setting (1-100, higher is better)
            effort: Encoding effort (1-10, higher is slower but better compression)
            max_threads: Maximum number of threads (0 for auto-detect)
            tile_size: Tile size for tiled encoding
            enable_animation: Enable animation support
            enable_3d: Enable 3D model support
            enable_vector: Enable vector graphics support
        """
        if self._encoder is None:
            raise RuntimeError("Encoder not initialized")
        
        # Validate parameters
        if quality < 1 or quality > 100:
            raise ValueError("Quality must be between 1 and 100")
        if effort < 1 or effort > 10:
            raise ValueError("Effort must be between 1 and 10")
        
        # Create parameters structure
        params = fresco_encode_params_t()
        params.mode = FRESCO_COMPRESSION_LOSSY if mode == "lossy" else FRESCO_COMPRESSION_LOSSLESS
        params.quality = quality
        params.effort = effort
        params.max_threads = max_threads
        params.tile_size = tile_size
        params.enable_animation = 1 if enable_animation else 0
        params.enable_3d = 1 if enable_3d else 0
        params.enable_vector = 1 if enable_vector else 0
        
        result = fresco_encoder_set_params(self._encoder, params)
        if result != FRESCO_OK:
            raise RuntimeError(f"Failed to set encoder parameters: {fresco_error_string(result)}")
    
    def encode(self, data: Union[bytes, np.ndarray], 
               format: Optional[str] = None) -> bytes:
        """
        Encode image data to FRESCO format.
        
        Args:
            data: Input image data (bytes or numpy array)
            format: Input format (auto-detected if None)
            
        Returns:
            Encoded FRESCO data as bytes
        """
        if self._encoder is None:
            raise RuntimeError("Encoder not initialized")
        
        # Convert numpy array to bytes if needed
        if isinstance(data, np.ndarray):
            data = data.tobytes()
        
        if not isinstance(data, bytes):
            raise TypeError("Data must be bytes or numpy array")
        
        # Encode
        output_data = None
        output_size = 0
        
        result = fresco_encoder_encode(self._encoder, data, len(data),
                                     output_data, output_size)
        
        if result != FRESCO_OK:
            raise RuntimeError(f"Failed to encode: {fresco_error_string(result)}")
        
        # Convert to Python bytes
        encoded_data = bytes(output_data[:output_size])
        fresco_free(output_data)
        
        return encoded_data
    
    def encode_file(self, input_path: str, output_path: str) -> None:
        """
        Encode an image file to FRESCO format.
        
        Args:
            input_path: Path to input image file
            output_path: Path to output FRESCO file
        """
        with open(input_path, 'rb') as f:
            data = f.read()
        
        encoded_data = self.encode(data)
        
        with open(output_path, 'wb') as f:
            f.write(encoded_data)
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()
    
    def close(self):
        """Close the encoder and free resources."""
        if self._encoder is not None:
            fresco_encoder_destroy(self._encoder)
            self._encoder = None
    
    def __del__(self):
        self.close()


def encode(data: Union[bytes, np.ndarray], 
           output_path: Optional[str] = None,
           **kwargs) -> Union[bytes, None]:
    """
    Convenience function to encode image data to FRESCO format.
    
    Args:
        data: Input image data (bytes or numpy array)
        output_path: Optional output file path
        **kwargs: Encoding parameters (see FrescoEncoder.set_params)
        
    Returns:
        Encoded data as bytes (if output_path is None) or None
    """
    with FrescoEncoder(**kwargs) as encoder:
        encoded_data = encoder.encode(data)
        
        if output_path:
            with open(output_path, 'wb') as f:
                f.write(encoded_data)
            return None
        else:
            return encoded_data
