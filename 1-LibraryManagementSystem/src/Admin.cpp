#include "../include/Admin.h"
#include "../include/Utils.h" // for helper file paths
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Show all issued books with due dates
void viewIssuedRecords() {
    ifstream file("data/issued_books.txt");
    if (!file) {
        cout << "❌ Failed to open issued_books.txt\n";
        return;
    }

    string line;
    cout << "\n📋 All Issued Book Records:\n";
    cout << left << setw(15) << "Student ID" << setw(10) << "Book ID" << setw(15) << "Issued Date" << setw(15) << "Due Date\n";
    cout << "-----------------------------------------------------\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string sid, bid, date;
        getline(ss, sid, ',');
        getline(ss, bid, ',');
        getline(ss, date, ',');

        // Calculate due date (7 days from issued date)
        int year, month, day;
        sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
        tm due = {};
        due.tm_year = year - 1900;
        due.tm_mon = month - 1;
        due.tm_mday = day + 7;
        mktime(&due);

        char dueDate[11];
        snprintf(dueDate, sizeof(dueDate), "%04d-%02d-%02d", 1900 + due.tm_year, 1 + due.tm_mon, due.tm_mday);

        cout << left << setw(15) << sid << setw(10) << bid << setw(15) << date << setw(15) << dueDate << "\n";
    }

    file.close();
}

// Delete a student by ID
void deleteStudentByID(const string& studentID) {
    ifstream inFile("data/students.txt");
    ofstream outFile("data/temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string sid;
        getline(ss, sid, ',');
        if (sid != studentID) {
            outFile << line << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("data/students.txt");
    rename("data/temp.txt", "data/students.txt");

    if (found)
        cout << "🗑️ Student ID " << studentID << " deleted.\n";
    else
        cout << "❌ Student ID not found.\n";
}

// Admin Menu (Moved from main.cpp)
void showAdminMenu(Library& lib) {
    int choice;
    do {
        cout << "\n👨‍💼 ======= Admin Menu =======\n";
        cout << "1. View All Issued Records\n";
        cout << "2. Add Book\n";
        cout << "3. Delete Book\n";
        cout << "4. Delete Student\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewIssuedRecords();
                break;
            case 2: {
                Book b;
                b.inputBook();
                lib.addBook(b);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            }
            case 4: {
                string sid;
                cout << "Enter Student ID to delete: ";
                cin >> sid;
                deleteStudentByID(sid);
                break;
            }
            case 0:
                cout << "👋 Admin logged out.\n";
                break;
            default:
                cout << "❌ Invalid choice.\n";
        }

    } while (choice != 0);
}
