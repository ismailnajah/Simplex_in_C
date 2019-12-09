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

    
    State(cR,cB,B,R,NULL);
    show_matrix(Substract( cR , Multiply( cB , Multiply( Inverse(B) , R ) ) ));

    free_memory(A,C,b,B,R,cB,cR,NULL);
    fclose(file);
    return 0;
}