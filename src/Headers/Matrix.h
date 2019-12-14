
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#ifndef H_MATRIX
#define H_MATRIX

struct Matrix{
    int r;//rows
    int c;//columns
    float **values;
};
typedef struct Matrix* Matrix;


typedef struct{
    float optimal_value;
    Matrix xB;
    Matrix xR;
    Matrix cB;
    Matrix cR;
    Matrix B;
    Matrix R;
    Matrix b;
    Matrix cR_cB_Bi_R;
}Linear_Program;


void get_data(FILE* file,Matrix *C,Matrix *b,Matrix *A);



//Matrix operations
Matrix new_matrix(int rows,int cols);
Matrix Multiply(Matrix m1,Matrix m2);
Matrix Add(Matrix m1,Matrix m2);
Matrix Substract(Matrix m1,Matrix m2);
float compute(Matrix left,Matrix right,int line,int col);

Matrix multiply_by_k(float value,Matrix m);

Matrix Transpose(Matrix m);
Matrix Cofactor(Matrix m,int row,int col);
float Determinante(Matrix m);
Matrix Adjoint(Matrix m);
Matrix Inverse(Matrix m);

void Transvection(Matrix m,int i,int j,float a);
void Dilation(Matrix m,int line,float a);
void Permutation(Matrix m,int i,int j);
Matrix Augment(Matrix m,Matrix I);

Matrix Inverse_Gaussian(Matrix m);



Matrix copy(Matrix m);
Matrix base_variables(Matrix A,int m);
Matrix off_base_variables(Matrix A,int m);
Matrix init_base_variables(int m,int n);
Matrix init_off_base_variables(int m,int n);

Matrix Identity(int n);


//Memory managemet
void free2D(float** pointer,int n);
void free_matrix(Matrix m);
void free_memory(Matrix m,...);

//utility functions
void error_handler(void* pointer,char* msg);
Matrix copy_values(Matrix m,Matrix t);

#endif