# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Interface for logger objects to handle log messages.
- Global LoggerManager object to handle multiple loggers.
- StandardLogger class that writes logs to the standard output.
- Build dependency to the [fmt](https://github.com/fmtlib/fmt) library.
- Convenience macros for writing logs.

### Changed

- Project now follows the [Canonical Project Structure](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html).
- Project is now licensed under either the MIT or APACHE-2.0 licenses.
- Removed copyright notice from source files.
- Disabled environment unit tests.
- Standardized the structure of the README file.

## [0.1.0] - 2023-01-28

### Added

- Base class for protocol and message parsers.
- Ethernet protocol parser.
- IPv4 protocol parser.
- ICMP protocol parser.

### Changed

- Disabled session unit tests.

### Fixed

- VLAN Tag attribute setters.
