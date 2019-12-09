#include "Headers/Matrix.h"
#define FLOAT_FORMAT "%6.2f"
#define SPACE_FORMAT "      "

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

void show_matrix(Matrix m){
    for(int i=0; i < m->r; i++){
        for(int j=0; j < m->c; j++){
            printf(FLOAT_FORMAT,m->values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



Matrix base_variables(Matrix A,int m){
    Matrix B = new_matrix(A->r,m);
    for(int i=0; i < A->r; i++){
        for(int j=0; j < m; j++){
            B->values[i][j] = A->values[i][j];
        }
    }
    return B;
}

Matrix off_base_variables(Matrix A,int m){
    int c = A->c - m;
    Matrix R = new_matrix(A->r,c);

    for( int i=0; i < A->r; i++){
        for( int j=m; j < A->c; j++){
            R->values[i][j-m] = A->values[i][j];
        }
    }
    return R;
}

//Matrix operations
float compute(Matrix left,Matrix right,int line,int col){
    float result = 0;
    for(int i=0;i < left->c;i++){
        result += left->values[line][i]*right->values[i][col];
    }
    return result;
}

Matrix Multiply(Matrix left,Matrix right){
    if (left->c != right->r){
        printf("Invalid matrix multiplication\n");
        exit(EXIT_FAILURE);
    }
    int cols = right->c;
    int rows =left->r;

    Matrix result = new_matrix(rows,cols);
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            result->values[i][j] = compute(left,right,i,j);
        }
    }
    return Return(left,result);
}

Matrix multiply_by_k(float value,Matrix m){
    for(int i=0;i<m->r;i++){
        for(int j=0;j<m->c;j++){
            m->values[i][j] *= value;
        }
    }
    return m;
}

Matrix Add(Matrix m1,Matrix m2){
    for(int i=0;i<m1->r;i++){
        for(int j=0;j<m1->c;j++){
            m1->values[i][j] += m2->values[i][j];
        }
    }
    return m1;
}

Matrix Substract(Matrix m1,Matrix m2){
    for(int i=0;i<m1->r;i++){
        for(int j=0;j<m1->c;j++){
            m1->values[i][j] -= m2->values[i][j];
        }
    }
    return m1;
}

Matrix Cofactor(Matrix m,int row,int col){
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

float Determinante(Matrix m){
    if(m->r == 1)
        return m->values[0][0];
    float D = 0;
    int sign = 1;
    for(int i=0;i<m->c;i++){
        Matrix cof = Cofactor(m,0,i);
        D += sign*m->values[0][i]*Determinante(cof);
        free_matrix(cof);
        sign = -sign;
    }

    return D;
}

Matrix Adjoint(Matrix m){
    Matrix temp = new_matrix(m->r,m->c);
    int sign = 1;
    for(int row=0;row < temp->r;row++){
        for(int col=0;col<temp->c;col++){
            Matrix cof = Cofactor( m, row, col);
            temp->values[row][col] = sign * Determinante(cof);
            sign = -sign;
            free_matrix(cof);
        }
    }
    Matrix result = Transpose(temp);

    return Return(m,result);
}

Matrix Transpose(Matrix m){
    Matrix t = new_matrix(m->c,m->r);
    for(int i=0;i< t->r ;i++){
        for(int j=0;j<t->c;j++){
            t->values[i][j] = m->values[j][i];
        }
    }
    return Return(m,t);

}

Matrix Inverse(Matrix m){
    float det = Determinante(m);
    Matrix adj = Adjoint(m);
    Matrix inv = multiply_by_k(1/det,adj);
    return inv;    
}

Matrix Identity(int n){
    Matrix I = new_matrix(n,n);
    for(int i=0;i<n;i++){
        I->values[i][i] = 1;
    }
    return I;
}

void State(Matrix m,...){
    int row = 0;
    int c=1;
    while(c!=0){
        c=0;
        va_list list;
        va_start(list,m);
        Matrix a = m;
        while(a!=NULL){
            c += print_row(a,row);
            printf("  ");
            a = va_arg(list,Matrix);
        }
        va_end(list);
        row++;
        printf("\n");
    }

}

int print_row(Matrix m,int row){
    int c=0;
    for(int i=0;i<m->c;i++){
        if(row < m->r){
            printf(FLOAT_FORMAT,m->values[row][i]);
            c++;
        }else{
            printf(SPACE_FORMAT); 
        }
    }
    return c;
}


//Memory management 
void free2D(float** pointer,int n){
    for(int i=0;i<n;i++){
        free(pointer[i]);
    }
    free(pointer);
}

void free_matrix(Matrix m){
    free2D(m->values,m->r);
    free(m);
}

void free_memory(Matrix m,...){
    va_list ap;
    va_start(ap,m);
    Matrix a = m;
    while(a!=NULL){
        free_matrix(a);
        a = va_arg(ap,Matrix);
    }
    va_end(ap);
}


//utility functions
void error_handler(void* pointer,char* msg){
    if(pointer==NULL){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

Matrix Return(Matrix m,Matrix temp){
    free2D(m->values,m->r);
    m->r = temp->r;
    m->c = temp->c;
    m->values = temp->values;
    free(temp);
    return m;
}