#include "Headers/Matrix.h"
#define DEFAULT_URL "input.csv"

int main(int argc,char* argv[]) {
    FILE *file;
    file = fopen(DEFAULT_URL,"r");
    error_handler(file,"main");
    Matrix C,b,A;

    get_data(file,&C,&b,&A);

    Matrix x = new_matrix(3,3);
    x->values[0][0] = 1;
    x->values[0][1] = 0;
    x->values[0][2] = 0;

    x->values[1][0] = 0;
    x->values[1][1] = 1;
    x->values[1][2] = 0;

    x->values[2][0] = 0;
    x->values[2][1] = 0;
    x->values[2][2] = 1;

    show_matrix(A);


    Matrix tA=transpose(A);
    show_matrix(tA);

    Matrix B=multiply_matrix(A,tA);
    show_matrix(B);

    Matrix I=Inverse(B);
    show_matrix(Inverse(B));
    
    free_matrix(B);
    free_matrix(A);
    free_matrix(C);
    free_matrix(b);
    free_matrix(x);
    free_matrix(I);
    free_matrix(tA);
    fclose(file);
    return 0;
}