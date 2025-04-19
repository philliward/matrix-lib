#ifndef MATRIX_B
#define MATRIX_B

#include "matrix.h"


void Matrix_setRowsCols(Matrix *t, int rows, int cols) {
    Matrix_free(t);
    t->m_rows = max(rows,0); t->m_cols = max(cols,0); 
    t->m_size = t->m_rows * t->m_cols; t->m_vals = NULL;
    t->m_vals = (element*) malloc(t->m_size * sizeof(element));
    for (int i = 0; i < t->m_size; i++) t->m_vals[i] = 0;
}


void Matrix_setRowsColsVals(Matrix *t, int rows, int cols, element* vals) {
    Matrix_setRowsCols(t, rows, cols);
    for (int i = 0; i < t->m_size; i++) t->m_vals[i] = vals[i];
}


void Matrix_setIdentity(Matrix *t, int size) {
    Matrix_setRowsCols(t, size, size);
    int a = max(size,0) + 1;
    for (int i = 0; i < t->m_size; i += a) t->m_vals[i] = 1;
}


void Matrix_free(Matrix *t) {
    if (t->m_vals != NULL) free(t->m_vals);
    t->m_cols = 0; t->m_rows = 0; t->m_size = 0; t->m_vals = NULL;
}



bool Matrix_add(Matrix *lhs, Matrix *rhs, Matrix *out) {
    if (lhs->m_rows != rhs->m_rows || lhs->m_cols != rhs->m_cols) return false;
    Matrix_setRowsCols(out, lhs->m_rows, lhs->m_cols);

    for (int i = 0; i < out->m_rows; i++) for (int j = 0; j < out->m_cols; j++) 
        out->m_vals[i * out->m_cols + j] = 
            lhs->m_vals[i * out->m_cols + j] + 
            rhs->m_vals[i * out->m_cols + j];
    return true;
}


bool Matrix_subtract(Matrix *lhs, Matrix *rhs, Matrix *out) {
    if (lhs->m_rows != rhs->m_rows || lhs->m_cols != rhs->m_cols) return false;
    Matrix_setRowsCols(out, lhs->m_rows, lhs->m_cols);

    for (int i = 0; i < out->m_rows; i++) for (int j = 0; j < out->m_cols; j++) 
        out->m_vals[i * out->m_cols + j] = 
            lhs->m_vals[i * out->m_cols + j] - 
            rhs->m_vals[i * out->m_cols + j];
    return true;
}


bool Matrix_multiplyByScalar(Matrix *lhs, element rhs, Matrix *out) {
    Matrix_setRowsCols(out, lhs->m_rows, lhs->m_cols);

    for (int i = 0; i < out->m_rows; i++) for (int j = 0; j < out->m_cols; j++) 
        out->m_vals[i * out->m_cols + j] = lhs->m_vals[i * lhs->m_cols + j] * rhs;
    return true;
}


bool Matrix_multiplyByMatrix(Matrix *lhs, Matrix *rhs, Matrix *out) {
    if (lhs->m_cols != rhs->m_rows) return false;
    Matrix_setRowsCols(out, lhs->m_rows, rhs->m_cols);

    for (int i = 0; i < out->m_rows; i++) {
        for (int j = 0; j < out->m_cols; j++) {
            element a = 0;
            for (int n = 0; n < lhs->m_cols; n++) a += 
                lhs->m_vals[lhs->m_cols * i + n] * 
                rhs->m_vals[rhs->m_cols * n + j];
            out->m_vals[i * out->m_cols + j] = a;
        }
    }
    return true;
}


void Matrix_transpose(Matrix *t, Matrix *out) {
    Matrix_setRowsCols(out, t->m_cols, t->m_rows);
    for (int i = 0; i < t->m_rows; i++) for (int j = 0; j < t->m_cols; j++)
            out->m_vals[j * t->m_rows + i] = t->m_vals[i * t->m_cols + j];
}


void Matrix_dump(Matrix* t) {
    printf("\n");
    for (int i = 0; i < t->m_rows; i++) {
        printf("[");
        for (int j = 0; j < t->m_cols; j++) printf(" %8.2f", t->m_vals[i * t->m_cols + j]);
        printf("]\n");
    }
}

#endif