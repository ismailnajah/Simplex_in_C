#ifndef H_SIMPLEX
#define H_SIMPLEX

#include "Matrix.h"
#include "Show.h"

Pivot find_pivot(Linear_Program LP);

void Simplex(Matrix C,Matrix b,Matrix A);
void insert_pivot_in_base(Linear_Program LP,Pivot p);
float pivot(Linear_Program LP);

//utility functions
void swap(float *a,float *b);



#endif