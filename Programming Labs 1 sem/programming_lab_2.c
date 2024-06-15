#include <stdio.h>
#include <math.h>

int main()  
{   
    float a = -5, b = 1, x, n = 7;

    float func1(float x){
        float val = pow(2, x) + pow(exp(1), x/2);
        return val;
    }

    float func2(float x){
        float val = pow(2, -x) / fabs(x);
        return val;
    }

    float func3(float x){
        float val = pow(x+9, 3/2);
        return val;
    }

    void draw_line(){
        for(int a = 0; a <= 81; a++){
            printf("-");
        }
    }

    draw_line();

    printf("\n|   X\t|\t2^x + e^(x/2)\t|\t2^(-x)/|x|\t|\t(x+9)^(3/2)\t |\n");

    for (int i = 0; i <= n; i++){
        draw_line();
        printf("\n");
        x = a+i*((b-a)/n);
        printf("| %0.2f\t|\t%0.2f\t\t|\t%0.2f\t\t|\t%0.2f\t\t |\n", x, func1(x), func2(x), func3(x));

        }

    draw_line();

    printf("\n|\t\t\t  Sklav: Zemlyanski E.V. KV-22\t\t\t\t |\n");

    draw_line();

    return 0;
}  

    