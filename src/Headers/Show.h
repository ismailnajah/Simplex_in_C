#ifndef H_SHOW
#define H_SHOW

#include "Matrix.h"

void show_matrix(Matrix m);
void State(Matrix m,...);
int print_row(Matrix m,int row);
void print_table(Linear_Program LP);

void header(Matrix xB_T,Matrix xR);
void body(Matrix xB,Matrix I,Matrix R,Matrix Z,Matrix b);
void footer(Matrix B,Matrix R,Matrix z,float result);

void br(char sep);

#endif