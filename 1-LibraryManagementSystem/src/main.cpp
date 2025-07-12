#include "../include/Book.h"
#include "../include/Library.h"
#include "../include/Student.h"  
#include "../include/Utils.h"   
#include <iostream>

using namespace std;

void showAdminMenu(Library& lib) {
    int choice;
    do {
        cout << "\n👨‍💼 ======= Admin Menu =======\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Delete Book\n";
        cout << "5. Issue Book (admin)\n";
        cout << "6. Return Book (admin)\n";
        cout << "0. Logout & Save\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Book b;
                b.inputBook();
                lib.addBook(b);
                break;
            }
            case 2:
                lib.displayBooks();
                break;
            case 3: {
                int id;
                cout << "Enter Book ID to search: ";
                cin >> id;
                lib.searchBookById(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter Book ID to issue: ";
                cin >> id;
                lib.issueBook(id); // Will later connect to student
                break;
            }
            case 6: {
                int id;
                cout << "Enter Book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;
            }
            case 0:
                lib.saveBooksToFile();
                cout << "✅ Library saved. Admin logged out.\n";
                break;
            default:
                cout << "❌ Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}

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
                // 🔜 We'll connect this to student-issued data file
                lib.issueBook(id);  // Replace later with student logic
                recordIssueBook(studentID,id);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                //Removing the record from issued books 
              returnBookForStudent(studentID, lib);
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

int main() {
    Library lib;
    lib.loadBooksFromFile();

    int choice;
    while (true) {
        cout << "\n📚 ======= Library System Main Menu =======\n";
        cout << "1. Student Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Register New Student\n"; // inside main menu

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
                string adminPass;
                cout << "Enter Admin Password: ";
                cin >> adminPass;
                if (adminPass == "admin123") {
                    showAdminMenu(lib);
                } else {
                    cout << "❌ Incorrect Admin password.\n";
                }
                break;
            }
            case 3: {
    Student s;
    s.registerStudent();
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
