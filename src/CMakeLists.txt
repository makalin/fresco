# Source directory CMakeLists.txt

# Set source files
set(FRESCO_SOURCES
    core/encoder.cpp
    core/decoder.cpp
    core/compression.cpp
    core/container.cpp
    core/utils.cpp
    codecs/lossy_codec.cpp
    codecs/lossless_codec.cpp
    codecs/vector_codec.cpp
    codecs/3d_codec.cpp
)

# Create library
add_library(fresco ${FRESCO_SOURCES})

# Set library properties
set_target_properties(fresco PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/../include/fresco/fresco.h"
)

# Link libraries
target_link_libraries(fresco
    ${CMAKE_THREAD_LIBS_INIT}
)

# Add OpenMP if available
if(OpenMP_CXX_FOUND)
    target_link_libraries(fresco OpenMP::OpenMP_CXX)
endif()

# Include directories
target_include_directories(fresco
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(fresco PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -fvisibility=hidden
    )
endif()

if(MSVC)
    target_compile_options(fresco PRIVATE
        /W4
        /wd4251  # class needs to have dll-interface
    )
    target_compile_definitions(fresco PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

# Export symbols
if(WIN32)
    target_compile_definitions(fresco PRIVATE FRESCO_EXPORTS)
endif()

# Install library
install(TARGETS fresco
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fresco)
