# Contributing

Thanks for your interest in improving Garbage! Please open an issue or pull request for bug fixes,
improvements, or new features.

## Building

```sh
make            # release build via CMake (build/release/garbage)
make PRESET=debug
```

Requires CMake 3.28+, GNU Make, and GCC 14+ or Clang 18+. See `CMakePresets.json` for the
`debug`, `release`, and `asan` presets.

## Testing

```sh
make test       # builds and runs the Catch2 unit tests + CLI smoke tests via CTest
make sanitize   # runs the same suite under AddressSanitizer + UBSan
```

Catch2 is fetched automatically at configure time (pinned to an exact commit). Pass
`-DBUILD_TESTING=OFF` to CMake to skip it. Please add or update tests for any behavior change.

## Formatting and linting

```sh
make format        # applies clang-format (config in .clang-format)
make format-check  # what CI runs
make lint          # clang-tidy over src/ (config in .clang-tidy)
```

CI (see `.github/workflows/ci.yml`) gates on the build matrix (GCC 14, Clang 18), tests,
sanitizers, clang-format, and clang-tidy — please make sure `make test format-check lint`
passes before opening a PR.

## Commit messages

The history follows [Conventional Commits](https://www.conventionalcommits.org/) (`feat:`,
`fix:`, `chore:`, ...). Please keep new commits consistent with that style.
