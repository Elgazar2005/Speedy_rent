#include "Filter.h"


vector<Car> Filter::byCategory(const vector<Car>& cars, const string& category) {
    vector<Car> filtered;
    string categoryLower = category;
    transform(categoryLower.begin(), categoryLower.end(), categoryLower.begin(), ::tolower);

    for (const auto& c : cars) {
        string carCategoryLower = c.category;
        transform(carCategoryLower.begin(), carCategoryLower.end(), carCategoryLower.begin(), ::tolower);

        if (carCategoryLower == categoryLower)
            filtered.push_back(c);
    }
    return filtered;
}

vector<Car> Filter::byTransmission(const vector<Car>& cars, const string& transmission) {
    vector<Car> filtered;
    string transLower = transmission;
    transform(transLower.begin(), transLower.end(), transLower.begin(), ::tolower);

    for (const auto& c : cars) {
        string carTransLower = c.transmission;
        transform(carTransLower.begin(), carTransLower.end(), carTransLower.begin(), ::tolower);

        if (carTransLower == transLower)
            filtered.push_back(c);
    }
    return filtered;
}
