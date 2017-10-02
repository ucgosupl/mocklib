Changelog
============
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]
------------------------

### Added

### Changed

### Fixed

### Deprecated

### Removed

## [0.3.0] - 2017-10-02
------------------------

### Added
- Integration with Travis-CI
- Callback mode
- Script for automatic generation of mocklib_define.h macros
- Common log for all unit tests
- Makefile checks dependency on header files

### Changed
- Make default behaviour is compilation only, tests run with flag RUN_TEST=1
- Travis compiles all targets first, then run tests

### Fixed
- Macro UTLIB_ASSERT_EQUAL required one argument msg instead of two - expected and actual.

### Deprecated

### Removed

## [0.2.0] - 2017-09-25
------------------------

### Added
- Python scripts for generating mocks.
- Scripts integration with mock tests.

### Changed

### Fixed
- Compiler warnings.

### Deprecated

### Removed

## 0.1.0 - 2017-09-01
------------------------

### Added
- Basic mode implementation.
- Trace mode implementation.
- Macros for mock creation.
- Reference implementation of example mocks.
- Integration with Unity framework.

### Changed

### Fixed

### Deprecated

### Removed


[Unreleased]: https://github.com/ucgosupl/mocklib/compare/v0.2.0...dev
[0.2.0]: https://github.com/ucgosupl/mocklib/compare/v0.1.0...v0.2.0
[0.3.0]: https://github.com/ucgosupl/mocklib/compare/v0.2.0...v0.3.0