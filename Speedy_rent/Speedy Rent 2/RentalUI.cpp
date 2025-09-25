#include "RentalUI.h"
#include <chrono>

using namespace std;

void RentalUI::loadCars(const string& file) {
    ifstream f(file);
    string line;
    getline(f, line); // Skip header
    while (getline(f, line)) {
        stringstream ss(line);
        string id, make, model, type, fuel, category, priceStr, status, color, transmission;
        getline(ss, id, ','); getline(ss, make, ','); getline(ss, model, ',');
        getline(ss, type, ','); getline(ss, fuel, ','); getline(ss, category, ',');
        getline(ss, priceStr, ','); getline(ss, status, ','); getline(ss, color, ','); getline(ss, transmission, ',');

        double price = 0.0;
        try { price = stod(priceStr); }
        catch (...) {}
        cars.emplace_back(id, make, model, type, fuel, category, price, status, color, transmission);
    }
}

void RentalUI::mainMenu() {
    int choice;
    cout << "\n-------Main Menu-------\n";
    cout << "1. Contact Support\n";
    cout << "2. See Recommended Cars\n";
    cout << "3. Rent a Car\n";
    cout << "4. Admin Login\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        Supporter::showOptions();
        int opt;
        cout << "Choose option: ";
        cin >> opt;
        Supporter::handle(opt);
        break;
    case 2:
        recommender.displayRecommended();
        break;
    case 3:
        startRentalProcess();
        break;
    case 4: {
        Admin admin;
        if (admin.login()) {
            admin.manage(cars);
        }
        else {
            cout << "Access denied.\n";
        }
        break;
    }
    default:
        cout << "Invalid choice.\n";
    }
}

void RentalUI::startRentalProcess() {
    string make;
    cout << "\nEnter Car Make to Search: ";
    cin >> make;
    transform(make.begin(), make.end(), make.begin(), ::tolower);

    vector<Car> found = SearchCar::searchByMake(cars, make);

    if (found.empty()) {
        cout << "No cars found for this make.\n";
        return;
    }

    char filter;
    cout << "Apply filter? (y/n): ";
    cin >> filter;
    if (tolower(filter) == 'y') {
        int opt;
        cout << "1. Filter by Category\n2. Filter by Transmission\nChoose: ";
        cin >> opt;
        if (opt == 1) {
            string cat;
            cout << "Enter category (Economy, Standard, Premium, Luxury): ";
            cin >> cat;
            transform(cat.begin(), cat.end(), cat.begin(), ::tolower);
            found = Filter::byCategory(found, cat);
        }
        else if (opt == 2) {
            string tr;
            cout << "Enter transmission (Automatic, Manual): ";
            cin >> tr;
            transform(tr.begin(), tr.end(), tr.begin(), ::tolower);
            found = Filter::byTransmission(found, tr);
        }
    }

    if (found.empty()) {
        cout << "No cars match the applied filters.\n";
        return;
    }

    for (const auto& c : found) c.showBasicInfo();

    string id;
    cout << "\nEnter Car ID to rent: ";
    cin >> id;

    auto it = find_if(found.begin(), found.end(), [&id](const Car& c) { return c.id == id; });

    if (it == found.end()) {
        cout << "Car not found.\n";
        return;
    }

    it->showFullDetails();
    Availability::showStatus(*it);
    if (!Availability::isAvailable(*it)) return;

    char confirm;
    cout << "Do you want to rent this car? (y/n): ";
    cin >> confirm;
    if (tolower(confirm) != 'y') return;

    CustomerInfo customer;
    while (!customer.collect()) {
        cout << "\nPlease re-enter your information correctly.\n";
    }

    vector<string> penaltyReasons;
    double penalty = PenaltyManager::getPenalty(customer.phone, penaltyReasons);

    if (penalty > 0) {
        cout << "\n--- Outstanding Penalty Notice ---\n";
        cout << "Penalty Amount: " << penalty << " EGP\n";
        cout << "Penalty Reasons:\n";
        for (const string& reason : penaltyReasons) {
            cout << " - " << reason << "\n";
        }

        char payNow;
        cout << "\nYou must pay the penalty before proceeding with the booking.\n";
        cout << "Would you like to pay now? (y/n): ";
        cin >> payNow;

        if (tolower(payNow) == 'y') {
            cout << "\nProcessing your payment...\n";
            this_thread::sleep_for(chrono::seconds(5));
            PenaltyManager::clearPenalty(customer.phone);
            cout << "Payment received. Your penalty has been cleared successfully.\n";
            cout << "Proceeding with your booking...\n";
        }
        else {
            cout << "\nBooking has been cancelled due to unpaid penalty.\n";
            return;
        }
    }

    Booking booking;
    if (!booking.collect(it->id, customer.name, customer.phone)) return;

    int days = calculateDays(booking.bookingDate, booking.returnDate);
    if (days <= 0) {
        cout << "Invalid booking dates.\n";
        return;
    }

    Payment payment;
    payment.collect();
    double total = it->dailyPrice * days;
    double afterPromo = payment.applyDiscount(total);
    double finalPrice = LoyaltyProgram::applyLoyaltyDiscount(afterPromo, customer.phone);

    ofstream paymentFile("PaymentsHistory.txt", ios::app);
    if (paymentFile.is_open()) {
        customer.printToFile(paymentFile);
        payment.printInvoiceToFile(paymentFile);
        paymentFile << "Days Rented    : " << days << "\n";
        paymentFile << "Total Price    : " << finalPrice << " EGP\n";
        paymentFile << "-----------------------------------------\n\n";
        paymentFile.close();
    }

    ofstream outFile("CustomerPaymentInfo.txt", ios::app);
    if (outFile.is_open()) {
        customer.printToFile(outFile);
        payment.printInvoiceToFile(outFile);
        outFile << "Days Rented    : " << days << "\n";
        outFile << "Total Price    : " << finalPrice << " EGP\n\n";
        outFile.close();
    }

    booking.saveToFile();
    LoyaltyProgram::recordBooking(customer.phone);

    cout << "\n============================================\n";
    cout << "           Booking Confirmation\n";
    cout << "============================================\n";
    cout << "Customer Name : " << customer.name << "\n";
    cout << "Phone Number  : " << customer.phone << "\n";
    cout << "Car ID        : " << it->id << "\n";
    cout << "Days Rented   : " << days << "\n";
    cout << "Total Amount  : " << finalPrice << " EGP\n";
    cout << "--------------------------------------------\n";
    cout << "✅ Thank you for choosing our service!\n";
    cout << "✅ Your car is now reserved successfully.\n";
    cout << "✅ We wish you a safe and pleasant journey.\n";
    cout << "============================================\n\n";

    Feedback feedback;
    cout << "\nWould you like to leave feedback? (y/n): ";
    char fbChoice;
    cin >> fbChoice;
    if (tolower(fbChoice) == 'y') {
        feedback.collect();
        feedback.saveToFile();
    }
}

int RentalUI::calculateDays(const string& from, const string& to) {
    tm d1 = parseDate(from), d2 = parseDate(to);
    time_t t1 = mktime(&d1), t2 = mktime(&d2);
    return max(1, int(difftime(t2, t1) / (60 * 60 * 24)));
}

tm RentalUI::parseDate(const string& date) {
    tm t = {};
    t.tm_mday = stoi(date.substr(0, 2));
    t.tm_mon = stoi(date.substr(3, 2)) - 1;
    t.tm_year = stoi(date.substr(6, 4)) - 1900;
    return t;
}

void RentalUI::run() {
    SetConsoleOutputCP(CP_UTF8);
    recommender.loadCarRecommendation("C:\\Users\\AD\\Downloads\\Car Recomindation.csv");
    while (true) {
        mainMenu();
        char again;
        cout << "\nDo you want to go back to main menu? (y/n): ";
        cin >> again;
        if (tolower(again) != 'y') break;
    }
}
