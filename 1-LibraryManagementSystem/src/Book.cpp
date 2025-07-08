#include "Book.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;

//Default constructor
Book::Book(){
  bookID=0;
  title="";
  author="";
publisher="";
  quantity=0;
}

//Parameterized constructor
Book::Book(int id, const string& t, const string& a, const string& p, int q) {
bookID = id;
  title = t;
  author = a;
  publisher = p;
  quantity = q;  

}

//Setter methods
void Book::setBookID(int id){
  bookID = id;
}
void Book::setTitle(const string& t){
  title = t;
}
void Book::setAuthor(const string& a){
  author = a;
}
void Book::setPublisher(const string& p){
  publisher = p;
}
void Book::setQuantity(int q){
  quantity = q;
}

//Getter methods
int Book::getBookID() const {
  return bookID;
}
string Book::getTitle() const {
  return title;
}
string Book::getAuthor() const {
  return author;
}
string Book::getPublisher() const {
  return publisher;
}
int Book::getQuantity() const {
  return quantity;
}

//Input from user
void Book::inputBook() {
    cout << "\n📘 Enter Book Details:\n";

    // Book ID
    cout << "Enter Book ID: ";
    while (!(cin >> bookID)) {
        cout << "❌ Invalid input! Enter a number for Book ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();  // clear buffer after number input

    // Title
    cout << "Enter Title: ";
    getline(cin, title);

    // Author
    cout << "Enter Author: ";
    getline(cin, author);

    // Publisher
    cout << "Enter Publisher: ";
    getline(cin, publisher);

    // Quantity
    cout << "Enter Quantity: ";
    while (!(cin >> quantity) || quantity < 0) {
        cout << "❌ Invalid input! Enter a positive number for Quantity: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\n✅ Book details entered successfully!\n";
}


//Display book details
void Book::displayBook() const {
    cout << "\n📚 Book Details:\n";
    cout << "-----------------------------\n";
    cout << "Book ID     : " << bookID << "\n";
    cout << "Title       : " << title << "\n";
    cout << "Author      : " << author << "\n";
    cout << "Publisher   : " << publisher << "\n";
    cout << "Quantity    : " << quantity << "\n";
    cout << "-----------------------------\n";
}

//Convert book to string for file storage
string Book::serialize()const{
  ostringstream oss;
  oss<<bookID<<"|"<<title<<"|"<<author<<"|"<<publisher<<"|"<<quantity;
return oss.str();
}

//Load book from string
void Book::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() != 5) {
        std::cerr << "❌ Invalid data format: " << data << "\n";
        return;
    }

    try {
        bookID = std::stoi(tokens[0]);
        title = tokens[1];
        author = tokens[2];
        publisher = tokens[3];
        quantity = std::stoi(tokens[4]);
    } catch (const std::exception& e) {
        std::cerr << "❌ Error while parsing book data: " << data << "\n";
        std::cerr << "Reason: " << e.what() << "\n";
    }
}
