#ifndef SUPPORTER_H
#define SUPPORTER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

class Supporter {
public:
    static void showOptions();
    static void handle(int choice);

private:
    static void showRentGuide();
    static void showPaymentHelp();
    static void showContactInfo();
    static void showFAQ();
    static void collectUserQuestion();
    static void sendLiveChat();
    static void showReplies();
};

#endif // SUPPORTER_H
