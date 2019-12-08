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

    m->values = (float**)malloc(rows*sizeof(float*));
    error_handler(m->values,"new_matrix");
    for(int i=0;i<rows;i++){
        m->values[i] = (float*)calloc(cols,sizeof(float));
        error_handler(m->values[i],"new_matrix");
    }
    return m;
}

void show_matrix(Matrix m){
    for(int i=0; i < m->r; i++){
        for(int j=0; j < m->c; j++){
            printf(" %f ",m->values[i][j]);
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
Matrix transpose(Matrix matrix) {
    Matrix t = new_matrix(matrix->c, matrix->r);
    for (int i = 0; i < matrix->r; i++) {
        for (int j = 0; j < matrix->c ; j++) {
            t->values[j][i] = matrix->values[i][j];
        }
    }
    return t;
}


float determinant(Matrix a,float k)
{
    float s = 1, det = 0;
    Matrix b=new_matrix(a->r,a->c+1);
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a->values[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0;i < k; i++)
            {
                for (j = 0 ;j < k; j++)
                {
                    b->values[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b->values[m][n] = a->values[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a->values[0][c] * determinant(b,k-1));
            s = -1 * s;
        }
    }
    free_matrix(b);
    return (det);
}

Matrix Adjugate(Matrix M) {
    Matrix b=new_matrix(M->r,M->c);
    Matrix fac=new_matrix(M->r,M->c);
    Matrix adj = new_matrix(M->r, M->c);
    int p, q, m, n, i, j;
    for (q = 0; q < adj->r; q++) {
        for (p = 0; p < adj->r; p++) {
            m = 0;
            n = 0;
            for (i = 0; i < adj->r; i++) {
                for (j = 0; j < adj->r; j++) {
                    if (i != q && j != p) {
                        b->values[m][n] = M->values[i][j];
                        if (n < (adj->r - 2))
                            n++;
                        else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            double t=0;
            if((p+q)%2==0){
                t=1;
            } else{
                t=-1;
            }
            fac->values[q][p] = t * determinant(b, M->r - 1);
        }
    }
    free_matrix(adj);
    free_matrix(b);
    return transpose(fac);
}


void free_matrix(Matrix matrix) {

    for (int i = 0; i < matrix->r; i++) {
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}

void Multipy_by_k(Matrix M, float k){
    for (int i = 0; i < M->r; ++i) {
        for (int j = 0; j < M->c; ++j) {
            M->values[i][j]=k*M->values[i][j];
        }
    }
}

Matrix Inverse(Matrix A){
    Matrix I=Adjugate(A);
    float k=1/determinant(A,A->r);
    Multipy_by_k(I,k);
    return I;
}