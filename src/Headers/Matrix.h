#ifndef H_MATRIX
#define H_MATRIX

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Matrix{
    int r;//rows
    int c;//columns
    float **values;
};
typedef struct Matrix* Matrix;

Matrix new_matrix(int rows,int cols);
void show_matrix(Matrix m);
void free_matrix(Matrix m);

void get_data(FILE* file,Matrix *C,Matrix *b,Matrix *A);

//Matrix operations
Matrix multiply_matrix(Matrix m1,Matrix m2);
float multiply(Matrix left,Matrix right,int line,int col);

Matrix multiply_matrix_float(float value,Matrix m);

Matrix cofactor(Matrix m,int row,int col);
float determinante_matrix(Matrix m);


//utility functions
void error_handler(void* pointer,char* msg);

#endif