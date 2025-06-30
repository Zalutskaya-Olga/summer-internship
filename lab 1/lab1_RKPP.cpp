#include <iostream>
#include <string>

class Transport {
public:
    const int ID = 1; 
    virtual void drive() = 0; 
    virtual ~Transport() {} 
};

class Dvigatel {
private:
    std::string type; 
    int power;  

public:
    Dvigatel(const std::string& type, int power) 
        : type(type), power(power) {}

    void info() const {
        std::cout << "Dvigatel type: " << type << ", Power: " << power << std::endl;
    }
};

class Car : public Transport {
public:
   // static const int ID = 2;
    std::string brand;
    double price; 
    Dvigatel dvigatel;

    Car(const std::string& brand, double price, const Dvigatel& dvigatel) 
        : brand(brand), price(price), dvigatel(dvigatel) {
        count++; 
    }

    void drive() override {
        std::cout << "Car is moving!" << std::endl; 
    }

    void info() const {
        std::cout << "Car Brand: " << brand << ", Price: " << price << std::endl;
        dvigatel.info(); 
    }

    static int count; 
    ~Car() { count--; } 

};

int Car::count = 0; 

class Truck : public Car {
private:
    int gruzopodyomnost; 

public:
   // static const int ID = 3; 

    Truck(const std::string& brand, double price, const Dvigatel& dvigatel, int gruzopodyomnost)
        : Car(brand, price, dvigatel), gruzopodyomnost(gruzopodyomnost) {
        count++; 
    } 

    void drive() override {
        std::cout << "Truck is moving!" << std::endl; 
    }    

    void info() const {
        Car::info(); 
        std::cout << "Truck gruzopodyomnost: " << gruzopodyomnost << std::endl;
    }

    ~Truck() { count--; } 
};

int main() {
    Dvigatel dvigatel("Petrol", 150);
    Dvigatel dvigatelTruck("Diesel", 250); 
    Car car("Toyota", 20000, dvigatel);   
    Truck truck("Mersedes", 50000, dvigatelTruck, 5000); 

    car.info();
    truck.info();

    std::cout << "Total Cars: " << Car::count << std::endl;
    std::cout << "Total Trucks: " << Truck::count << std::endl;

    return 0;
}