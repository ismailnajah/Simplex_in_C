#include "Headers/Matrix.h"
#define DEFAULT_URL "input.csv"

int main(){
    FILE *file;
    file = fopen(DEFAULT_URL,"r");
    error_handler(file,"main");
    //Matrix C,b,A;

    //get_data(file,&C,&b,&A);

    Matrix x = new_matrix(3,3);
    
    x->values[0][0] = 1;
    x->values[0][1] = 2;
    x->values[0][2] = 3;

    x->values[1][0] = 4;
    x->values[1][1] = 1;
    x->values[1][2] = 5;

    x->values[2][0] = 4;
    x->values[2][1] = 0;
    x->values[2][2] = 1;

    show_matrix(x);
    printf("\n");
    Matrix invx = Inverse(x);
    show_matrix(invx);

    /* free_matrix(A);
    free_matrix(C);
    free_matrix(b); */
    free_matrix(x);
    free_matrix(invx);

    fclose(file);
    return 0;
}