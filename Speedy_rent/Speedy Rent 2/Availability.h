#ifndef AVAILABILITY_H
#define AVAILABILITY_H

#include <iostream>
#include "Car.h"

class Availability {
public:
    static bool isAvailable(const Car& c);
    static void showStatus(const Car& c);
};

#endif // AVAILABILITY_H
