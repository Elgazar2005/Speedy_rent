#include "Payment.h"


double Payment::applyDiscount(double price) {
    if (promoCode == "SOHA40") return price * 0.6;
    return price;
}

void Payment::collect() {
    do {
        cout << "Payment Method (Cash/Visa): ";
        cin >> method;
        transform(method.begin(), method.end(), method.begin(), ::tolower);
    } while (method != "cash" && method != "visa");

    if (method == "visa") collectVisaData();

    cout << "Promo Code (or 'none'): ";
    cin >> promoCode;
    transform(promoCode.begin(), promoCode.end(), promoCode.begin(), ::toupper);
}

void Payment::printInvoiceToFile(ofstream& file) {
    file << "\n========== Payment Information ==========\n";
    file << "Payment Method : " << (method == "visa" ? "Visa" : "Cash") << "\n";
    if (method == "visa") {
        file << "Card Number     : " << maskCardNumber(cardNumber) << "\n";
        file << "Expiry Date     : " << expiryDate << "\n";
    }
    file << "Promo Code      : " << (promoCode == "NONE" ? "No Discount" : promoCode) << "\n";
    file << "=========================================\n";
}

void Payment::collectVisaData() {
    do {
        cout << "Enter Visa Card Number (16 digits, starts with 4): ";
        cin >> cardNumber;
    } while (!isValidCard(cardNumber));

    do {
        cout << "Enter Expiry Date (MM/YY): ";
        cin >> expiryDate;
    } while (!isValidExpiry(expiryDate));

    do {
        cout << "Enter CVV (3 digits): ";
        cin >> cvv;
    } while (!isValidCVV(cvv));
}

bool Payment::isValidCard(const string& card) {
    return card.length() == 16 && card[0] == '4' && all_of(card.begin(), card.end(), ::isdigit);
}

bool Payment::isValidExpiry(const string& expiry) {
    return expiry.length() == 5 && expiry[2] == '/';
}

bool Payment::isValidCVV(const string& cvvInput) {
    return cvvInput.length() == 3 && all_of(cvvInput.begin(), cvvInput.end(), ::isdigit);
}

string Payment::maskCardNumber(const string& card) {
    return "**** **** **** " + card.substr(12, 4);
}
