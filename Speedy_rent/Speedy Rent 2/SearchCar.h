#ifndef SEARCHCAR_H
#define SEARCHCAR_H

#include <vector>
#include <string>
#include <algorithm>
#include "Car.h"

using namespace std;

class SearchCar {
public:
    static vector<Car> searchByMake(const vector<Car>& cars, const string& make);
};

#endif // SEARCHCAR_H
