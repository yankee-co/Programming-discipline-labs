#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void fill_matrix(int rows, int columns, int matrix[rows][columns]){
    for (int i = 0; i <  rows; i++){
        for (int j = 0; j <  columns; j++){
            matrix[i][j] = rand()%10;
        }
    }
}

void display_matrix(int rows, int columns, int matrix[rows][columns]){
    for (int i = 0; i < rows; i++){
        printf("\n");
        for (int j = 0; j < columns; j++){
            printf("%d ", matrix[i][j]);
        }
    }
}


int calculate(int rows, int columns, int matrix[rows][columns]){
    int sum = 0;
    for (int i = 0; i <  rows; i++){
        for (int j = 0; j <  columns; j++){
            sum += matrix[i][j];
        }
    }
    return sum;
}

int main(){

    srand(time(0));
    
    int A[7][4], B[6][5], C[6][8];
    
    // ���������� ������ �
    
    fill_matrix(7, 4, A);
    
    // ��������� ������ �

    printf("\nMatrix A:");
    display_matrix(7, 4, A);

    // ���������� ������ B
    
    fill_matrix(6, 5, B);

    // ��������� ������ B

    printf("\n\nMatrix B:");
    display_matrix(6, 5, B);

    // ���������� ������ C

    fill_matrix(6, 8, C);

    // ��������� ������ C

    printf("\n\nMatrix C: ");
    display_matrix(6, 8, C);

    printf("\n");

    //���� �������� �

    int sum_A = calculate(7, 4, A);
    printf("\nSum of A elements: %d", sum_A);

    //���� �������� B

    int sum_B = calculate(6, 5, B);
    printf("\nSum of B elements: %d", sum_B);

    //���� �������� C

    int sum_C = calculate(6, 8, C);
    printf("\nSum of C elements: %d", sum_C);

    return 0;
}

// 12. ���� ��� ������� ����� ����� A[7,4], B[6,5], C[6,8]. ��������� ����
// �������� ������ � ������� ����� ������� �������.