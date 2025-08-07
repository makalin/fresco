# Contributing to FRESCO

Thank you for your interest in contributing to FRESCO! This document provides guidelines and information for contributors.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Setup](#development-setup)
- [Contributing Guidelines](#contributing-guidelines)
- [Code Style](#code-style)
- [Testing](#testing)
- [Documentation](#documentation)
- [Submitting Changes](#submitting-changes)
- [Release Process](#release-process)

## Code of Conduct

This project is committed to providing a welcoming and inclusive environment for all contributors. Please be respectful and considerate of others.

## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 6+, MSVC 2017+)
- CMake 3.15+
- Python 3.8+ (for Python bindings)
- Node.js 14+ (for Node.js bindings)
- Git

### Fork and Clone

1. Fork the repository on GitHub
2. Clone your fork locally:
   ```bash
   git clone https://github.com/your-username/fresco.git
   cd fresco
   git remote add upstream https://github.com/makalin/fresco.git
   ```

## Development Setup

### Building from Source

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON

# Build
make -j$(nproc)

# Run tests
make test
```

### Python Development

```bash
# Install development dependencies
pip install -r requirements.txt

# Install in development mode
cd bindings/python
pip install -e .

# Run tests
python -m pytest tests/
```

### Node.js Development

```bash
# Install dependencies
npm install

# Build
npm run build

# Run tests
npm test
```

## Contributing Guidelines

### Issue Reporting

Before creating a new issue:

1. Check if the issue has already been reported
2. Use the appropriate issue template
3. Provide detailed information including:
   - Operating system and version
   - Compiler version
   - Steps to reproduce
   - Expected vs actual behavior

### Feature Requests

When requesting new features:

1. Describe the use case and motivation
2. Explain how it fits into the project's goals
3. Consider implementation complexity
4. Discuss potential impact on existing functionality

### Bug Fixes

When fixing bugs:

1. Create a minimal test case that reproduces the issue
2. Add regression tests to prevent future occurrences
3. Document the fix in commit messages
4. Consider backporting to stable releases

## Code Style

### C++ Code Style

- Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- Use 2-space indentation
- Maximum line length: 100 characters
- Use `snake_case` for variables and functions
- Use `PascalCase` for classes and structs
- Use `UPPER_CASE` for constants and macros

### Python Code Style

- Follow [PEP 8](https://www.python.org/dev/peps/pep-0008/)
- Use 4-space indentation
- Maximum line length: 88 characters (Black default)
- Use `snake_case` for variables and functions
- Use `PascalCase` for classes

### TypeScript/JavaScript Code Style

- Follow the project's ESLint configuration
- Use 2-space indentation
- Use `camelCase` for variables and functions
- Use `PascalCase` for classes and interfaces

### Formatting

Run the formatting tools before submitting:

```bash
# C++
find src include tools tests -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Python
black bindings/python/

# TypeScript/JavaScript
prettier --write bindings/nodejs/src/**/*.ts
```

## Testing

### Writing Tests

- Write tests for all new functionality
- Aim for high test coverage
- Use descriptive test names
- Test both success and failure cases
- Include edge cases and boundary conditions

### Running Tests

```bash
# C++ tests
cd build && make test

# Python tests
cd bindings/python && python -m pytest tests/

# Node.js tests
npm test

# All tests
make test
```

### Test Coverage

```bash
# Python coverage
cd bindings/python && python -m pytest --cov=fresco tests/

# Generate coverage report
coverage html
```

## Documentation

### Code Documentation

- Document all public APIs
- Use Doxygen-style comments for C++
- Use docstrings for Python
- Use JSDoc for TypeScript/JavaScript
- Keep documentation up to date with code changes

### User Documentation

- Update README.md for user-facing changes
- Add examples for new features
- Update API documentation
- Write tutorials for complex features

### Technical Documentation

- Update design documents for architectural changes
- Document performance characteristics
- Explain algorithms and data structures
- Maintain changelog

## Submitting Changes

### Commit Guidelines

Follow the [Conventional Commits](https://www.conventionalcommits.org/) specification:

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

Types:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes
- `refactor`: Code refactoring
- `test`: Test changes
- `chore`: Build or tool changes

### Pull Request Process

1. Create a feature branch from `develop`:
   ```bash
   git checkout develop
   git pull upstream develop
   git checkout -b feature/your-feature-name
   ```

2. Make your changes and commit them:
   ```bash
   git add .
   git commit -m "feat: add new compression algorithm"
   ```

3. Push to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```

4. Create a pull request:
   - Use the appropriate PR template
   - Describe the changes clearly
   - Link related issues
   - Request reviews from maintainers

5. Address review feedback:
   - Respond to comments promptly
   - Make requested changes
   - Update documentation if needed

### Review Process

- All changes require at least one review
- Maintainers will review for:
  - Code quality and style
  - Test coverage
  - Documentation updates
  - Performance impact
  - Security considerations

## Release Process

### Versioning

FRESCO follows [Semantic Versioning](https://semver.org/):

- `MAJOR.MINOR.PATCH`
- Major: Breaking changes
- Minor: New features (backward compatible)
- Patch: Bug fixes (backward compatible)

### Release Checklist

Before releasing:

- [ ] All tests pass
- [ ] Documentation is up to date
- [ ] Changelog is updated
- [ ] Version numbers are updated
- [ ] Release notes are written
- [ ] Binaries are built and tested
- [ ] Package distributions are created

### Creating a Release

1. Update version numbers:
   ```bash
   # Update CMakeLists.txt
   # Update package.json
   # Update Python setup.py
   # Update documentation
   ```

2. Create release branch:
   ```bash
   git checkout develop
   git checkout -b release/v1.0.0
   git push origin release/v1.0.0
   ```

3. Create pull request to main:
   - Merge release branch to main
   - Tag the release
   - Create GitHub release

4. Update develop:
   ```bash
   git checkout develop
   git merge main
   git push origin develop
   ```

## Getting Help

- Check the [documentation](https://fresco-format.github.io)
- Search existing issues and discussions
- Ask questions in GitHub Discussions
- Contact maintainers for urgent issues

## Recognition

Contributors will be recognized in:
- Project README
- Release notes
- Contributor hall of fame
- GitHub contributors page

Thank you for contributing to FRESCO!
