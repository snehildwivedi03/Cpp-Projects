#ifndef UTILS_H
#define UTILS_H
#include<string>
#include"./Library.h"
void recordIssueBook(const std::string& studentId, int bookID );
 void viewIssuedBooks(const std::string& studentId);
 void removeIssueRecord(const std::string& studentId, int bookID);
    void returnBookForStudent(const std::string& studentID, Library& lib); 







#endif