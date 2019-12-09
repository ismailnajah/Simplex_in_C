#include "Headers/Matrix.h"
#define DEFAULT_URL "input.csv"

int main(){
    FILE *file;
    file = fopen(DEFAULT_URL,"r");
    error_handler(file,"main");
    Matrix C,b,A;

    get_data(file,&C,&b,&A);
    int m = A->r;
    Matrix cB,cR,B,R;

    cB = base_variables(C,m);
    B = base_variables(A,m);

    cR = off_base_variables(C,m);
    R = off_base_variables(A,m);

    Matrix Bi = Inverse(B);
    Matrix Bib = Multiply(Bi,b);
    Matrix cBBib = Multiply(cB,Bib);
    //show_matrix(cBBib);

    State(A,cB,cR,B,R,b,NULL);

    free_memory(A,C,b,B,R,cB,cR,NULL);
    fclose(file);
    return 0;
}