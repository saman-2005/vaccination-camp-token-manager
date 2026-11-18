#include<iostream>
#include<string>
using namespace std;

class bloodpressure {
    private:
    int participantID;
    string name;
    int age;
    int systolic;
    int diastolic;
    string date;
    string category;

    static int totalRecords;

    public:
    void setDetails(int id, string n, int a, int s, int d, string dt) {
        this->participantID = id;
        this->name = n;
        this->age = a;
        this->systolic = s;
        this->diastolic = d;
        this->date = dt;

        if (s >= 140 || d >= 90) {
            category = "High";
        }
        else if (s >= 120 || d >= 80) {
            category = "Elevated";
        }
        else {
            category = "Normal";
        }

        totalRecords++;
    }

    inline void display() {
        cout << "\nParticipant ID: " << participantID;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nSystolic BP: " << systolic;
        cout << "\nDiastolic BP: " << diastolic;
        cout << "\nDate: " << date;
        cout << "\nCategory: " << category << endl;
    }

    int getID() {
        return participantID;
    }

    string getCategory() {
        return category;
    }

    static int getTotal() {
        return totalRecords;
    }

    friend void showRecord(bloodpressure obj);
    friend class CampAdmin;
};

int bloodpressure::totalRecords = 0;

void showRecord(bloodpressure obj) {
    cout << "\nRegistered Participant: " << obj.name;
    cout << "\nParticipant ID: " << obj.participantID << endl;
}

class CampAdmin {
    public:
    void showPrivateData(bloodpressure obj) {
        cout << "\nAdmin Access: " << obj.name;
        cout << "\nBP Reading: " << obj.systolic << "/" << obj.diastolic << endl;
    }
};

const int SIZE = 100;

bool checkDuplicate(bloodpressure arr[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].getID() == id) {
            return true;
        }
    }
    return false;
}

void byValue(int x) {
    x = x + 10;
    cout << "\nInside Call by Value: " << x;
}

void byAddress(int *x) {
    *x = *x + 10;
}

void byReference(int &x) {
    x = x + 10;
}

int countHigh(bloodpressure arr[], int count, int index) {
    if (index == count) {
        return 0;
    }

    int current = 0;

    if (arr[index].getCategory() == "High") {
        current = 1;
    }

    return current + countHigh(arr, count, index + 1);
}

void addRecord(bloodpressure arr[], int &count) {
    if (count == SIZE) {
        cout << "\nStorage is full!";
        return;
    }

    int id, age, sys, dia;
    string name, date;

    cout << "\nEnter Participant ID: ";
    cin >> id;

    if (id <= 0 || checkDuplicate(arr, count, id)) {
        cout << "\nInvalid or Duplicate ID!";
        return;
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Systolic BP: ";
    cin >> sys;

    cout << "Enter Diastolic BP: ";
    cin >> dia;

    cin.ignore();

    cout << "Enter Screening Date: ";
    getline(cin, date);

    if (age <= 0 || age > 120 ||
        sys < 50 || sys > 300 ||
        dia < 30 || dia > 200 ||
        name.empty() || date.empty()) {
        cout << "\nInvalid Details!";
        return;
    }

    arr[count].setDetails(id, name, age, sys, dia, date);

    count++;

    cout << "\nRecord Added Successfully!";

    showRecord(arr[count - 1]);
}

void viewRecords(bloodpressure arr[], int count) {
    if (count == 0) {
        cout << "\nNo Records Found!";
        return;
    }

    bloodpressure *ptr = arr;

    cout << "\n===== BLOOD PRESSURE RECORDS =====\n";

    for (int i = 0; i < count; i++) {
        (ptr + i)->display();
    }

    cout << "\nTotal Records: " << bloodpressure::getTotal();
}

void demonstrate() {
    cout << "\n===== C++ CONCEPTS =====";

    int a = 10;
    int &ref = a;
    ref = 20;

    cout << "\nReference Variable: " << a;

    int x = 5;
    byValue(x);

    cout << "\nAfter Call by Value: " << x;

    int y = 5;
    byAddress(&y);

    cout << "\nAfter Call by Address: " << y;

    int z = 5;
    byReference(z);

    cout << "\nAfter Call by Reference: " << z;

    cout << "\n\nProcedural Programming uses functions.";
    cout << "\nOOP combines data and functions in classes.";
}

int main() {
    bloodpressure arr[SIZE];

    int count = 0;
    int choice;

    do {
        cout << "\n\n===== BLOOD PRESSURE CAMP ANALYZER =====";
        cout << "\n1. Add Screening Record";
        cout << "\n2. View Records";
        cout << "\n3. Demonstrate C++ Concepts";
        cout << "\n4. Admin Access";
        cout << "\n5. Count Records Using Recursion";
        cout << "\n0. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord(arr, count);
                break;

            case 2:
                viewRecords(arr, count);
                break;

            case 3:
                demonstrate();
                break;

            case 4: {
                if (count > 0) {
                    int id;
                    bool found = false;

                    cout << "\nEnter Participant ID: ";
                    cin >> id;

                    for (int i = 0; i < count; i++) {
                        if (arr[i].getID() == id) {
                            CampAdmin admin;
                            admin.showPrivateData(arr[i]);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "\nParticipant Not Found!";
                    }
                }
                else {
                    cout << "\nNo Records Available!";
                }
                break;
            }

            case 5:
                cout << "\nTotal High BP Records: "
                     << countHigh(arr, count, 0);
                break;

            case 0:
                cout << "\nThank You!";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 0);

    return 0;
}
