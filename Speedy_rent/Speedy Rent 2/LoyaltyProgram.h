#ifndef LOYALTYPROGRAM_H
#define LOYALTYPROGRAM_H

#include <string>
#include <fstream>
#include<iostream>
using namespace std;

class LoyaltyProgram {
public:
    static int getBookingsCount(const string& phone);
    static double applyLoyaltyDiscount(double price, const string& phone);
    static void recordBooking(const string& phone);
};

#endif // LOYALTYPROGRAM_H
