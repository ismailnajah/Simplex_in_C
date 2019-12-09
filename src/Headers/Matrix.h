
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#ifndef H_MATRIX
#define H_MATRIX
#define FLOAT_FORMAT "%3.0f"
#define SPACE_FORMAT "   "




struct Matrix{
    int r;//rows
    int c;//columns
    float **values;
};
typedef struct Matrix* Matrix;

Matrix new_matrix(int rows,int cols);
void show_matrix(Matrix m);

void free_matrix(Matrix m);
void free_memory(Matrix m,...);

void get_data(FILE* file,Matrix *C,Matrix *b,Matrix *A);

//Matrix operations
Matrix Multiply(Matrix m1,Matrix m2);
float compute(Matrix left,Matrix right,int line,int col);

Matrix multiply_by_k(float value,Matrix m);

Matrix Cofactor(Matrix m,int row,int col);
float Determinante(Matrix m);
Matrix Adjoint(Matrix m);
Matrix Inverse(Matrix m);
Matrix Transpose(Matrix m);

Matrix base_variables(Matrix A,int m);
Matrix off_base_variables(Matrix A,int m);


Matrix Identity(int n);



void State(Matrix m,...); 
int print_row(Matrix m,int row);

//utility functions
void error_handler(void* pointer,char* msg);

#endif