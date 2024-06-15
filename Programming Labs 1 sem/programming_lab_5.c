#include "preview.h"
#include <ctype.h>



int main () {

    borders();
    hello("Lab No.5");

    char line[64];
    student students[20];

    FILE *students_txt; 
    students_txt = fopen("students.txt", "r"); // opening file
    
    if(!students_txt){
            printf("Failed to open the file\n");
            exit(1);
        }

    int student_counter = 0;

    while (fgets(line, sizeof(line), students_txt) != NULL)
    {
        sscanf(line, "%s %s %d %d %d %d %d", students[student_counter].name, students[student_counter].surname, &students[student_counter].mark1, &students[student_counter].mark2, &students[student_counter].mark3, &students[student_counter].mark4, &students[student_counter].scholarship);
        student_counter++;
    }
    
    fclose(students_txt); // closing file

    int max_scholarship = students[0].scholarship;
    student swap;

    for(int i = 0; i < student_counter; i++){
        for (int j = 0; j < student_counter; j++){
            if (students[j].scholarship < students[i].scholarship){
                swap = students[i];
                students[i] = students[j];
                students[j] = swap;
            }
        }
    }
    
    puts("\nList of students with scholarship:");
    for(int i = 0; i < student_counter; i++){
        if(students[i].scholarship > 0) printf("\nStudent: %s %s\nProgramming: %d\nDSnA: %d\nMath. analysis: %d\nLinear algebra: %d\nSholarship: %d\n", students[i].name, students[i].surname, students[i].mark1, students[i].mark2, students[i].mark3, students[i].mark4, students[i].scholarship);
    }
    
    puts("\nList of students without scholarship:");
    for(int i = 0; i < student_counter; i++){
        if(students[i].scholarship == 0) printf("\nStudent: %s %s\nProgramming: %d\nDSnA: %d\nMath. analysis: %d\nLinear algebra: %d\nSholarship: %d\n", students[i].name, students[i].surname, students[i].mark1, students[i].mark2, students[i].mark3, students[i].mark4, students[i].scholarship);
    }

    printf("\nClick 'Enter' to finish");
    getchar();

    return(0);
}