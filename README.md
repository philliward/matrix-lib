# Matrix
Author: Phillip Ward (UMBC CMSC 313 Mon/Wens 2:30-345)

Matrix is a C/C++ library that implements a Matrix object in each language that can handle addition, subtraction, scalar multiplication, matrix multiplication, and transposing. Users can create, display, and perform operations using matrices.

### Files

Project files are contained in `src/c` and `src/cplusplus`. Each folder contains three files of note: `main.c(pp)`, `matrix.h`, and `matrix.c(pp)`. `main` is the "testing" file, while `matrix.h/c(pp)` is the library file. The parentheses indicate that the C version uses `.c` files and the C++ version uses `c++` files.

### Build Instructions

Download the three relevant files in the language of choice (either C or C++), place them in the same folder, and run this command: `gcc -Wall main.c(pp) -o main`. This will compile the demo program of the library. To add Matrix to another project, adding the line `#include "matrix.h` in your program and putting the files in the project folder is enough.

Matrix was tested by implementing matrices of various sizes and shapes, then comparing the program output visually with the results given by online calculators. It was also tested for memory leaks, of which the C version has many if any matrices created are not freed.
