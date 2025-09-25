#ifndef CAR_RECOMMENDATION_H
#define CAR_RECOMMENDATION_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "Car.h"

using namespace std;

class CarRecommendation {
public:
    vector<Car> recommendedCars;
    void loadCarRecommendation(const string& filename);
    void displayRecommended();
};

#endif // CAR_RECOMMENDATION_H
