#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define E 2.718281828459045

float calculate(float x, float y, float z){

    void invalid(){
        printf("Input data is out of the valid values range\n"); 
    }

    if (sin(y)>0){
        if((0.5-exp(2*log(sin(y))))!=0){
            float a = (2*(cos(x-PI/6))) / (0.5-exp(2*log(sin(y))));
            printf("Value of a: %f", a);
        }
    }
    else{
        printf("\nA: ");
        invalid();
    }

    if (tan(z) > 0){
        if (exp(2*log(tan(z)))-1>0){
            float b = exp(abs(x-y)*log(E)) * exp(x*log(exp(2*log(tan(z)))-1));
            printf("\nValue of b: %f", b);
        }
    }
    else{
        printf("\nB: ");
        invalid();
    }

    return 0;
};

int main(){
    float a, b, c;
    
    printf("Enter value of 'x': ");
    scanf("%f", &a);
    printf("Enter value of 'y': ");
    scanf("%f", &b);
    printf("Enter value of 'z': ");
    scanf("%f", &c);

    calculate(a, b, c);
    return 0;
};
