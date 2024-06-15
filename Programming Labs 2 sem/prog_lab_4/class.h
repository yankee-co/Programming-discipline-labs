#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Car{
    private:
        string mark;
        int power;
        float price;

    public:
        Car();
        Car(string markValue, int powerValue, float priceValue);
        void SetCar(string markValue, int powerValue, float priceValue);
        void GetCar();
        void CopyCar(const Car & refCar);
        ~Car();
};

#endif
