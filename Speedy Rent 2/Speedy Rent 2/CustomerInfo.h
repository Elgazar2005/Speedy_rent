#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

class CustomerInfo {
public:
    string name, phone, address, dob, nid;

    bool collect();
    void printToFile(ofstream& file);
};

#endif // CUSTOMERINFO_H
