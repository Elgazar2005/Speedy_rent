#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>

using namespace std;

class Car {
public:
    string id, make, model, type, fuel, category, color, transmission, status;
    double dailyPrice;

    Car(string id, string make, string model, string type, string fuel,
        string category, double price, string status,
        string color, string transmission);

    Car(string id, string make, string model, string type, string fuel, string category);

    void showBasicInfo() const;
    void showFullDetails() const;
    bool isAvailable() const;
};

#endif // CAR_H
