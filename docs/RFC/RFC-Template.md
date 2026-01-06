# RFC XXXX: Title
Status: Draft | Approved | Rejected | Implemented
Author: Name
Created: YYYY-MM-DD
Last Update: YYYY-MM-DD
## 1. Summary
Brief summary of the proposal in 2–5 sentences.
Explain what is being proposed and why it matters
## 2. Definitions (Optional)
Only used when:

- Used terms with special meaning
- The term in common language does not match the term in the project

Example:

| Master Key | A secret key from which all cryptographic material of an account is deterministically derived      |
| ------------ | -------------------------------------------------------------------------------------------------- |
| Username   | A public, deterministic identifier derived from cryptographic material and used for peer discovery |

## 3. Motivation

Describe the problem this RFC aims to solve.

- What is currently missing or insufficient?
- Why is this change necessary?
- What constraints or goals drive this design?

Avoid proposing solutions in this section
## 4. Goals & Non-Goals

Explicitly list what this RFC intends to achieve and what this RFC does not try to solve.

- clear, testable goals
- security and architectural goals included
- scope creep

Example:
- Deterministic identity derivation
- Ability to verify the authenticity of identity
- Secure message transport
- UI/UX considerations
## 5. Requirements
Requirements must include the following words:
- MUST
- MUST NOT
- SHOULD
- SHOULD NOT
- MAY

Requirements MUST be testable or verifiable.
## 6 Proposed Design
Describe the proposed solution at a conceptual level.

- data flow
- trust boundaries
- interaction between layers

Do not include code here unless absolutely necessary.

Diagrams, schemes are welcome.
## 7. Module Responsibilities

Describe how responsibilities are split between modules.

Example:

- core/
  - owns business rules
  - orchestrates cryptographic operations
- crypto/
  - provides primitives
  - hides implementation details
- shared/
  - string helpers
  - error handling
## 8. Security Considerations

This section is mandatory.

- What are the security assumptions?
- What happens if the server is compromised?
- What attacks are mitigated?
- What attacks are explicitly not mitigated?

If this section is empty, the RFC is incomplete.
## 9. Alternatives Considered (Optional)

Describe alternative designs that were considered and rejected.

For each alternative:
- short description
- reason for rejection

This documents *why* the chosen design exists.
## 10. Impact on Existing Architecture

- Does this RFC change module boundaries?
- Does it introduce new dependencies?
- Does it break compatibility?

Reference `architecture.md` if needed.
## 11. Backward / Forward Compatibility (Optional)

- Is this change backward compatible?
- Does it require versioning?
- Can it coexist with older implementations?

If not applicable, explicitly state so.
## 12. Open Questions

List unresolved questions or decisions that are deferred.

This section may be empty for finalized RFCs.
## 13. References

Links to:
- related RFCs
- design documents