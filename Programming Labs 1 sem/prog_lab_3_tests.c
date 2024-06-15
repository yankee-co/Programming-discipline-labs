#include <stdio.h>
#include <math.h>
#include <stdlib.h>


float f(float i, float j){
        float result = 4*fabs(8.5 - i) - 1.5*pow(j, 2) + 2;
        return result;
    }

float g(float x){
    int product = 1, sum = 0, n = 6;
    for (int i = 1; i <= n-2; i++){
        for (int j = i; j <= i+2; j++){
            product *= x;
        }
        sum += product;
        product = 1;
    }
    return sum;
}

void display(float matrix[][6]){
    int n = 6;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%0.2f ", matrix[i][j]);
        }
        printf("\n");
    }        
}

void fill_matrix(float matrix[][6]){
    float elem1;
    int n = 6;
    printf("Enter elements of matrix row by row: \n");
    for (int i = 0; i < n; i++){
        printf("Row %d: ", i+1);
        for (int j = 0; j < n; j++)
        {   
            // matrix[i][j] = f(i, j);
            scanf("%f", &elem1);
            matrix[i][j] = elem1;
        }
        printf("\n");
    }
}

void sort(float matrix[][6]){
    int n = 6;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {     
            for (int k = j+1; k < n; k++) {     
                if(matrix[i][j] >= matrix[i][k]) {    
                    float temp = matrix[i][j];    
                    matrix[i][j] = matrix[i][k];    
                    matrix[i][k] = temp;    
                }     
            }     
        }
    }
}

void find_vector(float matrix[][6], float X[6]){
    int n = 6;
    for (int i = 0; i < n; i++){
        X[i] = matrix[i][n-1];
    }
}

void display_vector(float X[6]){
    printf("\nVector 'X':\n\n");
    for (int i=0; i < 6; i++){
        printf("%0.2f ", X[i]);
    }

}

int main(){

    int n = 6;
    float A[6][6], X[6], U;

    fill_matrix(A);

    printf("\nMatrix: \n\n");
    display(A);

    sort(A);

    printf("\nEdited matrix: \n\n");
    display(A);

    find_vector(A, X);

    display_vector(X);

    printf("\n\nU values:");
    for(int i = 0; i < n; i++){
        U = g(X[i]);
        printf("\nU%d = g(%0.2f) = %0.2f", i + 1, X[i], U);
    }

    return 0;
} 

// 12. Кожний рядок матриці відсортувати за неспаданням його елементів, а
// за вектор Х взяти стовпчик, який містить найбільші елементи рядків.