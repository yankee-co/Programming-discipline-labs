#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

double f(double x){
    if (x == 0) x += pow(0.01, 10);
    return log(1/(5 - 3*cos(x)) + 1/(pow(x, 2)));
    
}

double sympson(double a, double b, int N, double (*f) (double)){
    double h = (b - a) / N;
    double sum = f(a) + f(b);
    int k;

    for (int i = 1; i <= N - 1; i++){
        k = 2 + 2 * (i % 2);
        sum += k * f(a + i * h);
    }
    sum *= h / 3;
    return sum;
} 

int main(){
    double a = 0;
    double b = 2 * M_PI;

    double eps = 0.01;
    int k = 10;
    int i = 0;
    double diff;

    do
    {
        i++;
        diff = fabs(sympson(a, b, k * i, f) - sympson(a, b, k * (i * 2), f));
    } while (diff > eps);

    printf("Integral value = %f", sympson(a, b, k * (i * 2), f));

    return 1;
}

//      -3.648431486288209

Заданий масив з 10 елментів, знайти максимальний, індексами не користуємось, лише вказівниками, запвонити як завгодно