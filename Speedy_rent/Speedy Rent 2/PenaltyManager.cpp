#include "PenaltyManager.h"


void PenaltyManager::addPenalty(const string& phone, double amount, const string& reason) {
    ofstream file("Penalties.csv", ios::app);
    if (file.is_open()) {
        file << phone << "," << amount << "," << reason << "\n";
        file.close();
        cout << "Penalty added successfully.\n";
    }
}

double PenaltyManager::getPenalty(const string& phone, vector<string>& reasons) {
    ifstream file("Penalties.csv");
    string line;
    double total = 0.0;
    while (getline(file, line)) {
        stringstream ss(line);
        string phn, amtStr, reason;
        getline(ss, phn, ',');
        getline(ss, amtStr, ',');
        getline(ss, reason);
        if (phn == phone) {
            total += stod(amtStr);
            reasons.push_back(reason);
        }
    }
    return total;
}

void PenaltyManager::clearPenalty(const string& phone) {
    ifstream file("Penalties.csv");
    vector<string> rows;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string phn, amt, reason;
        getline(ss, phn, ',');
        getline(ss, amt, ',');
        getline(ss, reason);

        if (phn != phone) {
            rows.push_back(phn + "," + amt + "," + reason);
        }
    }
    file.close();

    ofstream out("Penalties.csv");
    for (const string& r : rows) {
        out << r << "\n";
    }
    out.close();
}
