# Contributing to sample-c

Thank you for your interest in contributing to this project!

## Getting Started

### Prerequisites

- GCC or compatible C compiler
- CMake (optional, for build system)
- Git

### Setting Up the Development Environment

1. Fork the repository on GitHub
2. Clone your fork locally:
   ```bash
   git clone https://github.com/YOUR_USERNAME/sample-c.git
   cd sample-c
   ```
3. Add the upstream remote:
   ```bash
   git remote add upstream https://github.com/s-celles/sample-c.git
   ```

### Building the Project

```bash
# Using GCC directly
gcc -o HelloWorld main.c

# Or using CMake
mkdir build && cd build
cmake ..
make
```

## How to Contribute

### Reporting Bugs

- Check if the issue already exists in [GitHub Issues](https://github.com/s-celles/sample-c/issues)
- If not, create a new issue with a clear description and steps to reproduce

### Suggesting Features

- Open a new issue describing the feature and its use case
- Discuss the implementation approach before starting work

### Submitting Changes

1. Create a new branch from `main`:
   ```bash
   git checkout -b feat/your-feature-name
   ```
2. Make your changes following the coding standards below
3. Commit using [Conventional Commits](https://www.conventionalcommits.org/):
   - `feat:` for new features
   - `fix:` for bug fixes
   - `docs:` for documentation changes
   - `refactor:` for code refactoring
   - `test:` for adding tests
   - `chore:` for maintenance tasks
4. Push to your fork and open a Pull Request

### Coding Standards

- Follow consistent C coding style
- Use meaningful variable and function names
- Add comments for complex logic
- Ensure code compiles without warnings

## Versioning

This project follows [Semantic Versioning](https://semver.org/) (SemVer):

- **MAJOR** version for incompatible API changes
- **MINOR** version for backwards-compatible new features
- **PATCH** version for backwards-compatible bug fixes

## Code of Conduct

Please be respectful and constructive in all interactions. We aim to maintain a welcoming environment for all contributors.

## Questions?

Feel free to open an issue for any questions about contributing.
