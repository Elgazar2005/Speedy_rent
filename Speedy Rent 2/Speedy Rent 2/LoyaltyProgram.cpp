#include "LoyaltyProgram.h"


int LoyaltyProgram::getBookingsCount(const string& phone) {
    ifstream file("RentalHistory.csv");
    string line;
    int count = 0;

    while (getline(file, line)) {
        if (line == phone) {
            count++;
        }
    }
    return count;
}

double LoyaltyProgram::applyLoyaltyDiscount(double price, const string& phone) {
    int count = getBookingsCount(phone);
    if (count >= 3) {
        cout << "\nSurprise! Because you've booked more than 3 times with us\n"
            << "you've automatically received a 15% loyalty discount.\n"
            << "Thank you for being a valued customer!\n";
        return price * 0.85;
    }
    return price;
}

void LoyaltyProgram::recordBooking(const string& phone) {
    ofstream file("RentalHistory.csv", ios::app);
    if (file.is_open()) {
        file << phone << "\n";
        file.close();
    }
}
