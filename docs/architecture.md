# Messenger Architecture

## 1. Goals and Non-Goals
## Goals
- Deterministic identity based on master key
- Portable core usable across platforms
- Clear separation between crypto and business logic
- Long-term maintainability

## Non-Goals
- UI implementation
- Transport protocol optimization
- Custom cryptographic primitives
## 2. High-Level Overview
The system is composed of a portable core library, a cryptographic
subsystem, and platform-specific clients built on top of the core.
The server operates as a separate component.

## 3. Layered Architecture
The project follows a strict layered architecture:
- UI Layer
- Core Layer
- Crypto Layer
- External Dependencies

Dependencies are allowed only downward.
Reverse dependencies are forbidden.
## 4. Core Module
The core module contains all messenger-specific logic:
- account lifecycle
- business logic
- state machines
- protocol-independent logic

The core module MUST NOT:
- call external libraries directly
- implement cryptographic primitives
- implement UI
- perform I/O
## 5. Crypto Module
The crypto module provides cryptographic primitives used by the core:
- hashing
- key derivation
- signing
- encryption

The crypto module:
- hides implementation details (libsodium)
- exposes stable, minimal APIs
- contains no business logic
## 6. Protocol
The protocol layer is responsible for:
- message transport
- protocol framing
- server communication

It is intentionally decoupled from the core logic.
## 7. Server Architecture
The server is a standalone system responsible for:
- user ID resolution
- username mapping
- message routing

The server does not:
- store private keys
- have keys for users data
- ensures trust
- perform cryptographic identity derivation
## 8. Dependency Rules
- `core` → `crypto` is allowed
- `crypto` → `core` is forbidden
- `core` → `protocol` is allowed
- `protocol` → `crypto` is forbidden
## 9. Shared Utilities
The `shared` module contains low-level, dependency-free utilities
used across multiple layers.

Allowed content:
- string helpers
- byte buffers
- error codes
- small data structures

Restrictions:
- no business logic
- no cryptography
- no networking
- no external dependencies
## 10. Data Flow Examples
1. Core requests identity derivation
2. Crypto derives keys
3. Core derives username and user ID
4. Server verifies identity authenticity
## 11. Testing
Tests are organized in a separate `tests` directory and mirror
the project module structure.

Tests are not part of the production architecture.
## 11. Security Considerations
- Cryptography is delegated to proven libraries
- No custom crypto is implemented
- Master keys never leave the client