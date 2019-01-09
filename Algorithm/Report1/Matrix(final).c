#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 8

int** mat_assign();
void mat_maker(int** mat);
void mat_printer(int** mat);
void standard(int** mat1, int** mat2, int** mul);
void recursion(int row1, int col1, int** mat1, int row2, int col2, int** mat2, int** mul);
int** mul_sub(int** mat1, int** mat2, int size);
void strassen(int** mat1, int** mat2, int** mul);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int** mat1 = (int**)malloc(sizeof(int*)*LEN);
    for(int i=0; i<LEN; i++){
        mat1[i] = (int*)malloc(sizeof(int)*LEN);
    }
    int** mat2 = (int**)malloc(sizeof(int*)*LEN);
    for(int i=0; i<LEN; i++){
        mat2[i] = (int*)malloc(sizeof(int)*LEN);
    }
    int** mul = (int**)malloc(sizeof(int*)*LEN);
    for(int i=0; i<LEN; i++){
        mul[i] = (int*)malloc(sizeof(int)*LEN);
    }

    
    mat_maker(mat1); mat_maker(mat2);
    printf("matrix A\n"); mat_printer(mat1); printf("\n");
    printf("matrix B\n"); mat_printer(mat2); printf("\n");

    printf("\nResult of Multiplication by standard method\n");
    for(int i=0; i<LEN; i++){
        for(int j=0; j<LEN; j++){
            mul[i][j] = 0;
        }
    }
    standard(mat1, mat2, mul);
    mat_printer(mul);
    printf("\nResult of Multiplication by recursion\n");
    for(int i=0; i<LEN; i++){
        for(int j=0; j<LEN; j++){
            mul[i][j] = 0;
        }
    }
    recursion(0, 0, mat1, 0, 0, mat2, mul);
    mat_printer(mul);
    printf("\nResult of Multiplication by Strassen method\n");
    for(int i=0; i<LEN; i++){
        for(int j=0; j<LEN; j++){
            mul[i][j] = 0;
        }
    }
    strassen(mat1, mat2, mul);
    mat_printer(mul);
    return 0;
}


void mat_maker(int** mat){
    for(int i=0; i<LEN; i++){
        for(int j=0; j<LEN; j++){
            mat[i][j] = rand()%1000;
        }
    }
}

void mat_printer(int** mat){
    for(int i=0; i<LEN; i++){
        for(int j=0; j<LEN; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void standard(int** mat1, int** mat2, int** mul){
    for(int i=0; i<LEN; i++){
        for(int j=0; j<LEN; j++){
            for(int k=0; k<LEN; k++){
                mul[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
void recursion(int row1, int col1, int** mat1, int row2, int col2, int** mat2, int** mul){
    if(row1==LEN-1 && col1==LEN-1 && row2==LEN-1 && col2==LEN-1){
        mul[row1][col2] += mat1[row1][col1] * mat2[row2][col2];
        return;
    }
    else if(row2==LEN-1 && col2==LEN-1){
        mul[row1][col2] += mat1[row1][col1] * mat2[row2][col2];
        recursion(row1+1, 0, mat1, 0, 0, mat2, mul);
    }
    else if(row2==LEN-1){
        mul[row1][col2] += mat1[row1][col1] * mat2[row2][col2];
        recursion(row1, 0, mat1, 0, col2+1, mat2, mul);
    }
    else{
        mul[row1][col2] += mat1[row1][col1] * mat2[row2][col2]; 
        recursion(row1, col1+1, mat1, row2+1, col2, mat2, mul);
    }
    
}

int** mul_sub(int** mat1, int** mat2, int size){
    int** mul = (int**)malloc(sizeof(int*)*size);
    for(int i=0; i<size; i++){
        mul[i] = (int*)malloc(sizeof(int)*size);
    }
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            mul[i][j] = 0;
            for(int k=0; k<size; k++){
                mul[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return mul;
}

void strassen(int** mat1, int** mat2, int** mul){
    int P = LEN/2;
    int **M1;
    int **M2;
    int **M3;
    int **M4;
    int **M5;
    int **M6;
    int **M7;
    int** temp1 = (int**)malloc(sizeof(int*)*P);
    for(int i=0; i<P; i++){
        temp1[i] = (int*)malloc(sizeof(int)*P);
    }
    int** temp2 = (int**)malloc(sizeof(int*)*P);
    for(int i=0; i<P; i++){
        temp2[i] = (int*)malloc(sizeof(int)*P);
    }
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            temp1[i][j] = mat1[i][j] + mat1[P+i][P+j];
            temp2[i][j] = mat2[i][j] + mat2[P+i][P+j];
        }
    }
    M1 = mul_sub(temp1, temp2, P);
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            temp1[i][j] = mat1[P+i][j] + mat1[P+i][P+j];
            temp2[i][j] = mat2[i][j];
        }
    }
    M2 = mul_sub(temp1, temp2, P);
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            temp1[i][j] = mat1[i][j];
            temp2[i][j] = mat2[i][P+j] - mat2[P+i][P+j];
        }
    }
    M3 = mul_sub(temp1, temp2, P);
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            temp1[i][j] = mat1[P+i][P+j];
            temp2[i][j] = mat2[P+i][j] - mat2[i][j];
        }
    }
    M4 = mul_sub(temp1, temp2, P);
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            temp1[i][j] = mat1[i][j] + mat1[i][P+j];
            temp2[i][j] = mat2[P+i][P+j];
        }
    }
    M5 = mul_sub(temp1, temp2, P);
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            temp1[i][j] = mat1[P+i][j] - mat1[i][j];
            temp2[i][j] = mat2[i][j] + mat2[i][P+j];
        }
    }
    M6 = mul_sub(temp1, temp2, P);
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            temp1[i][j] = mat1[i][P+j] - mat1[P+i][P+j];
            temp2[i][j] = mat2[P+i][j] + mat2[P+i][P+j];
        }
    }
    M7 = mul_sub(temp1, temp2, P);
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            mul[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            mul[i][P+j] = M3[i][j] + M5[i][j];
            mul[P+i][j] = M2[i][j] + M4[i][j];
            mul[P+i][P+j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }


}

