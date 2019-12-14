#ifndef H_SIMPLEX
#define H_SIMPLEX

#include "Matrix.h"
#include "Show.h"

int find_pivot_row(Matrix R,Matrix b,int col);
int find_pivot_col(Matrix cR);

void Simplex(Matrix C,Matrix b,Matrix A);
void insert_pivot_in_base(Linear_Program LP,int p_row,int p_col);
float pivot(Linear_Program LP);

//utility functions
void swap(float *a,float *b);



#endif