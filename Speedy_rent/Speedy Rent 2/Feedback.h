#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Feedback {
public:
    string customerName, comments;

    void collect();
    void saveToFile();
};

#endif // FEEDBACK_H
