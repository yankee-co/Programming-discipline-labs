#include "preview.h"

void print_date(int day, int month, int year){
    printf("Previous date: %d.%d.%d", day, month, year);
    getchar();
    exit(1);
}

void wrong_date(){
    printf("Wrong date!");
    getchar();
    exit(1);
}

void check_date(int day, int month, int year){
    if (day >= 1 && day <= 31 && year >= 1 && month >= 1 && month <= 12){
        
        day--;
        
        if(month >= 4 && month <= 8){

            if (month % 2 == 0){
                if (day == 0){ day = 31; month--; }
                else if (day > 31) wrong_date();
            }

            else{
                if (day == 0){ day = 30; month--; }
                else if (day > 32) wrong_date();
            }

            print_date(day, month, year); 
        }

        else if (month >= 9 && month <= 12){

            if (month % 2 == 0){
                if (day == 0){ day = 30; month--; }
                else if (day > 32) wrong_date();
            }

            else{
                if (day == 0){ day = 31; month--; }
                else if (day > 31) wrong_date();
            }

            print_date(day, month, year); 
        }
        else{
 
            switch (month){
                case 1:
                    if (day == 0){
                        day = 31;
                        month = 12;
                        year--;
                        if (year == 0){
                            puts("No previous date!");
                            getchar();
                            exit(1);
                        }
                    }
                    else if (day > 31) wrong_date();
                    break;

                case 2:
                    if (day == 0) {day = 31; month--;}
                    else if (year % 4 == 0 && day > 29) wrong_date();
                    else if (day > 28) wrong_date();
                    break;

                case 3:
                    if (day == 0 && year % 4 == 0) {day = 29; month--;}
                    else if (day == 0) day = 28;
                    else if (day > 31) wrong_date();
                    break;

                default:
                    wrong_date();
            }

        }

        print_date(day, month, year);
    }
    else{
        printf("Wrong date");
    } 
}

int main(){

    int day, month, year;

    borders();
    hello("DKR No.1");
    
    printf("Enter date: ");
    scanf("%d.%d.%d", &day, &month, &year);

    check_date(day, month, year);

    return 0;
}