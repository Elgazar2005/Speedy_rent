#ifndef BOOKINGVALIDATOR_H
#define BOOKINGVALIDATOR_H

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class BookingValidator {
public:
    static bool isDateConflict(const string& id, const string& startDate, const string& endDate);

private:
    static bool isOverlap(const string& a1, const string& a2, const string& b1, const string& b2);
    static tm parse(const string& date);
};

#endif // BOOKINGVALIDATOR_H
