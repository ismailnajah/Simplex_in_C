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

Matrix init_base_variables(int m,int n){
    Matrix X = new_matrix(m,n);
    for(int i=0;i< m;i++){
        for(int j=0;j<n;j++){
            X->values[i][j] = 1+i+j;
        }
    }
    return X;
}

Matrix init_off_base_variables(int m,int n){
    Matrix X = new_matrix(1,n);
    for(int i=0;i< n;i++){
        X->values[0][i] = 1+m+i;
    }
    return X;
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
    return result;
}

Matrix multiply_by_k(float value,Matrix m){
    Matrix result = new_matrix(m->r,m->c);
    for(int i=0;i<m->r;i++){
        for(int j=0;j<m->c;j++){
            result->values[i][j] = m->values[i][j] * value;
        }
    }
    return result;
}

Matrix Add(Matrix m1,Matrix m2){
    Matrix result = new_matrix(m1->r,m2->c);
    for(int i=0;i<m1->r;i++){
        for(int j=0;j<m1->c;j++){
            result->values[i][j] = m1->values[i][j] + m2->values[i][j];
        }
    }
    return result;
}

Matrix Substract(Matrix m1,Matrix m2){
    Matrix result = new_matrix(m1->r,m2->c);
    for(int i=0;i<m1->r;i++){
        for(int j=0;j<m1->c;j++){
            result->values[i][j] = m1->values[i][j] - m2->values[i][j];
        }
    }
    return result;
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
    free_matrix(temp);
    return result;
}

Matrix Transpose(Matrix m){
    Matrix t = new_matrix(m->c,m->r);
    for(int i=0;i< t->r ;i++){
        for(int j=0;j<t->c;j++){
            t->values[i][j] = m->values[j][i];
        }
    }
    return t;

}

Matrix Inverse(Matrix m){
    float det = Determinante(m);
    Matrix adj = Adjoint(m);
    Matrix inv = multiply_by_k(1/det,adj);
    free_matrix(adj);
    return inv;    
}

Matrix Inverse_Gaussian(Matrix m){
    Matrix I = Identity(m->r);
    Matrix A = Augment(m,I);
    int n = m->r;
    int p = m->c;
    int i0 = 0;

    for(int j=0; j<p; j++){
        int k = i0;
        while( k < n && A->values[k][j] == 0)
            k++;

        if( k < n){
            float d = (float)(1.0f / A->values[i0][j]);
            Permutation(A,i0,k);

            Dilation(A,i0, d);

            for(int i=0; i < n;i++){
                if(i!=i0){
                    Transvection(A,i,i0,-A->values[i][j]);
                }
            }
            i0++;
        }
    }
    Matrix result = off_base_variables(A,m->c);
    free_matrix(A);
    free_matrix(I);
    return result;
}

void Permutation(Matrix m,int i,int j){
    float* temp = m->values[i];
    m->values[i] = m->values[j];
    m->values[j] = temp;
}

void Dilation(Matrix m,int line,float a){
    for(int i=0;i<m->c;i++){
        m->values[line][i] *= a;
    }
}

void Transvection(Matrix m,int i,int j,float a){
    for(int k=0;k<m->c;k++){
        m->values[i][k] += a * m->values[j][k]; 
    }
}

Matrix Augment(Matrix m,Matrix I){
    Matrix A = new_matrix(m->r,m->c+I->c);
    for(int i=0;i<A->r;i++){
        for(int j=0;j<A->c;j++){
            A->values[i][j] = j < m->c ? m->values[i][j] : I->values[i][j-m->c];
        }
    }
    return A;
}

Matrix Identity(int n){
    Matrix I = new_matrix(n,n);
    for(int i=0;i<n;i++){
        I->values[i][i] = 1;
    }
    return I;
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

Matrix copy(Matrix m){
    Matrix c = new_matrix(m->r,m->c);
    for(int i=0;i<c->r;i++){
        for(int j=0;j<c->c;j++){
            c->values[i][j] = m->values[i][j];
        }
    }
    return c;
}