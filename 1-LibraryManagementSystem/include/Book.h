//Book.h
#ifndef BOOK_H
#define BOOK_H

#include<iostream>
#include<string>

class Book{
  private:
    int bookID;
    std::string title;
    std::string author;
    std::string publisher;
    int quantity;
  
  
  public:
    // Constructor
    Book();

    // Parameterized constructor
Book(int id, const std::string& t, const std::string& a, const std::string& p, int q);

//Setter methods
    void setBookID(int id);
    void setTitle(const std::string& t);
void setAuthor(const std::string& a);
    void setPublisher(const std::string& p);
    void setQuantity(int q);

    // Getter methods
    int getBookID() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getQuantity() const;

    //Input and Display
  void inputBook();
  void displayBook() const;

  //File Handling
  std::string serialize() const ; //convert object to string for file storage
  void deserialize(const std::string& data); //convert string back to object
};
#endif