#include "matrix.h"

float A[] = {6,4,8,3};
float B[] = {1,2,3,4,5,6};
float C[] = {2,4,6,1,3,5};

int main() {

    // Sets a to a 2x2 square matrix, then copies the values from 
    // array A into a using =.
    Matrix a(2);
    a = A;

    // Sets b to a 2x3 matrix and fills in the values from array B using the
    // overloaded constructor.
    Matrix b(2,3,B);

    // Sets c to a blank 2x3 matrix then fills in the values using the () 
    // access operator.
    Matrix c(2,3);
    c(1,1) = 2;
    c(1,2) = 4;
    c(1,3) = 6;
    c(2,1) = 1;
    c(2,2) = 3;
    c(2,3) = c(1,3) - c(2,1);

    // Prints the operation given in the homework
    Matrix d = a + (3 * b * c.transpose());
    cout << d;
    return 0;
}