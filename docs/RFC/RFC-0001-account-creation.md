# RFC-001: Account Creation Model
## Status: `Implemented`
## Motivation
Account creation is a core operation of the messenger and defines:
- user identity model
- cryptographic trust base
- long-term compatibility of keys and accounts
## Scope
### In scope
- Account creation flow
- Identity format
- Key generation
### Out of scope
- Authentication protocol
- Messaging protocol
- UI menu
## Definitions

| Term         | Meaning                             |
| ------------ | ----------------------------------- |
| `Account`    | Logical identity of a user          |
| `Keypair`    | Asymmetric cryptographic keypair    |
| `Username`   | Public representation of an account |
| `Master Key` | 32 bytes length array               |
| `User ID`    | Constant based on public keys       |
## Requirements
### Functional Requirements
1. `Keypairs` must be determined from randomly generated `Master Key`
2. `Username` must contains security tag so that users can verify identity
3. `User ID` must be permanent and based on public keys
4. Max length for `Name` is 64 bytes
5. `Username` length is 32 bytes
6. All account data must be signed by asymmetric algorithm `Ed25519` 
### Security Requirements
1. An account must be created fully offline
2. Cryptographic operations must be isolated in `crypto/`
3. Memory containing secrets must be wiped after use
## Account Model
### Identity Components
- Name
- Username
- User ID
- Public key for signatures
- Public key for encryption
- Signature
## Account Creation Flow
<img src="https://github.com/Wemis/messenger/blob/master/docs/images/RFC-001-account-creation-scheme.png">

## Module Responsibilities
### core/
- Validates input
- Coordinates account creation
- Derives `Username` and `User ID`
- Stores account data
### crypto/
- `Keypair` generation
- Secure random generation
- Key serialization
- Memory wiping of secrets
## Acceptance Criteria
- Account can be created without network access
- Private keys never appear in logs
- Memory containing secrets is wiped
- RFC fully implemented and referenced in code and commits
