#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void gotoxy(int x, int y){

    COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CRD);
}

void borders()
{
	int i;
	
	/*corners*/
    gotoxy(5, 5);
    printf("%c", 201);
    gotoxy(45, 5);
	printf("%c", 187);
    gotoxy(5,11);
	printf("%c", 200);
    gotoxy(45,11);
	printf("%c", 188);
	
	/*vertical lines*/
	for(i = 6; i < 11; i++)
	{
        gotoxy(5, i);
        printf("%c", 186);

        gotoxy(45, i);
        printf("%c", 186);
	}
	
	/*horizontal lines */
	for (i = 6; i < 45; i++)
	{
        gotoxy(i, 5);
        printf("%c", 205);
        gotoxy(i, 11);
        printf("%c", 205);
	}
}

void hello(char *title){
    char * line1 = title;
    char line2[] = "Eduard Zemlyanski";
    char line3[] = "KV-22";
    
    int space(char *line){
        return (40 - strlen(line))/2 + 5;
    }

    gotoxy(space(line1),7);
    puts(line1);
    gotoxy(space(line2),8);
    puts(line2);
    gotoxy(space(line3),9);
    puts(line3);
    gotoxy(13,13);
    printf("Click 'Enter' to continue");
    gotoxy(0,0);
    getchar();
    system("cls");
}