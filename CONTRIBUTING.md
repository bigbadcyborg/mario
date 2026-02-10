# Contributing Guide

Thank you for contributing to this project. This guide defines how work should be planned, implemented, reviewed, and merged.

## Branching Strategy

- Always create a topic branch from the default integration branch.
- Branch names must follow the pattern: `feature/<short-description>`.
  - Examples:
    - `feature/player-collision-fix`
    - `feature/network-latency-profiling`
- Direct commits to the integration branch are not allowed.
- Every change must be merged through a Pull Request (PR).

## Pull Request Requirements

- PRs must have a clear scope and a concise title.
- PR descriptions should include:
  - Problem statement
  - Proposed solution
  - Validation steps
  - Any follow-up work (if applicable)

## Code Review Checklist

Reviewers and authors should verify all of the following before approving:

- **SOLID principles are respected**:
  - Single Responsibility Principle
  - Open/Closed Principle
  - Liskov Substitution Principle
  - Interface Segregation Principle
  - Dependency Inversion Principle
- No monolithic functions:
  - Functions should be focused, readable, and maintainable.
  - Complex behavior should be decomposed into small composable units.
- Tests are required:
  - New logic is covered with tests where test infrastructure exists.
  - Bug fixes include regression tests when feasible.
  - Existing tests continue to pass.
- Naming and structure are clear and consistent.
- Error handling and edge cases are considered.
- Documentation is updated when behavior or architecture changes.

## Definition of Done

A task is considered done only when all of the following are true:

1. **Build passes** in the target development environment.
2. **Tests pass** (unit/integration/regression as applicable).
3. **Documentation is updated**, including relevant technical or usage notes.

If any of these are incomplete, the task is not done and should not be merged.
