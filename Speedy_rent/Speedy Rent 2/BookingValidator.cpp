#include "BookingValidator.h"


bool BookingValidator::isDateConflict(const string& id, const string& startDate, const string& endDate) {
    ifstream file("Booking.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string b_id, name, phone, start, end;
        getline(ss, b_id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, start, ',');
        getline(ss, end, ',');

        if (b_id == id && isOverlap(startDate, endDate, start, end)) {
            return true;
        }
    }
    return false;
}

bool BookingValidator::isOverlap(const string& a1, const string& a2, const string& b1, const string& b2) {
    tm t_a1 = parse(a1), t_a2 = parse(a2);
    tm t_b1 = parse(b1), t_b2 = parse(b2);

    time_t newStart = mktime(&t_a1);
    time_t newEnd = mktime(&t_a2);
    time_t oldStart = mktime(&t_b1);
    time_t oldEnd = mktime(&t_b2);

    return (newStart <= oldEnd && newEnd >= oldStart);
}

tm BookingValidator::parse(const string& date) {
    tm t = {};
    t.tm_mday = stoi(date.substr(0, 2));
    t.tm_mon = stoi(date.substr(3, 2)) - 1;
    t.tm_year = stoi(date.substr(6, 4)) - 1900;
    return t;
}
