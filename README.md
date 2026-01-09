# Sodum

Sodum is a from-scratch systems language implementation project built to understand the journey of code from raw text to native machine execution.

The project has evolved from a pure front-end experiment into a **vertically integrated compiler toolchain** using LLVM as a backend.

---

## Current Status

Sodum has reached its **LLVM MVP Stage**. It can now lex, parse, and compile multiple statements—including variable declarations, assignments, and complex arithmetic—into native executable binaries.

---

## ✅ Completed

### Language Infrastructure
- **Handwritten Lexer:** Line-aware tokenization with support for keywords, literals, and operators.
- **Recursive Descent Parser:** Handles operator precedence (BODMAS), block scoping, and statement sequencing.
- **Structural AST:** A clean, semantic representation of the program logic, decoupled from concrete syntax.

### LLVM Backend & CodeGen
- **AST to LLVM IR Lowering:** Implemented via the Visitor Pattern.
- **Memory Management:** Stack-based variable allocation using `alloca`, `load`, and `store` instructions.
- **Expression Support:** Full support for integer math (+, -, *, /) and nested parenthesized expressions.
- **Symbol Table:** Integrated symbol tracking to bridge AST identifiers with LLVM memory addresses.

### Compiler Driver (The Toolchain)
- **Automated Pipeline:** A single command orchestrates the entire flow: `Sodum Source -> LLVM IR -> Clang -> Native Binary`.
- **System Agnostic:** Automatically detects available system compilers (`clang`, `gcc`, or `cc`).
- **Safety Gatekeeper:** Prevents code generation if the parser detects syntax errors.

---

## 🚧 In Progress 

### Language Features
- **Boolean Logic:** Comparison operators (`==`, `>`, `<`, etc.) and Boolean literals.
- **Print statements** Have a function to print to the terminal to show the state.
- **Control Flow:** `if` statements and `while` loops using LLVM Basic Blocks and Branching.
- **Function Support:** Moving beyond a single `@main` block to user-defined functions.

---

## 🔮 Planned

### Static Analysis
- Uninitialized/Unused variable detection via AST traversal.
- Scope-aware validation.
- Control Flow Graph (CFG) construction.

### Optimization
- Leveraging LLVM's optimization passes (-O2, -O3).
- SSA (Static Single Assignment) form refinements.

---

## How to Run

1. **Build the compiler:**
   ```bash
   mkdir build && cd build
   cmake ..
   make


2. **Compile a sodum script:**
    ```bash
    ./sodum examples/test.sod

3. **Execute the Result:**
    ```bash
    ./sodum
    echo $? #Currently check the result via exit code 
