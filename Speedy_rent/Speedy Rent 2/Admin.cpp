#include "Admin.h"


bool Admin::login() {
    string pass;
    cout << "Enter admin password: ";
    cin >> pass;
    return pass == password;
}

void Admin::manage(vector<Car>& cars) {
    int c;
    cout << "1. Add\n2. Remove\n3. Mark Unavailable\n4. Add Penalty\n5. Reply Messages\nChoose: ";
    cin >> c;

    if (c == 1) {
        string id, mk, mdl, typ, f, cat, col, tr, stat = "Available";
        double pr;
        cout << "Enter ID Make Model Type Fuel Category Price Color Transmission:\n";
        cin >> id >> mk >> mdl >> typ >> f >> cat >> pr >> col >> tr;
        cars.emplace_back(id, mk, mdl, typ, f, cat, pr, stat, col, tr);
        appendToFile(cars.back());
    }
    else if (c == 2) {
        string id;
        cout << "ID to remove: ";
        cin >> id;
        auto it = remove_if(cars.begin(), cars.end(), [&](Car& car) { return car.id == id; });
        cars.erase(it, cars.end());
        writeAllToFile(cars);
    }
    else if (c == 3) {
        string id;
        cout << "ID to disable: ";
        cin >> id;
        for (auto& car : cars) {
            if (car.id == id) car.status = "Unavailable";
        }
        writeAllToFile(cars);
    }
    else if (c == 4) {
        string phone, reason;
        double amt;
        cout << "Enter Customer Phone and Penalty Amount: ";
        cin >> phone >> amt;
        cin.ignore();
        cout << "Enter Reason for Penalty: ";
        getline(cin, reason);
        PenaltyManager::addPenalty(phone, amt, reason);
    }
    else if (c == 5) {
        replyToUsers();
    }
}

void Admin::appendToFile(const Car& car) {
    ofstream file(carsFile, ios::app);
    if (file.is_open()) {
        file << car.id << "," << car.make << "," << car.model << "," << car.type << "," << car.fuel << "," << car.category << ","
            << car.dailyPrice << "," << car.status << "," << car.color << "," << car.transmission << "\n";
        file.close();
    }
}

void Admin::writeAllToFile(const vector<Car>& cars) {
    ofstream file(carsFile);
    if (file.is_open()) {
        file << "ID,Make,Model,Type,Fuel,Category,Price,Status,Color,Transmission\n";
        for (const auto& car : cars) {
            file << car.id << "," << car.make << "," << car.model << "," << car.type << "," << car.fuel << "," << car.category << ","
                << car.dailyPrice << "," << car.status << "," << car.color << "," << car.transmission << "\n";
        }
        file.close();
    }
}

void Admin::replyToUsers() {
    vector<string> rows;
    vector<int> noReplyIndexes;
    string line;

    ifstream file("LiveChatMessages.csv");
    while (getline(file, line)) {
        rows.push_back(line);
    }
    file.close();

    while (true) {
        noReplyIndexes.clear();
        cout << "\nPending messages:\n";

        for (int i = 0; i < rows.size(); ++i) {
            stringstream ss(rows[i]);
            string phone, message, reply, sentTime, replyTime;
            getline(ss, phone, ',');
            getline(ss, message, ',');
            getline(ss, reply, ',');
            getline(ss, sentTime, ',');
            getline(ss, replyTime);

            if (reply == "(no reply yet)") {
                noReplyIndexes.push_back(i);
                cout << noReplyIndexes.size() << ". From " << phone << ": " << message << " (Sent at: " << sentTime << ")\n";
            }
        }

        if (noReplyIndexes.empty()) {
            cout << "No pending messages.\n";
            break;
        }

        cout << "\nEnter the number of the message to reply (0 to exit): ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;
        if (choice < 1 || choice > noReplyIndexes.size()) {
            cout << "Invalid selection. Try again.\n";
            continue;
        }

        int idx = noReplyIndexes[choice - 1];
        stringstream ss(rows[idx]);
        string phone, message, reply, sentTime, replyTime;
        getline(ss, phone, ',');
        getline(ss, message, ',');
        getline(ss, reply, ',');
        getline(ss, sentTime, ',');
        getline(ss, replyTime);

        cout << "Your reply to " << phone << ": ";
        string newReply;
        getline(cin, newReply);

        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);
        char replyTimestamp[100];
        strftime(replyTimestamp, sizeof(replyTimestamp), "%d/%m/%Y %H:%M:%S", &localTime);

        rows[idx] = phone + "," + message + "," + newReply + "," + sentTime + "," + replyTimestamp;
    }

    ofstream out("LiveChatMessages.csv");
    for (const string& row : rows) {
        out << row << "\n";
    }
    out.close();

    cout << "\nAll selected replies submitted.\n";
}
