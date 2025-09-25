#ifndef PENALTYMANAGER_H
#define PENALTYMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class PenaltyManager {
public:
    static void addPenalty(const string& phone, double amount, const string& reason);
    static double getPenalty(const string& phone, vector<string>& reasons);
    static void clearPenalty(const string& phone);
};

#endif // PENALTYMANAGER_H
