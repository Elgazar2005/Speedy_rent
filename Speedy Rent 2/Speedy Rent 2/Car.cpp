#include "Car.h"

Car::Car(string id, string make, string model, string type, string fuel,
    string category, double price, string status,
    string color, string transmission)
    : id(id), make(make), model(model), type(type), fuel(fuel),
    category(category), dailyPrice(price), status(status),
    color(color), transmission(transmission) {
}

Car::Car(string id, string make, string model, string type, string fuel, string category)
    : id(id), make(make), model(model), type(type), fuel(fuel), category(category), dailyPrice(0.0), status("Unknown"), color("Unknown"), transmission("Unknown") {
}

void Car::showBasicInfo() const {
    cout << "ID: " << id << " | " << make << " " << model << " | " << category << "\n";
}

void Car::showFullDetails() const {
    cout << "\n[Car Details]\n";
    cout << "ID: " << id << "\nMake: " << make << "\nModel: " << model
        << "\nType: " << type << "\nFuel: " << fuel << "\nCategory: " << category
        << "\nColor: " << color << "\nTransmission: " << transmission << "\n"
        << "Daily Price: " << dailyPrice << " EGP\n"
        << "Status: " << status << "\n";
}

bool Car::isAvailable() const {
    return status == "Available" || status == "Avaliable";
}
