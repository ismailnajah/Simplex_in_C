#ifndef H_SHOW
#define H_SHOW

#include "Matrix.h"


void show_matrix(Matrix m);
void State(Matrix m,...);
int print_row(Matrix m,int row);
void show_system(Matrix xB,Matrix xR,Matrix B,Matrix R,Matrix cB,Matrix cR,Matrix b);

void header(Matrix xB_T,Matrix xR);
void body(Matrix xB,Matrix I,Matrix R,Matrix Z,Matrix b);
void footer(Matrix B,Matrix R,Matrix z,Matrix result);

void br(char sep);

#endif