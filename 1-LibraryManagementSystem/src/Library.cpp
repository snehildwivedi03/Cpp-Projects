#include "../include/Library.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

//Load books from file int the book map

void Library::loadBooksFromFile() {
  ifstream file(filename);
  if(!file){
      cout << "⚠️  Could not open " << filename << " for reading. Starting with an empty library.\n";
        return;
  }
  string line;
  while(getline(file,line)){
    Book b;
    b.deserialize(line);
    books[b.getBookID()]=b;
  }
  file.close();
  cout << "✅ Loaded " << books.size() << " books from " << filename << ".\n";
}

//Save books to file from the book map
void Library::saveBooksToFile(){
  ofstream file(filename);
  if(!file){
   cout << "❌ Error opening " << filename << " for writing!\n";
        return;
    }
    for(const auto& pair : books){
      file<<pair.second.serialize()<<"\n";
    }
    file.close();
    cout << "✅ Library data saved to " << filename << ".\n";
  
}

//Add a new book to the library

void Library::addBook(const Book& book){
  int id = book.getBookID();

  //Check if the book already exists

  if(books.find(id)!=books.end()){
    cout << "❌ Book with ID " << id << " already exists!\n";
        return;
  }
  books[id] = book;
  cout << "✅ Book with ID " << id << " added successfully.\n";
}

//Display all books in the library

void Library::displayBooks() const{
    if (books.empty()) {
        cout << "📭 No books available in the library.\n";
        return;
    }

    cout << "\n📚 All Books in Library:\n";
    cout << "==============================\n";
    for (const auto& pair : books) {
        pair.second.displayBook();
        cout << "------------------------------\n";
    }
}

//Delete a book by ID
void Library::deleteBook(int id){
  auto it = books.find(id);
  if(it != books.end() ){
    books.erase(it);
    cout << "✅ Book with ID " << id << " deleted successfully.\n";
  } else {
    cout << "❌ Book with ID " << id << " not found!\n";
  }
}

//Issue a book by ID
void Library::issueBook(int id){
  auto it = books.find(id);
  if(it != books.end()){
    if(it->second.getQuantity()>0){
      it->second.setQuantity(it->second.getQuantity()-1);
      cout << "✅ Book with ID " << id << " issued successfully.\n";
    }else{
      cout << "❌ Book with ID " << id << " is out of stock!\n";
    }
    } else{
      cout << "❌ Book with ID " << id << " not found!\n";
    }
  
}

//Return a book by ID
void Library::returnBook(int id){
  auto it = books.find(id);
  if(it !=books.end()){
    it->second.setQuantity(it->second.getQuantity()+1);
    cout << "✅ Book with ID " << id << " returned successfully.\n";
  } else {
    cout << "❌ Book with ID " << id << " not found!\n";
  }
  saveBooksToFile(); // Save updated quantity

}

//Search for a book by ID
void Library::searchBookById(int id) const {
    auto it = books.find(id);
    if (it != books.end()) {
        const Book& book = it->second;
        cout << "\n🔍 Book Found:\n";
        cout << "ID: " << book.getBookID() << "\n";
        cout << "Title: " << book.getTitle() << "\n";
        cout << "Author: " << book.getAuthor() << "\n";
        cout << "Publisher: " << book.getPublisher() << "\n";
        cout << "Quantity: " << book.getQuantity() << "\n";
    } else {
        cout << "❌ Book with ID " << id << " not found in the library.\n";
    }
}
