#include "Headers/Matrix.h"
#define MIN(x,y) ((x)<(y)?(x):(y))

void get_data(FILE* file,Matrix *C,Matrix *b,Matrix *A){
    int rows,cols;
    fscanf(file,"%i",&cols);
    fscanf(file,"%i",&rows);

    *C = new_matrix(1,cols);
    *b = new_matrix(rows,1);
    *A = new_matrix(rows,cols);

    //objectif function values : cT
    for(int i=0;i<cols;i++){
        fscanf(file,"%i",&((*C)->values[0][i]));
    }

    //Constrains values : b
    for(int i=0;i<rows;i++){
        fscanf(file,"%i",&((*b)->values[i][0]));
    }
 
    //the A matrix
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            fscanf(file,"%i",&((*A)->values[i][j]));
        }
    }
    
}

Matrix new_matrix(int rows,int cols){
    Matrix m = (Matrix)malloc(sizeof(struct Matrix));
    error_handler(m,"new_matrix");

    m->c = cols;
    m->r = rows;

    m->values = (int**)malloc(rows*sizeof(int*));
    error_handler(m->values,"new_matrix");
    for(int i=0;i<rows;i++){
        m->values[i] = (int*)calloc(cols,sizeof(int));
        error_handler(m->values[i],"new_matrix");
    }
    return m;
}

void show_matrix(Matrix m){
    for(int i=0; i < m->r; i++){
        for(int j=0; j < m->c; j++){
            printf("%3i",m->values[i][j]);
        }
        printf("\n");
    }
}

//Matrix operations
int multiply(Matrix left,Matrix right,int line,int col){
    int result = 0;
    for(int i=0;i < left->c;i++){
        result += left->values[line][i]*right->values[i][col];
    }
    return result;
}

Matrix multiply_matrix(Matrix left,Matrix right){
    if (left->c != right->r){
        printf("Invalid matrix multiplication\n");
        exit(EXIT_FAILURE);
    }
    int cols = right->c;
    int rows =left->r;

    Matrix result = new_matrix(rows,cols);
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            result->values[i][j] = multiply(left,right,i,j);
        }
    }
    return result;
}

//utility functions
void error_handler(void* pointer,char* msg){
    if(pointer==NULL){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}