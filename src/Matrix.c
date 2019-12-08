#include "Headers/Matrix.h"


void get_data(FILE* file,Matrix *C,Matrix *b,Matrix *A){
    int rows,cols;
    fscanf(file,"%i",&cols);
    fscanf(file,"%i",&rows);

    *C = new_matrix(1,cols);
    *b = new_matrix(rows,1);
    *A = new_matrix(rows,cols);

    //objectif function values : cT
    for(int i=0;i<cols;i++){
        fscanf(file,"%f",&((*C)->values[0][i]));
    }

    //Constrains values : b
    for(int i=0;i<rows;i++){
        fscanf(file,"%f",&((*b)->values[i][0]));
    }
 
    //the A matrix
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            fscanf(file,"%f",&((*A)->values[i][j]));
        }
    }
    
}

Matrix new_matrix(int rows,int cols){
    Matrix m = (Matrix)malloc(sizeof(struct Matrix));
    error_handler(m,"new_matrix");

    m->c = cols;
    m->r = rows;

    m->values = (float**)malloc(rows*sizeof(int*));
    error_handler(m->values,"new_matrix");
    for(int i=0;i<rows;i++){
        m->values[i] = (float*)calloc(cols,sizeof(int));
        error_handler(m->values[i],"new_matrix");
    }
    return m;
}

void free_matrix(Matrix m){
    for(int i=0;i<m->r;i++){
        free(m->values[i]);
    }
    free(m->values);
    free(m);
}

void show_matrix(Matrix m){
    for(int i=0; i < m->r; i++){
        for(int j=0; j < m->c; j++){
            printf("%3.2f ",m->values[i][j]);
        }
        printf("\n");
    }
}

//Matrix operations
float multiply(Matrix left,Matrix right,int line,int col){
    float result = 0;
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


Matrix multiply_matrix_float(float value,Matrix m){
    Matrix result = new_matrix(m->r,m->c);
    for(int i=0;i<m->r;i++){
        for(int j=0;j<m->c;j++){
            result->values[i][j] = m->values[i][j] * value;
        }
    }
    return result;
}


Matrix cofactor(Matrix m,int row,int col){
    Matrix cof = new_matrix(m->r-1,m->c-1);
    int r=0,c=0;
    for(int i=0;i<m->r;i++){
        if(i!=row){
            for(int j=0;j<m->c;j++){
                if(j!=col)
                    cof->values[r][c++] = m->values[i][j];
                if(c==m->c-1){
                    c=0;
                    r++;
                }
            }
        }
    }
    return cof;
}

float determinante_matrix(Matrix m){
    if(m->r == 1)
        return m->values[0][0];
    float D = 0;
    int sign = 1;
    for(int i=0;i<m->c;i++){
        Matrix cof = cofactor(m,0,i);
        D += sign*m->values[0][i]*determinante_matrix(cof);
        free_matrix(cof);
        sign = -sign;
    }

    return D;
}



//utility functions
void error_handler(void* pointer,char* msg){
    if(pointer==NULL){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}