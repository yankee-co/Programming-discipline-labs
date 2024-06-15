#include "class.h"

using namespace std;

int main(){

    Car car1, car2;

    car1.SetCar("Opel Zafira A", 190, 5400);
    car1.GetCar();

    car2.SetCar("Opel Zafira B", 130, 4200);
    car2.GetCar();

    car2.CopyCar(car1);
    car2.GetCar();

    Car * car3 = new Car;
    Car * car4 = new Car;

    car3->SetCar("BMW E5", 210, 5000);
    car3->GetCar();

    car4->SetCar("Audi R8", 220, 7090);
    car4->GetCar();

    delete car3;
    delete car4;

    Car &car5 = * (new Car);
    Car &car6 = * (new Car);

    car5.SetCar("Tavria Nova", 90, 900);
    car5.GetCar();

    car6.SetCar("Deviatka", 110, 1200);
    car6.GetCar();

    car6.CopyCar(car5);
    car6.GetCar();

    const int quantity = 2;
    Car Cars[quantity];

    Car car7;
    Cars[0] = car7;

    Cars[1].SetCar("Renault Master", 160, 2300);
    Cars[1].GetCar();

    Car * Cars2;
    Cars2 = new Car[2];
    
    Cars2[0] = Car("Nissan Note", 120, 1500);
    Cars2[0].GetCar();

    Cars2[1] = Car("Nissan Leaf", 100, 3500);
    Cars2[1].GetCar();

    Cars2[1].CopyCar(Cars2[0]);
    Cars2[1].GetCar();

    void (Car::*methodPtr)(const Car & refCar) = &Car::CopyCar;
    (Cars2[1].*methodPtr)(car1);
    Cars2[1].GetCar();

    delete[] Cars2;

    return 0;
}