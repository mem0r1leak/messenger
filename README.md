# Messenger

A zero-trust, end-to-end encrypted messenger implemented in pure C.

This project focuses on cryptographic correctness, architectural clarity,
and long-term maintainability. It is designed as a portable core library
with untrusted servers and platform-specific clients built on top.
## Project Status

🚧 **Early development / experimental**

Currently implemented:
- account creation from master key
- account import from master key
- cryptographic identity verification

Networking, protocol implementation, and UI are under active design.
## Philosophy
This messenger is built on a strict **zero-trust model**.
- no phone numbers
- no email addresses
- no passwords
- no implicit trust in servers

All trust is derived exclusively from cryptography.
The server acts as an untrusted, dumb store for encrypted data and
public keys.

A detailed description of the design principles can be found in
- [docs/philosophy.md](docs/philosophy.md)
## Architecture Overview
The project is structured as a layered system:

- **core/** — messenger-specific logic and rules
- **crypto/** — cryptographic primitives and abstractions
- **shared/** — low-level, dependency-free utilities
- **server/** — untrusted message storage and routing
- **tests/** — unit and integration tests

A high-level architectural overview is available in:
- [docs/architecture.md](docs/architecture.md)
## Building
The project uses **CMake** as its build system.
### Requirements
- C compiler with C11 support (GCC or Clang)
- CMake ≥ 3.16
- libsodium
- cmocka

### Build Steps

```sh
git clone https://github.com/Wemis/messenger.git
cd messenger

cmake -B build/
cmake --build build/
```
The build produces:
- a core static library
- supporting libraries
- test binaries
## Documentation

All project documentation is located in the `docs/` directory.
### Key Documents
- [docs/philosophy.md](docs/philosophy.md) - project principles and trust model
- [docs/architecture.md](docs/architecture.md) - system architecture
- [docs/rfc](docs/RFC) - RFCs documents
### Development Guidelines
- [docs/development/workflow.md](docs/development/workflow.md)
- [docs/development/commits.md](docs/development/commits.md)
- [docs/coding/style.md](docs/coding/style.md)
## Contributing
Contributions are welcome, but the project follows strict architectural  
and security guidelines.

Before contributing, please read:
- [CONTRIBUTING.md](CONTRIBUTING.md)

All contributions must:
- follow the documented coding style
- respect architectural boundaries
- include tests where applicable
- avoid introducing implicit trust assumptions
