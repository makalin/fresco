# Tools directory CMakeLists.txt

# Command-line interface
add_executable(fresco-cli fresco-cli.cpp)

# Link with fresco library
target_link_libraries(fresco-cli fresco)

# Include directories
target_include_directories(fresco-cli PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Set executable properties
set_target_properties(fresco-cli PROPERTIES
    OUTPUT_NAME fresco
)

# Install executable
install(TARGETS fresco-cli
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
