#ifndef ADMIN_H
#define ADMIN_H

#include "Car.h"
#include <vector>
#include <string>
#include "PenaltyManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

class Admin {
    string password = "admin123";
    string carsFile = "C:\\Users\\AD\\Downloads\\cars.csv";

public:
    bool login();
    void manage(vector<Car>& cars);

private:
    void appendToFile(const Car& car);
    void writeAllToFile(const vector<Car>& cars);
    void replyToUsers();
};

#endif // ADMIN_H
