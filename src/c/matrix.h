#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define max(a,b) (a > b ? a : b)

// I'm assuming these matrices store floats.
typedef float element;

struct Matrix {
    int m_rows;
    int m_cols;
    int m_size;
    element* m_vals;
} const Matrix_default = {0,0,0,NULL};

typedef struct Matrix Matrix;


// Matrix_setRowsCols(Matrix*, int, int) void
//
// Sets the passed matrix to the given size, frees any memory previously
// held by it, and fills it with zeroes. Also works as a functional reset
// of the matrix.
void Matrix_setRowsCols(Matrix*, int, int);


// Matrix_setRowsColsVals(Matrix*, int, int, element*) void
//
// Sets the passed matrix to the given size and fills it with values from
// the passed elements array. Note: This function creates a deep copy of the
// passed array and stores that, it does not merely change a pointer.
void Matrix_setRowsColsVals(Matrix*, int, int, element*);


// Matrix_setIdentity(Matrix*, int) void
//
// Sets the passed matrix to the identity matrix of the given size.
void Matrix_setIdentity(Matrix*, int);


// Matrix_free(Matrix*) void
//
// Frees all data associated with a matrix and resets all of its members.
// Used to clear heap memory used with the matrix and prevent leaks.
void Matrix_free(Matrix*);


// Matrix_add(Matrix*, Matrix*, Matrix*) bool
//
// Adds two matrices together and stores the result in the third argument.
// Returns true if the addition was successful and false otherwise.
bool Matrix_add(Matrix*, Matrix*, Matrix*);


// Matrix_subtract(Matrix*, Matrix*, Matrix*) bool
//
// Subtracts two matrices from each other and stores the result in the third
// passed matrix. Returns true if the process was successful and false otherwise.
bool Matrix_subtract(Matrix*, Matrix*, Matrix*);


// Matrix_multiplyByScalar(Matrix*, element, Matrix*) bool
//
// Multiplies a matrix by the given scalar and stores the result in the third
// argument. Always returns true.
bool Matrix_multiplyByScalar(Matrix*, element, Matrix*);


// Matrix_multiplyByMatrix(Matrix*, Matrix*, Matrix*) bool
//
// Left-multiplies the second matrix by the first and stores the resulting
// matrix in the third argument. Returns true if this was successful and false
// otherwise.
bool Matrix_multiplyByMatrix(Matrix*, Matrix*, Matrix*);


// Matrix_transpose(Matrix*, Matrix*) void
//
// Takes the transpose of the matrix in the first argument and stores it in
// the second argument.
void Matrix_transpose(Matrix*, Matrix*);


// Matrix_dump(Matrix*) void
//
// Dumps the contents of a matrix in viewable form.
void Matrix_dump(Matrix*);

#include "matrix.c"
#endif