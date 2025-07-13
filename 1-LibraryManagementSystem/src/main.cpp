#include "../include/Book.h"
#include "../include/Library.h"
#include "../include/Student.h"  
#include "../include/Utils.h"  
#include "../include/Admin.h"  

#include <iostream>

using namespace std;


// =================== Student Menu ===================
void showStudentMenu(const string& studentID, Library& lib) {
    int choice;
    do {
        cout << "\n👩‍🎓 ======= Student Menu =======\n";
        cout << "1. Issue Book\n";
        cout << "2. Return Book\n";
        cout << "3. View My Issued Books\n";
        cout << "0. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                cout << "Enter Book ID to issue: ";
                cin >> id;
                lib.issueBook(id);
                recordIssueBook(studentID, id);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Book ID to return: ";
                cin >> id;
                returnBookForStudent(studentID, id, lib);
                break;
            }
            case 3:
                viewIssuedBooks(studentID);
                break;
            case 0:
                cout << "👋 Student logged out.\n";
                break;
            default:
                cout << "❌ Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

// =================== Main ===================
int main() {
    Library lib;
    lib.loadBooksFromFile();

    int choice;
    while (true) {
        cout << "\n📚 ======= Library System Main Menu =======\n";
        cout << "1. Student Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Register New Student\n";
        cout<<"4. Register New Admin\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                string id, password;
                cout << "Student ID: ";
                cin >> id;
                cout << "Password: ";
                cin >> password;

                Student s;
                if (s.authenticate(id, password)) {
                    cout << "✅ Login successful.\n";
                    showStudentMenu(id, lib);
                } else {
                    cout << "❌ Login failed.\n";
                }
                break;
            }
            case 2: {
    string id, password;
    cout << "Admin ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> password;

    if (authenticateAdmin(id, password)) {
        cout << "✅ Admin login successful.\n";
        showAdminMenu(lib);
    } else {
        cout << "❌ Invalid Admin ID or Password.\n";
    }
    break;
}
            case 3: {
                Student s;
                s.registerStudent();
                break;
            }
            case 4:{
                registerNewAdmin();
                break;
            }
            default:
                cout << "❌ Invalid choice. Try again.\n";
        }
    }

    lib.saveBooksToFile();
    cout << "👋 Goodbye! Library data saved.\n";
    return 0;
}
