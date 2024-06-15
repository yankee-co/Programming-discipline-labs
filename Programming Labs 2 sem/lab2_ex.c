#include <stdio.h>

int main(){

    int mas[10] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 16};

    int *vk = mas;

    int i = 0;
    while (i < sizeof(mas)/sizeof(mas[0])-1)
    {
        if(*(vk) < *(vk++)) vk++;
        i++;
    }
    
    printf("Max: %d", *vk);

    return 1;
}

// Заданий масив з 10 елментів, знайти максимальний, користуючись лише вказівниковою арифметикою, заповнити як завгодно