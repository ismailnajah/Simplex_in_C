#include "Headers/Simplex.h"
#include <string.h>
#define DEFAULT_URL "input.csv"

int main(){
    /* char path[1000];
    printf(" URL of the input file (Default: input.csv) : ");
    scanf("%s",path); */

    FILE *file;
    file = fopen(DEFAULT_URL,"r");
    
    error_handler(file,"main");
    Matrix C,b,A;

    get_data(file,&C,&b,&A);
    Simplex(C,b,A);
    //State(B,R,cB,cR,NULL);

    free_memory(A,C,b,NULL);
    fclose(file);
    return 0;
}
