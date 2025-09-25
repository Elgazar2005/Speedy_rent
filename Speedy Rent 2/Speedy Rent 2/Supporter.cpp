#include "Supporter.h"


void Supporter::showOptions() {
    cout << "\n[Support Options]\n";
    cout << "1. How to rent a car?\n";
    cout << "2. Payment issues\n";
    cout << "3. Contact support\n";
    cout << "4. Frequently Asked Questions (FAQ)\n";
    cout << "5. Submit a new question\n";
    cout << "6. Live Chat (Send Message)\n";
    cout << "7. View Replies\n";
}

void Supporter::handle(int choice) {
    switch (choice) {
    case 1:
        showRentGuide();
        break;
    case 2:
        showPaymentHelp();
        break;
    case 3:
        showContactInfo();
        break;
    case 4:
        showFAQ();
        break;
    case 5:
        collectUserQuestion();
        break;
    case 6:
        sendLiveChat();
        break;
    case 7:
        showReplies();
        break;
    default:
        cout << "Invalid option. Please try again.\n";
    }
}

void Supporter::showRentGuide() {
    cout << "\n[How to Rent a Car]\n";
    cout << "1. Search for available cars by make.\n";
    cout << "2. Apply filters (category, transmission) if needed.\n";
    cout << "3. Choose a car and confirm its availability.\n";
    cout << "4. Enter your personal and booking information.\n";
    cout << "5. Complete payment and confirm rental.\n";
}

void Supporter::showPaymentHelp() {
    cout << "\n[Payment Help]\n";
    cout << "- Ensure your Visa card has sufficient balance.\n";
    cout << "- Visa must start with 4 and be 16 digits.\n";
    cout << "- Expiry date format must be MM/YY.\n";
    cout << "- CVV must be 3 digits.\n";
    cout << "- Or simply choose 'Cash' as payment method.\n";
}

void Supporter::showContactInfo() {
    cout << "\n[Contact Support]\n";
    cout << "Email: support@rentalcars.com\n";
    cout << "WhatsApp: +201014912997\n";
    cout << "Available: 10 AM - 8 PM\n";
}

void Supporter::showFAQ() {
    cout << "\n[Frequently Asked Questions]\n";
    cout << "Q: Can I cancel my booking?\nA: Yes, but at least 24h in advance.\n\n";
    cout << "Q: Can I pay with card and cash split?\nA: No, only one payment method.\n\n";
    cout << "Q: Can someone else drive the car?\nA: No, only the registered renter.\n";
}

void Supporter::collectUserQuestion() {
    cin.ignore();
    string name, question, email;
    cout << "\nEnter your name: ";
    getline(cin, name);
    cout << "Enter your E-mail: ";
    getline(cin, email);
    cout << "What's your question? ";
    getline(cin, question);

    ofstream file("SupportQuestions.txt", ios::app);
    if (file.is_open()) {
        file << "Name: " << name << "\n";
        file << "Question: " << question << "\n---\n";
        file.close();
        cout << "-Thank you " << name << "! Your question has been submitted.\n";
    }
    else {
        cout << "Error saving your question.\n";
    }
}

void Supporter::sendLiveChat() {
    cin.ignore();
    string phone, message;
    cout << "\nEnter your phone number (11 digits): ";
    getline(cin, phone);
    if (phone.length() != 11 || !all_of(phone.begin(), phone.end(), ::isdigit)) {
        cout << "Invalid phone number.\n";
        return;
    }

    cout << "Enter your message: ";
    getline(cin, message);

    ofstream file("LiveChatMessages.csv", ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        char dt[100];
        ctime_s(dt, sizeof(dt), &now);
        dt[strcspn(dt, "\n")] = '\0';  // remove newline
        file << phone << "," << message << "," << "(no reply yet)" << "," << dt << "," << "(no reply timestamp)" << "\n";
        file.close();
        cout << "Your message has been sent.\n";
        cout << "We will reply within 5 minutes.\n";
    }
}

void Supporter::showReplies() {
    cin.ignore();
    string phone;
    cout << "\nEnter your phone number to check replies: ";
    getline(cin, phone);

    if (phone.length() != 11 || !all_of(phone.begin(), phone.end(), ::isdigit)) {
        cout << "Invalid phone number.\n";
        return;
    }

    ifstream file("LiveChatMessages.csv");
    string line;
    bool foundPhone = false;

    cout << "\n--- Your Messages and Replies ---\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string ph, message, reply, sentTime, replyTime;
        getline(ss, ph, ',');
        getline(ss, message, ',');
        getline(ss, reply, ',');
        getline(ss, sentTime, ',');
        getline(ss, replyTime);

        if (ph == phone) {
            foundPhone = true;
            cout << "Message     : " << message << "\n";
            cout << "Reply       : " << reply << "\n";
            cout << "Sent at     : " << sentTime << "\n";
            cout << "Reply at    : " << (replyTime == "(no reply timestamp)" ? "Pending" : replyTime) << "\n";
            cout << "---------------------------------\n";
        }
    }
    file.close();

    if (!foundPhone) {
        cout << "No messages found for this number.\n";
    }
}
