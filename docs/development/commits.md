# Commit Policy
## General Rules
- One commit = one logical change
- Commits must compile
- Tests must pass
## Commit Message Formats
### Standard (Recommended)
```
<module>:<short summary>

<optional detailed explanation>
```
Used when:
- Implementing features
- Contains business logic
- Fixing bug
- Affecting API 

Example:
```
core: introduce account creation flow

Core now manages identity creation without
direct dependency on crypto backend.
```
### Short
```
<short summary>
```
Used when:
- commits doesn't contain business logic
- temporary commits
- less valuable commits
Examples:
- `Fix typo`
- `Reformat files`
- `Update comments`
- `Remove unused imports`
## Commit Examples
### Good
- `core: implement account creation and import`
- `docs: update memory ownership rules`
- `Update README.md`
### Bad
- `Fix stuff`
- `many changes`
- `Update`
## Forbidden
- Broken builds
- Broken tests