#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_VALUES 100

int main() {
    FILE * f = fopen("f.bin", "wb");
    FILE * g = fopen("g.txt", "r");
    FILE * res = fopen("res.txt", "w");

    srand(time(NULL));

    int i;
    for (i = 0; i < NUM_VALUES; i++) {
        int value = rand() % 2;
        fwrite(&value, sizeof(int), 1, f);
        printf("%d ", value);
    }
    fclose(f);
    
    int f_value;
    char word_char;
    int count = 0;

    f = fopen("f.bin", "rb"); 
    while (fread(&f_value, sizeof(int), 1, f) == 1) {
        if (f_value == 1) {
            while (fscanf(g, "%c", &word_char) == 1 && word_char != ' ' && word_char != '\n' && word_char != '\r') {
                fprintf(res, "%c", word_char);
            }
            fprintf(res, "\n");
            count++;
        } else {
            char c;
            while (fscanf(g, "%c", &c) == 1 && c != ' ' && c != '\n' && c != '\r') {}
        }
    }

    while (fscanf(g, "%c", &word_char) == 1) {
        count++;
    }

    printf("\nNumber of words not included: %d of 69\n", count);

    fclose(g);
    fclose(res);
    
    return 0;
}