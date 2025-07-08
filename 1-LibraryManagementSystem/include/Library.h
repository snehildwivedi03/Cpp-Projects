#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include<map>
#include<string>

class Library{
  private:
  std::map<int, Book> books;
  const std::string filename = "data/books.txt";
  public:
  //File Handling
  void loadBooksFromFile();
  void saveBooksToFile();
  
  //Book Operations
  void addBook(const Book& book);
  void displayBooks()const ;
  void searchBookById(int id) const;
  void deleteBook(int id);
  void issueBook(int id);
  void returnBook(int id);
  
};
#endif