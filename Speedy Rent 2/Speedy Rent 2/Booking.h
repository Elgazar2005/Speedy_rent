#ifndef BOOKING_H
#define BOOKING_H

#include "BookingValidator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

class Booking {
public:
    string carID, customerName, phone, bookingDate, returnDate;

    bool collect(const string& cid, const string& cname, const string& cphone);
    void saveToFile();

private:
    bool isValidDate(const string& date);
    bool isReturnAfterBooking();
    tm parseDate(const string& date);
};

#endif // BOOKING_H
