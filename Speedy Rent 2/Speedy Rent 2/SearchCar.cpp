#include "SearchCar.h"


vector<Car> SearchCar::searchByMake(const vector<Car>& cars, const string& make) {
    vector<Car> filtered;
    string makeLower = make;
    transform(makeLower.begin(), makeLower.end(), makeLower.begin(), ::tolower);

    for (const auto& c : cars) {
        string carMakeLower = c.make;
        transform(carMakeLower.begin(), carMakeLower.end(), carMakeLower.begin(), ::tolower);

        if (carMakeLower == makeLower)
            filtered.push_back(c);
    }
    return filtered;
}
