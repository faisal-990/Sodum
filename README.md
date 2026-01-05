# Sodum

Sodum is a from-scratch language implementation project built to understand what happens under the hood when code is parsed, analyzed, and executed.

The project focuses on **compiler front-end design**, **AST construction**, and **static analysis foundations**, with future plans for LLVM-based code generation.

---

## Current Status

Sodum is currently in an **MVP front-end stage**, implementing a lexer, recursive-descent parser, structured AST, and visitor-based analysis framework.

---

## ✅ Completed

### Language Front-End
- Handwritten lexer with line-aware tokens
- Recursive descent parser
- Correct operator precedence and associativity
- Parenthesized expressions
- Block-based scoping (`{ ... }`)

### AST Design
- Structural AST (semantic, not a parse tree)
- Clear separation between:
  - Program
  - Block
  - Statements
  - Expressions
- Parentheses eliminated at AST level
- Encapsulation via private members and const getters

### Visitor Infrastructure
- Visitor pattern implemented from scratch
- AST nodes expose only `accept(Visitor&)`
- Visitors are fully decoupled from AST structure
- Enables multiple independent analysis passes

### Tooling
- AST Printer visitor
- Tree-structured output for verification
- Confirms correct parsing and operator precedence

---

## 🚧 In Progress

### Language Features
- `if` statements
- `while` loops
- Boolean expressions and conditions
- Extended expression support

### Static Analysis Foundations
- Symbol tracking
- Scope-aware traversal
- Rule-based AST visitors

---

## 🔮 Planned

### Static Analysis
- Uninitialized variable detection
- Unused variable detection
- Simple data-flow analysis
- Control Flow Graph (CFG) construction
- Rule-based checks inspired by static analysis tools

### LLVM Integration
- AST → LLVM IR lowering
- Expression code generation
- Variable allocation and scoping
- SSA via LLVM

### Code Generation
- Native binary generation
- Optional JIT execution
- Optimization passes via LLVM

---

## Design Decisions

### Handwritten Parser
- Chosen to fully understand grammar-to-AST mapping
- Enables explicit error handling and recovery
- Mirrors early-stage compiler design

### Structural AST
- AST represents meaning, not syntax
- Simplifies analysis and transformations
- Suitable for multiple backends and tools

### Visitor Pattern
- Keeps AST stable and extensible
- Allows independent tools (printers, analyzers, transforms)
- Aligns with real-world static analysis architectures

### Encapsulation First
- AST internals are private
- Visitors operate through well-defined interfaces
- Prevents accidental mutation during analysis

---

## Limitations

- No type checking yet
- No symbol table yet
- Error recovery is minimal
- Not optimized or production-ready

These are intentional trade-offs for correctness and clarity at this stage.

---

## File Format

Source files use the `.sod` extension.

---

## Vision

Sodum is designed as a learning-oriented compiler framework where the same AST can power:

- Interpreters
- Compilers
- Static analyzers
- Security rule engines

The long-term goal is to explore how real-world analysis tools reason about code at scale.

