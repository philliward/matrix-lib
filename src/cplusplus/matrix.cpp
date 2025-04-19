#ifndef MATRIX_B
#define MATRIX_B

#include "matrix.h"

// Matrix()
//
// Default constructor. Initializes all member variables with default values.
Matrix::Matrix(): m_rows(0), m_cols(0), m_size(0), m_vals(nullptr) {}


// ~Matrix()
//
// Deconstructor. Deletes dynamic memory used by the class.
Matrix::~Matrix() {
    clear();
}


// Matrix(int, int)
//
// Overloaded rows/cols constructor. Creates an empty matrix with the given
// amount of rows and columns and fills it with zeroes.
Matrix::Matrix(int rows, int cols): Matrix() {
    m_rows = max(rows,0); m_cols = max(cols,0); m_size = m_rows * m_cols;
    m_vals = (element*) malloc(sizeof(element) * m_size);
    for (int i = 0; i < m_size; i++) m_vals[i] = 0;
}


// Matrix(int, int, int*)
//
// Overloaded rows/cols/vals constructor. Creates a matrix of the given size
// and passes the values from the element array into it, filling each row
// before moving on to the columns.
Matrix::Matrix(int rows, int cols, element* vals): Matrix(rows, cols) {
    *this = vals;
}


// Matrix(const Matrix& rhs)
//
// Copy constructor for the matrix class. Creates a matrix that's a copy
// of the given matrix.
Matrix::Matrix(const Matrix& rhs): Matrix() {
    *this = rhs;
}


// Matrix(int)
//
// Overloaded constructor for the matrix class. Sets this matrix to a square
// identity matrix of the given size.
Matrix::Matrix(int size): Matrix(size, size) {
    for (int i = 0; i < size; i++) m_vals[size * i + i] = 1;
}


// const Matrix& = const Matrix&
//
// Equality operator for setting one matrix to be a deep copy of another.
const Matrix& Matrix::operator= (const Matrix& rhs) {
    m_rows = rhs.m_rows; m_cols = rhs.m_cols; m_size = rhs.m_size;
    if (m_vals != nullptr) free(m_vals);

    m_vals = (element*) malloc(sizeof(element) * m_size);

    for (int i = 0; i < m_size; i++) m_vals[i] = rhs.m_vals[i];

    return *this;
}


// const Matrix& = const element*
//
// Equality operator for filling a matrix with values from an array.
// Size of array assumed to match size of matrix, no checking will occur.
const Matrix& Matrix::operator= (const element* rhs) {
    for (int i = 0; i < m_rows; i++) for (int j = 0; j < m_cols; j++) {
        m_vals[i * m_cols + j] = rhs[i * m_cols + j];
    }
    return *this;
}


// const Matrix& += const Matrix&
//
// Addition equality operator for adding one matrix to this one. Adds the
// contents of the passed matrix to this one, element by element.
// Throws an exception if matrixes are of differing size.
const Matrix& Matrix::operator+= (const Matrix& rhs) {
    if (m_rows != rhs.m_rows && m_cols != rhs.m_cols) throw(domain_error("Size misalignment."));
    for (int i = 0; i < m_size; i++) m_vals[i] += rhs.m_vals[i];
    return *this;
}


// const Matrix& -= const Matrix&
//
// Subtraction equality operator for subtracting one matrix to this one.
// Subtracts the contents of the passed matrix from this one, element
// by element. Throws an exception if matrixes are of differing size.
const Matrix& Matrix::operator-= (const Matrix& rhs) {
    if (m_rows != rhs.m_rows && m_cols != rhs.m_cols) throw(domain_error("Size misalignment."));
    for (int i = 0; i < m_size; i++) m_vals[i] -= rhs.m_vals[i];
    return *this;
}


// const Matrix& *= const Matrix&
//
// Multiplication equality operator. Multiplies this matrix by the passed
// matrix, throws an exception for an illegal multiplication.
const Matrix& Matrix::operator*= (const Matrix& rhs) {
    *this = *this * rhs;
    return *this;
}


// const Matrix& *= const element
//
// Multiplication equality operator for scalar multiplication.
// Multiplies all elements of this matrix by the given scalar.
const Matrix& Matrix::operator*= (const element rhs) {
    for (int i = 0; i < m_rows; i++) for (int j = 0; j < m_cols; j++) {
        m_vals[i * m_cols + j] *= rhs;
    }
    return *this;
}


// Matrix * element
//
// Multiplication operator for scalar multiplication.
// Returns a matrix representing this matrix multiplied by the given value.
Matrix Matrix::operator* (const element rhs) const {
    Matrix out(m_rows, m_cols, m_vals);
    out *= rhs;
    return out;
}


// Matrix * const Matrix&
//
// Multiplication operator for matrix multiplication.
// Returns the matrix representing this matrix multiplied by the given matrix.
// Performs a standard matrix product.
// Throws an exception for illegal multiplication.
Matrix Matrix::operator* (const Matrix& rhs) const {
    if (m_cols != rhs.m_rows) throw(domain_error("Size misalignment."));

    Matrix out(m_rows, rhs.m_cols);

    for (int i = 0; i < out.m_rows; i++) {
        for (int j = 0; j < out.m_cols; j++) {
            element a = 0;
            for (int n = 0; n < m_cols; n++) a += 
                m_vals[m_cols * i + n] * 
                rhs.m_vals[rhs.m_cols * n + j];
            out.m_vals[i * out.m_cols + j] = a;
        }
    }

    return out;
}


// Matrix + const Matrix&
//
// Addition operator.
// Returns this matrix + the given matrix.
// Throws an exception if matrixes are of differing size.
Matrix Matrix::operator+ (const Matrix& rhs) const {
    Matrix out = *this;
    out += rhs;
    return out;
}


// Matrix - const Matrix&
//
// Subtraction operator.
// Returns this matrix - the given matrix.
// Throws an exception if matrixes are of differing size.
Matrix Matrix::operator- (const Matrix& rhs) const {
    Matrix out = *this;
    out -= rhs;
    return out;
}


// Matrix(int, int) const element
//
// Returns the element at the given location as a constant for reference.
// Throws an exception if an illegal access occurs.
const element Matrix::operator() (int row, int col) const {
    if (row < 0 || row > m_rows || col < 0 || col >= m_cols) throw out_of_range("Out of matrix bounds.");
    return m_vals[row * m_cols + col];
}



// Matrix(int, int) element*
//
// Returns a reference to the matrix at the given row/col location for assignment.
// Throws an exception if an illegal access occurs.
element& Matrix::operator() (int row, int col) {
    if (row < 1 || row > m_rows || col < 1 || col > m_cols) throw out_of_range("Out of matrix bounds.");
    return m_vals[(row - 1) * m_cols + col - 1];
}


// Matrix transpose()
//
// Returns the transpose of this matrix as a matrix object.
Matrix Matrix::transpose() const {
    Matrix out = Matrix(m_cols, m_rows);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            out.m_vals[j * m_rows + i] = m_vals[i * m_cols + j];
        }
    }
    return out;
}


// clear() void
//
// Resets all member variables to 0 and frees all dynamic memory.
void Matrix::clear () {
    m_size = 0;
    m_rows = 0;
    m_cols = 0;
    if (m_vals != nullptr) free(m_vals);
    m_vals = nullptr;
}


// ostream& << const Matrix&
//
// Ostream operator, outputs the contents of this matrix in a visual form.
ostream& operator<<(ostream& sout, const Matrix& rhs) {
    for (int i = 0; i < rhs.m_rows; i++) {
        sout << "[";
        for (int j = 0; j < rhs.m_cols; j++) {
            sout << right << setw(8) << rhs.m_vals[i * rhs.m_cols + j];
        }
        sout << "]\n";
    }
    sout << endl;
    return sout;
}


// isSquare() bool
//
// Returns whether or not this is a square matrix.
bool Matrix::isSquare() const {
    return m_cols == m_rows;
}

#endif