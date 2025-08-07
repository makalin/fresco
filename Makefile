# Makefile for FRESCO project

# Variables
BUILD_DIR = build
INSTALL_DIR = /usr/local
CMAKE = cmake
MAKE = make
PYTHON = python3
PIP = pip3

# Default target
.PHONY: all
all: build

# Create build directory and configure
.PHONY: configure
configure:
	@echo "Configuring FRESCO..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) .. -DCMAKE_BUILD_TYPE=Release

# Build the project
.PHONY: build
build: configure
	@echo "Building FRESCO..."
	@cd $(BUILD_DIR) && $(MAKE) -j$(shell nproc)

# Build with debug information
.PHONY: debug
debug:
	@echo "Building FRESCO (Debug)..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) .. -DCMAKE_BUILD_TYPE=Debug
	@cd $(BUILD_DIR) && $(MAKE) -j$(shell nproc)

# Install the library
.PHONY: install
install: build
	@echo "Installing FRESCO..."
	@cd $(BUILD_DIR) && sudo $(MAKE) install

# Uninstall the library
.PHONY: uninstall
uninstall:
	@echo "Uninstalling FRESCO..."
	@sudo rm -rf $(INSTALL_DIR)/include/fresco
	@sudo rm -f $(INSTALL_DIR)/lib/libfresco*
	@sudo rm -f $(INSTALL_DIR)/bin/fresco
	@sudo rm -rf $(INSTALL_DIR)/lib/cmake/fresco

# Run tests
.PHONY: test
test: build
	@echo "Running tests..."
	@cd $(BUILD_DIR) && $(MAKE) test

# Run benchmarks
.PHONY: benchmark
benchmark: build
	@echo "Running benchmarks..."
	@cd $(BUILD_DIR) && $(MAKE) benchmark

# Clean build files
.PHONY: clean
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)
	@find . -name "*.pyc" -delete
	@find . -name "__pycache__" -delete
	@find . -name "*.o" -delete
	@find . -name "*.so" -delete

# Clean everything
.PHONY: distclean
distclean: clean
	@echo "Cleaning everything..."
	@rm -rf node_modules
	@rm -f package-lock.json
	@rm -rf .pytest_cache
	@rm -rf htmlcov
	@rm -f .coverage

# Python package
.PHONY: python-build
python-build:
	@echo "Building Python package..."
	@cd bindings/python && $(PYTHON) setup.py build

.PHONY: python-install
python-install:
	@echo "Installing Python package..."
	@cd bindings/python && $(PIP) install -e .

.PHONY: python-test
python-test:
	@echo "Running Python tests..."
	@cd bindings/python && $(PYTHON) -m pytest tests/

# Node.js package
.PHONY: node-install
node-install:
	@echo "Installing Node.js dependencies..."
	@npm install

.PHONY: node-build
node-build: node-install
	@echo "Building Node.js package..."
	@npm run build

.PHONY: node-test
node-test: node-install
	@echo "Running Node.js tests..."
	@npm test

# Documentation
.PHONY: docs
docs:
	@echo "Building documentation..."
	@cd docs && $(MAKE) html

# Format code
.PHONY: format
format:
	@echo "Formatting code..."
	@find src -name "*.cpp" -o -name "*.h" | xargs clang-format -i
	@find include -name "*.h" | xargs clang-format -i
	@find tools -name "*.cpp" | xargs clang-format -i
	@find tests -name "*.cpp" | xargs clang-format -i
	@black bindings/python/
	@prettier --write bindings/nodejs/src/**/*.ts

# Lint code
.PHONY: lint
lint:
	@echo "Linting code..."
	@cd $(BUILD_DIR) && $(MAKE) lint

# Check code style
.PHONY: check-style
check-style:
	@echo "Checking code style..."
	@find src -name "*.cpp" -o -name "*.h" | xargs clang-format --dry-run --Werror
	@find include -name "*.h" | xargs clang-format --dry-run --Werror
	@black --check bindings/python/
	@prettier --check bindings/nodejs/src/**/*.ts

# Package for distribution
.PHONY: package
package: clean build test
	@echo "Creating distribution package..."
	@mkdir -p dist
	@tar -czf dist/fresco-$(shell git describe --tags --always).tar.gz \
		--exclude=.git --exclude=build --exclude=dist --exclude=node_modules .

# Help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all          - Build the project (default)"
	@echo "  configure    - Configure the build"
	@echo "  build        - Build the project"
	@echo "  debug        - Build with debug information"
	@echo "  install      - Install the library"
	@echo "  uninstall    - Uninstall the library"
	@echo "  test         - Run tests"
	@echo "  benchmark    - Run benchmarks"
	@echo "  clean        - Clean build files"
	@echo "  distclean    - Clean everything"
	@echo "  python-build - Build Python package"
	@echo "  python-install - Install Python package"
	@echo "  python-test  - Run Python tests"
	@echo "  node-install - Install Node.js dependencies"
	@echo "  node-build   - Build Node.js package"
	@echo "  node-test    - Run Node.js tests"
	@echo "  docs         - Build documentation"
	@echo "  format       - Format code"
	@echo "  lint         - Lint code"
	@echo "  check-style  - Check code style"
	@echo "  package      - Create distribution package"
	@echo "  help         - Show this help"
