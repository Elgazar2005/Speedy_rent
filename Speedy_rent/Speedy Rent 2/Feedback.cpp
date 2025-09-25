#include "Feedback.h"


void Feedback::collect() {
    cin.ignore();
    cout << "Your Name: ";
    getline(cin, customerName);
    cout << "Leave your feedback: ";
    getline(cin, comments);
    cout << "- Thank you " << customerName << " -" << endl;
}

void Feedback::saveToFile() {
    ofstream file("Feedback.txt", ios::app);
    if (file.is_open()) {
        file << "Customer: " << customerName << "\nFeedback: " << comments << "\n---\n";
        file.close();
    }
}
