#include "Headers/Matrix.h"
#define DEFAULT_URL "input.csv"

int main(){
    FILE *file;
    file = fopen(DEFAULT_URL,"r");
    error_handler(file,"main");
    Matrix C,b,A;

    get_data(file,C,b,A);
    show_matrix(C);

    
    fclose(file);
    return 0;
}