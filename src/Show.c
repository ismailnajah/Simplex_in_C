#include "Headers/Show.h"
#include "Headers/Simplex.h"
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

void print_table(Linear_Program LP){
    Matrix xB_T = Transpose(LP.xB);
    Matrix c_zero = new_matrix(LP.B->r,1);
    Matrix r_zero = new_matrix(1,LP.B->c);
    Matrix z = new_matrix(1,1);
    z->values[0][0] = 1;


    //Table
    br('-');
    header(LP.xB,LP.xR);
    br('-');
    body(xB_T,LP.B,LP.R,c_zero,LP.b);
    br('-');
    footer(r_zero,LP.cR_cB_Bi_R,z,LP.optimal_value);
    br('-');
    
    free_memory(xB_T , c_zero, r_zero, z,NULL);
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


void footer(Matrix B,Matrix R,Matrix z,float result){
    printf("   -Z     |");
    for(int i=0;i<B->c;i++)
        printf(FLOAT_FORMAT,B->values[0][i]);
    
    printf("  ");
    for(int i=0;i<R->c;i++)
        printf(FLOAT_FORMAT,R->values[0][i]);
    
    printf(" |");
    printf(FLOAT_FORMAT,z->values[0][0]);
    printf(" |");       
    printf(FLOAT_FORMAT,result);
    printf("\n");
}

void br(char sep){
    for(int i=0;i<BR;i++)
        printf("%c",sep);
    printf("\n");
}