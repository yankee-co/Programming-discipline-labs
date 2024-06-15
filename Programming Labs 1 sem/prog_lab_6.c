#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

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
    gotoxy(5,16);
	printf("%c", 200);
    gotoxy(45,16);
	printf("%c", 188);
	
	/*vertical lines*/
	for(i = 6; i < 16; i++)
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
        gotoxy(i, 16);
        printf("%c", 205);
	}
}

void choice1(){
    puts("1");
}

void choice2(){
    puts("2");
}

void choice3(){
    puts("3");
}

void menu(char *title){
    char choice;
    char * line1 = title;
    char line2[] = "Eduard Zemlyanski";
    char line3[] = "KV-22";
    char line4[] = "1.Task";
    char line5[] = "2.Letter 2D";
    char line6[] = "3.Letter 3D";
    char line7[] = "4.Exit program";
    char line8[] = "Make a choice 1/2/3/4: ";
    
    int space(char *line){
        return (40 - strlen(line))/2 + 5;
    }

    gotoxy(space(line1),7);
    puts(line1);
    gotoxy(space(line2),8);
    puts(line2);
    gotoxy(space(line3),9);
    puts(line3);

    // menu

    gotoxy(space(line4),11);
    puts(line4);
    gotoxy(space(line5),12);
    puts(line5);
    gotoxy(space(line6),13);
    puts(line6);
    gotoxy(space(line7),14);
    puts(line7);

    // end of menu

    gotoxy(space(line8), 18);
    printf("%s", line8);
    choice = getchar();
    system("cls");
    if (choice == '1') choice1();
    else if (choice == '2') choice2();
    else if (choice == '3') choice3();
    else if (choice == '4') exit(1);
    else {
        puts("Wrond choice, try again\n");
        Sleep(500);
        system("cls");
        borders();
        menu(title);
    }
}

int main(){

    borders();
    menu("Lab No.6");

    return 0;
}