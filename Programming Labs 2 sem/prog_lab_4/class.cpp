#include "class.h"

Car::Car(){
    cout << "Constructor called for " << this << endl;
}

Car::Car(string markValue, int powerValue, float priceValue){
    cout << "Constructor called for " << this << endl;
    SetCar(markValue, powerValue, priceValue);
}

void Car::SetCar(string markValue, int powerValue, float priceValue){
    cout << "Setter called for " << markValue << " " << this << endl;
    mark = markValue;
    power = powerValue;
    price = priceValue;
}

void Car::GetCar(){
    cout << "Getter called for " << mark << " " << this << endl;
    cout << "Mark: " << mark << "\nPower: " << power << "\nPrice: " << price << endl;
}

void Car::CopyCar(const Car & refCar){

    cout << "Copying called for " << mark << " " << this << endl;

    mark = refCar.mark;
    power = refCar.power;
    price = refCar.price;
}

Car::~Car(){
    cout << "Destructor called for " << mark << " " << this << endl;
}

