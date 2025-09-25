#ifndef RENTALUI_H
#define RENTALUI_H

#include "Car.h"
#include "CarRecommendation.h"
#include <vector>
#include <string>
#include "SearchCar.h"
#include "Filter.h"
#include "Availability.h"
#include "CustomerInfo.h"
#include "Payment.h"
#include "Booking.h"
#include "Supporter.h"
#include "Admin.h"
#include "PenaltyManager.h"
#include "LoyaltyProgram.h"
#include "Feedback.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

#include <algorithm>
#include <windows.h>

using namespace std;

class RentalUI {
private:
    vector<Car> cars;
    CarRecommendation recommender;

public:
    void loadCars(const string& file);
    void mainMenu();
    void startRentalProcess();
    int calculateDays(const string& from, const string& to);
    tm parseDate(const string& date);
    void run();
};

#endif // RENTALUI_H
