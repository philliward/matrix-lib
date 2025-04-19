#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <string>

class Matrix;

using namespace std;

// I'm assuming the matrix holds floats but that could change.
typedef float element;

class Matrix {
    public:

    // Constructors

    Matrix();
    ~Matrix();
    Matrix(int, int);
    Matrix(int, int, element*);
    Matrix(const Matrix&);
    Matrix(int);

    // Equality operators
    // Sets this matrix to the product of the given operation.
    const Matrix& operator= (const Matrix&);

    const Matrix& operator= (const element*);


    const Matrix& operator+= (const Matrix&);
    const Matrix& operator-= (const Matrix&);
        
    const Matrix& operator*= (const Matrix&);
    const Matrix& operator*= (const element);

    // Non-equality operators
    // Returns a Matrix object representing the product of the operation.
    Matrix operator* (const Matrix&) const;
    Matrix operator* (const element) const;
    friend Matrix operator* (const element lhs, const Matrix& rhs) {
        Matrix out(rhs);
        out *= lhs;
        return out;
    }

    Matrix operator+ (const Matrix&) const;
    Matrix operator- (const Matrix&) const;
    const element operator() (int, int) const;
    element& operator() (int, int);

    // Non-operator functions
    Matrix transpose() const;
    bool isSquare() const;

    void clear();
    friend ostream& operator<<(ostream&, const Matrix&);

    private:
    int m_rows;
    int m_cols;
    int m_size;
    element* m_vals;
};

#include "matrix.cpp"
#endif