#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define ERROR_FILE_OPEN -3


void block1(){
    FILE * f;
    FILE * g;
    FILE * h;
    
    int i = 10;
    float value;
    
    f = fopen("f.bin", "wb");

    if (f == NULL){
        printf("\nFile opening failed!\n");
        exit(ERROR_FILE_OPEN);
    }

    printf("\nValues in 'f.bin':\n");

    for (float k = 1; k <= i; k++){
        value = 1 / (k * (k + 1) * (k + 2));
        printf("%f ", value);
        fwrite(&value, sizeof(float), 1, f);
    }

    fclose(f);

    g = fopen("g.bin", "wb");

    if (g == NULL){
        printf("\nFile opening failed!\n");
        exit(ERROR_FILE_OPEN);
    }

    printf("\n\nValue in 'g.bin':\n");

    value = (i - 0.1) / (pow(i, 3) + abs(tan(2*i)));
    
    fwrite(&value, sizeof(float), 1, g);
    fwrite(&value, sizeof(float), 1, g);
    fwrite(&value, sizeof(float), 1, g);

    
    fclose(g);

    f = fopen("f.bin", "rb");
    h = fopen("h.bin", "wb");

    if (h == NULL){
        printf("\nFile opening failed!\n");
        exit(ERROR_FILE_OPEN);
    }

    while(fread(&value, sizeof(float), 1, f) != 0){
        fwrite(&value, sizeof(float), 1, h);
    }

    fclose(f);
    fclose(h);

    // fwrite(&value, sizeof(float), 1, h);

    
    g = fopen("g.bin", "rb");
    h = fopen("h.bin", "ab");

    while (fread(&value, sizeof(float), 1, g) != 0)
    {
        printf("%f ", value);
        fwrite(&value, sizeof(float), 1, h);
    }
    
    fclose(g);
    fclose(h);

    printf("\n\nValues in 'h.bin': \n");

    h = fopen("h.bin", "rb");

    while(fread(&value, sizeof(float), 1, h) != 0){
        printf("%f ", value);
    }

    fclose(h);
}

void take(FILE * file, int position, int * value)
{
    fseek(file, position * sizeof(int), SEEK_SET);
    fread(value, sizeof(int), 1, file);
}

void swap(FILE * file, int position1, int * value1, int position2, int * value2)
{
    fseek(file, position1 * sizeof(int), SEEK_SET);
    fwrite(value2, sizeof(int), 1, file);

    fseek(file, position2 * sizeof(int), SEEK_SET);
    fwrite(value1, sizeof(int), 1, file);
}

void selectionSort(FILE * file, int size)
{   
    int min_idx, value1, value2;
    for (int i = 0; i < size - 1; i++){
        min_idx = i;
        
        for (int j = i + 1; j < size; j++)
        {   
            take(file, j, &value1);
            take(file, min_idx, &value2);

            if (value1 < value2)
                min_idx = j;
        }
        
        if (min_idx != i){
            take(file, i, &value1);
            swap(file, i, &value1, min_idx, &value2);
        }
    }
}

void block2(){

    FILE * numbers = fopen("numbers.bin", "w+b");

    if (numbers == NULL){
        printf("\nFile opening error.\n");
    }

    int quantity, value;
    printf("\nEnter quantity of numbers to generate: ");
    scanf("%d", &quantity);

    for (int i = 0; i < quantity; i++){
        value = rand() % 100;
        fwrite(&value, sizeof(int), 1, numbers);
    }

    int counter = 1;

    fseek(numbers, 0, SEEK_SET);

    printf("\nNumbers in 'nubmers.bin' as generated:\n");

    while (fread(&value, sizeof(int), 1, numbers) != 0)
    {
        printf("%d ", value);
        counter++;
    }  
    
    selectionSort(numbers, counter);

    fclose(numbers);

    numbers = fopen("numbers.bin", "rb");

    printf("\nNumbers in 'nubmers.bin' sorted:\n");

    while (fread(&value, sizeof(int), 1, numbers) != 0)
    {
        printf("%d ", value);
    }

    fclose(numbers);
}   

void block3(){

    #define MAX_LINE_LENGTH 1000

    FILE * f = fopen("script.txt", "r");
    char line[MAX_LINE_LENGTH]; int open_br = 0, close_br = 0, line_counter = 1; 

    if (f == NULL){
        printf("Failed to open the file!");
        exit(1);
        }

    while (fgets(line, MAX_LINE_LENGTH, f)){
        for (int i = 0; i < strlen(line); i++){

            if (line[i] == '(') open_br++;
            else if (line[i] == ')') close_br++;
            if (close_br > open_br) break;
        }
        if (open_br != close_br) printf("\nMissing/extra bracket on line %d\n", line_counter);

        line_counter++; 
        open_br = 0;
        close_br = 0;
    } 

    fclose(f);
}

void main(){
    srand(time(0));
    printf("\n=== BLOCK 1 ===\n");
    block1();
    printf("\n\n=== BLOCK 2 ===\n");
    block2();
    printf("\n\n=== BLOCK 3 ===\n");
    block3();
    printf("\n");
}