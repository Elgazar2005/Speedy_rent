#include "Availability.h"


bool Availability::isAvailable(const Car& c) {
    return c.isAvailable();
}

void Availability::showStatus(const Car& c) {
    if (isAvailable(c)) {
        cout << "The car is available for rent\n";
    }
    else {
        cout << "Sorry! The car is not available right now.\n";
    }
}
