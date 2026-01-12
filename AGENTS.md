# Code Preferences

## Git Commits
- GitHub handle: s-celles
- Name: Sébastien Celles
- Use conventional commit format (feat:, fix:, refactor:, docs:, test:, chore:, etc.)
- Do NOT add "Co-Authored-By: Claude" to commit messages

## .gitignore
- Use appropriate .gitignore templates from https://github.com/github/gitignore
- Always ignore build artifacts, object files, and executables
- Ignore IDE-specific files (.vscode/, .idea/) - can be commented out if sharing settings is desired
- Ignore AI-generated folders (.claude/, .ai/, etc.) to keep repository clean
- Add project-specific binary names to .gitignore

## LICENSE
- Choose an appropriate license using https://choosealicense.com/
- This project uses MIT License
- Always include the LICENSE file at the repository root
- Update copyright year and author name in the LICENSE file

## CONTRIBUTING.md
- Include a CONTRIBUTING.md file to guide contributors
- Describe how to set up the development environment
- Explain the pull request process and coding standards
- Reference the CODE_OF_CONDUCT.md if applicable
- See https://docs.github.com/en/communities/setting-up-your-project-for-healthy-contributions

## SECURITY.md
- Include a SECURITY.md file to describe security policies
- Explain how to report vulnerabilities (responsible disclosure)
- List supported versions and security update policies
- GitHub provides a template via repository Security tab
- See https://docs.github.com/en/code-security/getting-started/adding-a-security-policy-to-your-repository

## Semantic Versioning
- Follow [Semantic Versioning](https://semver.org/) (SemVer) for releases
- Format: **MAJOR.MINOR.PATCH** (e.g., 1.2.3)
- **MAJOR**: Incompatible API changes
- **MINOR**: Backwards-compatible new features
- **PATCH**: Backwards-compatible bug fixes
- Use git tags for version releases (e.g., `v1.0.0`)

## Test-Driven Development (TDD)
- Write tests before implementing features (Red-Green-Refactor cycle)
- **Red**: Write a failing test that defines expected behavior
- **Green**: Write minimal code to make the test pass
- **Refactor**: Improve code while keeping tests green
- For C projects, use testing frameworks like [Unity](https://github.com/ThrowTheSwitch/Unity), [CUnit](http://cunit.sourceforge.net/), or [Check](https://libcheck.github.io/check/)
- Keep tests fast, isolated, and deterministic
- See https://martinfowler.com/bliki/TestDrivenDevelopment.html

## Continuous Integration (CI)
- Use GitHub Actions for CI/CD pipelines
- Run tests automatically on every push and pull request
- Build and test on multiple platforms/compilers when applicable
- Fail fast: stop pipeline on first failure
- Keep CI configuration in `.github/workflows/`
- See https://docs.github.com/en/actions

## Code Coverage
- Measure test coverage to identify untested code paths
- For C projects, use [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) with GCC or [llvm-cov](https://llvm.org/docs/CommandGuide/llvm-cov.html)
- Integrate with coverage services like [Codecov](https://codecov.io/) or [Coveralls](https://coveralls.io/)
- Aim for meaningful coverage, not 100% for its own sake
- Focus on critical paths and edge cases
- Display coverage badge in README.md

## Code Quality
- Use static analysis tools (e.g., [cppcheck](http://cppcheck.net/), [clang-tidy](https://clang.llvm.org/extra/clang-tidy/))
- Use linters to enforce coding standards
- Configure pre-commit hooks for automated checks
- Use [pre-commit](https://pre-commit.com/) framework for hook management
- Address compiler warnings (`-Wall -Wextra -Werror`)
- Consider memory sanitizers (ASan, MSan, UBSan) for debugging

## Documentation
- Write clear README.md with project overview, installation, and usage
- Document public APIs with comments (Doxygen for C)
- Keep documentation up-to-date with code changes
- Include examples and code snippets
- Generate API documentation automatically in CI

## Active Technologies
