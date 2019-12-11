#include "Headers/Matrix.h"
#include "Headers/Show.h"
#include <string.h>
#define DEFAULT_URL "input.csv"

int main(){
    char path[1000];
    printf(" URL of the input file (Default: input.csv) :\n");
    scanf("%s",path);

    FILE *file;
    file = fopen(path,"r");
    
    error_handler(file,"main");
    Matrix C,b,A;

    get_data(file,&C,&b,&A);
    int m = A->r;
    Matrix cB,cR,B,R,xB,xR;

    cB = base_variables(C,m);
    B = base_variables(A,m);

    cR = off_base_variables(C,m);
    R = off_base_variables(A,m);

    xB = init_base_variables(B->c,1);
    xR = init_off_base_variables(B->c,R->c);
    show_system(xB,xR,B,R,cB,cR,b);
    /* State(cR,cB,B,R,NULL);
    show_matrix( Multiply(cB , Multiply( Inverse(B) , b ))); */

    free_memory(A,C,b,B,R,cB,cR,xB,xR,NULL);
    fclose(file);
    return 0;
}
