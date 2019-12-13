#include "Headers/Show.h"
#define FLOAT_FORMAT " %6.2f"
#define SPACE_FORMAT "       "
#define BR 75

void show_matrix(Matrix m){
    for(int i=0; i < m->r; i++){
        for(int j=0; j < m->c; j++){
            printf(FLOAT_FORMAT,m->values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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
            a = va_arg(list,Matrix);
            printf("  ");
            
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

void show_system(Matrix xB,Matrix xR,Matrix B,Matrix R,Matrix cB,Matrix cR,Matrix b){
    Matrix xB_T = init_base_variables(1,B->c);
    Matrix I = Identity(B->c);
    Matrix c_zero = new_matrix(B->r,1);
    Matrix r_zero = new_matrix(1,B->c);
    Matrix z = new_matrix(1,1);
    z->values[0][0] = 1;

    
    Matrix Bi = Inverse_Gaussian(B);
    Matrix cB_Bi = Multiply( cB ,Bi);
    Matrix Bi_R = Multiply(Bi,R);
    Matrix cB_Bi_R = Multiply(cB_Bi,R);

    Matrix Bi_b = Multiply(Bi,b);
    Matrix cB_Bi_b = Multiply(cB_Bi,b);
    Matrix cR_cB_Bi_R = Substract(cR,cB_Bi_R);

    Matrix _cB_Bi_b = multiply_by_k(-1,cB_Bi_b);

    //Table
    br('-');
    header(xB_T,xR);
    br('-');
    body(xB,I,Bi_R,c_zero,Bi_b);
    br('-');
    footer(r_zero,cR_cB_Bi_R,z,_cB_Bi_b);
    br('-');

    
    free_memory(xB_T , I, c_zero, r_zero, z,Bi, cB_Bi, Bi_R,
                cB_Bi_R, Bi_b, cB_Bi_b, cR_cB_Bi_R, _cB_Bi_b,NULL);
}


void header(Matrix xB_T,Matrix xR){
    printf("Var. base |");
    for(int i=0;i<xB_T->c;i++)
        printf("     x%.0f",xB_T->values[0][i]);

    printf("   ");
    for(int i=0;i<xR->c;i++)
        printf("    x%.0f",xR->values[0][i]);

    printf("  |    -Z  |  Termes droit\n");    
}

void body(Matrix xB,Matrix I,Matrix R,Matrix Z,Matrix b){
    for(int i=0;i<xB->r;i++){
        printf("   x%.0f",xB->values[i][0]);
        printf("     |");
        print_row(I,i);
        printf("  ");
        print_row(R,i);
        printf(" |");
        print_row(Z,i);
        printf(" |");
        print_row(b,i);
        printf("\n");
    }
}


void footer(Matrix B,Matrix R,Matrix z,Matrix result){
    printf("   -Z     |");
    for(int i=0;i<B->c;i++)
        printf(FLOAT_FORMAT,B->values[0][i]);
    
    printf("  ");
    for(int i=0;i<R->c;i++)
        printf(FLOAT_FORMAT,R->values[0][i]);
    
    printf(" |");
    printf(FLOAT_FORMAT,z->values[0][0]);
    printf(" |");       
    printf(FLOAT_FORMAT,result->values[0][0]);
    printf("\n");
}

void br(char sep){
    for(int i=0;i<BR;i++)
        printf("%c",sep);
    printf("\n");
}