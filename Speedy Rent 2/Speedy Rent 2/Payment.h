#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Payment {
public:
    string method, promoCode, cardNumber, expiryDate, cvv;

    double applyDiscount(double price);
    void collect();
    void printInvoiceToFile(ofstream& file);

private:
    void collectVisaData();
    bool isValidCard(const string& card);
    bool isValidExpiry(const string& expiry);
    bool isValidCVV(const string& cvvInput);
    string maskCardNumber(const string& card);
};

#endif // PAYMENT_H
