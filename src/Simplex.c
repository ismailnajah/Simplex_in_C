#include "Headers/Simplex.h"
#define INFINITY 9999999

Pivot find_pivot(Linear_Program LP){
    Pivot p;
    p.col = 0;
    float min = LP.cR_cB_Bi_R->values[0][0];

    for(int i=1; i < LP.cR_cB_Bi_R->c ;i++){
        if( LP.cR_cB_Bi_R->values[0][i] < min){
            min = LP.cR_cB_Bi_R->values[0][i];
            p.col = i;
        }
    }
    if(min > 0){
        p.col = -1;
        return p;
    }
    min = INFINITY;
    for(int i=0;i<LP.R->r;i++){
        if(LP.R->values[i][p.col] != 0){
            float c = (float)(LP.b->values[i][0] / LP.R->values[i][p.col]);
            if(c<min && c > 0){
                p.row = i;
                min = c;
            }
        }
    }
    if(min < 0)
        p.row = -1;
    return p;
}

void insert_pivot_in_base(Linear_Program LP,Pivot p){
    swap( &LP.xB->values[0][p.row], &LP.xR->values[0][p.col]);
    for(int i=0;i<LP.R->r;i++){
        swap(&LP.R->values[i][p.col],&LP.B->values[i][p.row]);
    }
    swap(&LP.cB->values[0][p.row],&LP.cR->values[0][p.col]);
}

void Simplex(Matrix C,Matrix b,Matrix A){
    int m = A->r;
    
    Linear_Program LP;
    LP.cB = base_variables(C,m);
    LP.B = base_variables(A,m);
    LP.cR = off_base_variables(C,m);
    LP.R = off_base_variables(A,m);
    LP.xB = init_base_variables(LP.B->c,1);
    LP.xR = init_off_base_variables(LP.B->c,LP.R->c);
    LP.b = b;
    LP.cR_cB_Bi_R = new_matrix(LP.cR->r,LP.cR->c);
    LP.optimal_value = pivot(LP);

    int i=1;
    while(true){
        Pivot p = find_pivot(LP);
        print_table(LP,p);
        if(p.row < 0 || p.col<0) 
            break;

        printf("\nIteration : %i\n",i);
        insert_pivot_in_base(LP,p);
        LP.optimal_value = pivot(LP);
        p.col = -1;
        p.row = -1;
        i++;
    }

    free_memory(LP.cR_cB_Bi_R,LP.B,LP.R,LP.cB,LP.cR,LP.xB,LP.xR,NULL);
}

float pivot(Linear_Program LP){
    Matrix I = Identity(LP.B->r);

    Matrix Bi = Inverse_Gaussian(LP.B);
    Matrix cB_Bi = Multiply(LP.cB ,Bi);
    Matrix Bi_R = Multiply(Bi,LP.R);
    Matrix cB_Bi_R = Multiply(cB_Bi,LP.R);

    Matrix Bi_b = Multiply(Bi,LP.b);
    Matrix cB_Bi_b = Multiply(cB_Bi,LP.b);
    Matrix cR_cB_Bi_R = Substract(LP.cR,cB_Bi_R);

    Matrix _cB_Bi_b = multiply_by_k(-1,cB_Bi_b);


    copy_values(LP.B,I);
    copy_values(LP.R,Bi_R);
    copy_values(LP.cR_cB_Bi_R , cR_cB_Bi_R);
    copy_values(LP.b,Bi_b);

    float z = _cB_Bi_b->values[0][0];
    free_memory(Bi, cB_Bi,cB_Bi_R, cB_Bi_b,_cB_Bi_b,NULL);
    return z;
}


void swap(float *a,float *b){
    float temp = *a;
    *a = *b;
    *b =temp;
}