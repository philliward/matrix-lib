#include "matrix.h"

float A[] = {6,4,8,3};
float B[] = {1,2,3,4,5,6};
float C[] = {2,4,6,1,3,5};

int main() {
    // Creates matrix B.
    Matrix b = Matrix_default;
    Matrix_setRowsColsVals(&b,2,3,B);

    // Multiplies B by 3 and stores the result in a seperate matrix.
    Matrix b3 = Matrix_default;
    Matrix_multiplyByScalar(&b, 3, &b3);

    // Creates matrix C, then takes its transpose.
    Matrix c = Matrix_default;
    Matrix_setRowsColsVals(&c, 2,3,C);
    Matrix c_transpose = Matrix_default;
    Matrix_transpose(&c, &c_transpose);

    // Multiplies the prior two matricies together.
    Matrix_multiplyByMatrix(&b3, &c_transpose, &b);

    // Creates matrix A.
    Matrix a = Matrix_default;
    Matrix_setRowsColsVals(&a,2,2,A);

    // Creates matrix D and uses it to store the outcome of the multiplication.
    Matrix d = Matrix_default;
    Matrix_add(&a, &b, &d);

    // Prints the contents of matrix D.
    Matrix_dump(&d);


    // Frees all used memory.
    Matrix_free(&b); Matrix_free(&b3); Matrix_free(&c); Matrix_free(&c_transpose); Matrix_free(&a); Matrix_free(&d);
    return 0;
}