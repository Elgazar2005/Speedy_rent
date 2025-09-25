#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>
#include <algorithm>
#include "Car.h"

using namespace std;

class Filter {
public:
    static vector<Car> byCategory(const vector<Car>& cars, const string& category);
    static vector<Car> byTransmission(const vector<Car>& cars, const string& transmission);
};

#endif // FILTER_H
