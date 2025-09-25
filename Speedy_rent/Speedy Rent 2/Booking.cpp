#include "Booking.h"


bool Booking::collect(const string& cid, const string& cname, const string& cphone) {
    carID = cid;
    customerName = cname;
    phone = cphone;

    bool validBooking = false;
    while (!validBooking) {
        cout << "Enter Booking Date (DD/MM/YYYY): ";
        cin >> bookingDate;
        while (!isValidDate(bookingDate)) {
            cout << "Invalid or past booking date. Please try again: ";
            cin >> bookingDate;
        }

        cout << "Enter Return Date (DD/MM/YYYY): ";
        cin >> returnDate;
        while (!isValidDate(returnDate) || !isReturnAfterBooking()) {
            cout << "Return date must be after booking date. Please try again: ";
            cin >> returnDate;
        }

        if (BookingValidator::isDateConflict(carID, bookingDate, returnDate)) {
            char retry;
            cout << "\nThis car is already booked during the selected period.\n";
            cout << "Would you like to enter different dates? (y/n): ";
            cin >> retry;
            if (tolower(retry) != 'y') {
                cout << "Booking cancelled.\n";
                return false;
            }
        }
        else {
            validBooking = true;
        }
    }
    return true;
}

void Booking::saveToFile() {
    ofstream file("Booking.csv", ios::app);
    if (file.is_open()) {
        file << carID << "," << customerName << "," << phone << "," << bookingDate << "," << returnDate << "\n";
        file.close();
    }
}

bool Booking::isValidDate(const string& date) {
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') return false;
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    tm input = {};
    input.tm_mday = day;
    input.tm_mon = month - 1;
    input.tm_year = year - 1900;

    time_t inputTime = mktime(&input);
    time_t now = time(0);
    return difftime(inputTime, now) >= 0;
}

bool Booking::isReturnAfterBooking() {
    tm d1 = parseDate(bookingDate), d2 = parseDate(returnDate);
    time_t t1 = mktime(&d1), t2 = mktime(&d2);
    return difftime(t2, t1) >= 0;
}

tm Booking::parseDate(const string& date) {
    tm t = {};
    t.tm_mday = stoi(date.substr(0, 2));
    t.tm_mon = stoi(date.substr(3, 2)) - 1;
    t.tm_year = stoi(date.substr(6, 4)) - 1900;
    return t;
}
