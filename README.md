# Ninja Virtual Machine

A virtual machine, written in C, that executes bytecode instructions from a custom programming language called **"Ninja"**. Similar to the Java Virtual Machine (JVM), the Ninja Virtual Machine provides an environment where bytecode instructions can be interpreted or executed directly. It includes features such as memory management, garbage collection, and runtime environment handling for executed programs.

## Technologies Used

- **C**: Primary programming language used to implement the virtual machine.
- **Assembly**: For low-level operations and optimizations within the virtual machine.

## Features

- **Execution of Ninja Bytecode**: The VM interprets and executes bytecode instructions from the "Ninja" programming language.
- **Memory Management**: Includes a built-in memory manager for efficient allocation and deallocation.
- **Garbage Collection**: Automatically handles memory cleanup to ensure efficient usage of resources.
- **Runtime Environment**: Provides a runtime environment for executing Ninja programs, managing the program stack, heap, and registers.

## How It Works

1. **Bytecode Interpreter**: The virtual machine reads Ninja bytecode and interprets the instructions to perform operations like arithmetic, logic, and program flow control.
2. **Memory Management**: The VM allocates memory for variables and dynamically handles allocation and deallocation during execution.
3. **Garbage Collection**: Unused memory is automatically reclaimed to avoid memory leaks.
4. **Runtime Environment**: Manages the execution context, including the program stack, heap, and runtime registers.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC or Clang)
- Basic knowledge of C and Assembly programming
- Ninja bytecode files for testing and execution

### Included Test Programs and Tools

The project includes several pre-built binary files (`.bin`) for testing the functionality of the Ninja Virtual Machine. These programs showcase the VM's capabilities and provide examples for experimentation:

- **Fibonacci Sequence Generator**: Calculates the Fibonacci sequence up to a given number.
- **List Reversing Program**: Reverses the elements in a list.
- **Factorial Calculator**: Computes the factorial of a given number.

Additionally, the following tools are included to help work with Ninja programs:

- **`njc` Executable**: Converts source code written in the Ninja programming language (`.nj` files) into assembly code (`.asm` files).
- **`nja` Executable**: Converts assembly code (`.asm` files) into binary code (`.bin` files) that can be executed by the Ninja Virtual Machine.

---

### Usage Instructions

1. **Compile the Virtual Machine**  
   Use a C compiler, such as GCC, to compile the source code:
   ```bash
   gcc -o njvm njvm.c

2. **executing the machine**   
   In order to execute the machine and learn how to use it , In the command line enter:
   ```bash
   ./njvm --help 
    

