# Custom Stack Implementation in C++

This project was developed in C++ and implements a generic custom Stack class (stack.hpp) with all the typical functionalities of a stack data structure.
 Project Overview

The implementation is designed to be efficient and modular. Instead of relying on a standard dynamic list (like std::list or std::vector), this project implements the stack using a dynamic array. This design choice allows for direct memory management and optimized element access.

The project follows a clean structure with a dedicated header file for the template class and a Makefile for easy compilation.
 Key Features

    Dynamic Array Implementation: The stack manages memory manually using a dynamic array, ensuring deep understanding of memory allocation.

Generic Programming: The stack<T> class is a template, supporting any data type.

Standard Operations: Includes push, pop, size, and checks for empty/full states.

Advanced Methods:

    load_from_range: Loads elements from a generic iterator range.

    filter_out: Returns a new stack containing only elements satisfying a specific predicate .

    transform: Applies a function to all elements in the stack .

Iterators: Implements forward iterators (iterator and const_iterator) to traverse the stack.

Error Handling: Uses std::overflow_error and std::underflow_error for safe operations.

## File Structure

    stack.hpp: Contains the declaration and implementation of the template class stack.

    main.cpp: Contains unit tests and usage examples (fundamental methods, iterators, custom functors) .

    Makefile: script to automate the build process.

    Doxyfile: Configuration file to generate documentation using Doxygen .

## Build and Run

A Makefile is included to simplify the compilation process.

    Compile the project:
    Bash

make

Run the executable:
Bash

    ./main.exe

## Documentation

A Doxyfile is included to automatically generate project documentation using Doxygen. This makes the code easier to understand and maintain by providing detailed descriptions of classes and methods.

To generate the documentation, run:
Bash

doxygen Doxyfile
