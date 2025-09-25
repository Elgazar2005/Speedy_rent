#include "CarRecommendation.h"


void CarRecommendation::loadCarRecommendation(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open car recommendation file.\n";
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, make, model, type, fuel, category;
        getline(ss, id, ','); getline(ss, make, ','); getline(ss, model, ',');
        getline(ss, type, ','); getline(ss, fuel, ','); getline(ss, category, ',');
        recommendedCars.emplace_back(id, make, model, type, fuel, category);
    }
    file.close();
}

void CarRecommendation::displayRecommended() {
    cout << "\n---Car Recommendations---\n";
    cout << left << setw(15) << "ID" << " | " << setw(15) << "Make" << " | "
        << setw(15) << "Model" << " | " << setw(15) << "Fuel" << " | "
        << setw(15) << "Category" << "\n";
    for (int i = 0; i <= 90; i++) cout << "-";
    cout << "\n";
    for (const auto& car : recommendedCars) {
        cout << left << setw(15) << car.id << " | " << setw(15) << car.make
            << " | " << setw(15) << car.model << " | " << setw(15) << car.fuel
            << " | " << setw(15) << car.category << "\n";
    }
}
