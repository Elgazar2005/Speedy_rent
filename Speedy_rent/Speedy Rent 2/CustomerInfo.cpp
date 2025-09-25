#include "CustomerInfo.h"


bool CustomerInfo::collect() {
    cin.ignore();
    cout << "Full Name: "; getline(cin, name);
    cout << "Phone Number (11 digits): "; getline(cin, phone);
    cout << "Address: "; getline(cin, address);
    cout << "Date of Birth (DD/MM/YYYY): "; getline(cin, dob);
    cout << "National ID (14 digits): "; getline(cin, nid);

    bool valid = true;
    if (phone.size() != 11 || !all_of(phone.begin(), phone.end(), ::isdigit)) {
        cout << "Invalid phone number.\n"; valid = false;
    }
    if (nid.size() != 14 || !all_of(nid.begin(), nid.end(), ::isdigit)) {
        cout << "Invalid national ID.\n"; valid = false;
    }

    stringstream ss(dob);
    string d, m, y;
    getline(ss, d, '/'); getline(ss, m, '/'); getline(ss, y);

    if (d.empty() || m.empty() || y.empty() || y.length() != 4) {
        cout << "Invalid date format.\n"; valid = false;
    }
    else {
        tm birth = {};
        birth.tm_mday = stoi(d);
        birth.tm_mon = stoi(m) - 1;
        birth.tm_year = stoi(y) - 1900;

        time_t birthTime = mktime(&birth);
        time_t now = time(0);
        double ageInSeconds = difftime(now, birthTime);
        double years = ageInSeconds / (365.25 * 24 * 60 * 60);

        if (years < 18.0) {
            cout << "Customer must be at least 18 years old.\n";
            valid = false;
        }
    }
    return valid;
}

void CustomerInfo::printToFile(ofstream& file) {
    file << "========== Customer Information ==========\n";
    file << "Full Name       : " << name << "\n";
    file << "Phone Number    : " << phone << "\n";
    file << "Address         : " << address << "\n";
    file << "Date of Birth   : " << dob << "\n";
    file << "National ID     : " << nid << "\n";
}
