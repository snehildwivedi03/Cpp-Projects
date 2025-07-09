#include "../include/Utils.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<ctime>
#include <vector>

void recordIssuedBooK(const std::string& studentId, int bookID) {
std::ofstream file("data/issued_Books.txt",std::ios::app);
    if (!file) {
  std::cout << "❌ Failed to open issued_books.txt for writing.\n";
        return;
    
}

//Get current data and time

time_t now = time(0);
tm* ltm = localtime(&now);
char date[11];
snprintf(date, sizeof(date), "%04d-%02d-%02d",1900+ltm->tm_year,1+ltm->tm_mon,ltm->tm_mday);

file<<studentId<<","<<bookID<<","<<date<<"\n";
file.close();
 std::cout << "✅ Book " << bookID << " issued to " << studentId << " on " << date << ".\n";

}

void viewIssuedBooks(const std::string& studentId) {
std::ifstream file("data/issued_Books.txt");
    if (!file){
      std::cout<< "❌ Failed to open issued_books.txt for reading.\n";
        return;
    }
std::string line;
bool found = false;
while(std::getline(file,line)){
std::stringstream ss(line);
std::string sid,bid,date;
 std::getline(ss, sid, ',');
        std::getline(ss, bid, ',');
        std::getline(ss, date, ',');
        if(sid == studentId) {
          found = true;
          std::cout<< "📚 Book ID: " << bid << ", Issued on: " << date << "\n";
        }
}
if(!found) {
  std::cout << "❌ No books issued to student ID: " << studentId << ".\n";
}
}

//removeIssuedBook
void removeIssueRecord(const std::string& studentID, int bookID) {
    std::ifstream inFile("data/issued_books.txt");
    if (!inFile) {
        std::cout << "❌ Failed to open issued_books.txt for reading.\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Keep only the lines that are NOT the one we want to remove
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string sid, bid, date;
        std::getline(ss, sid, ',');
        std::getline(ss, bid, ',');
        std::getline(ss, date, ',');

        if (!(sid == studentID && std::to_string(bookID) == bid)) {
            lines.push_back(line);
        }
    }
    inFile.close();

    // Rewrite the file with remaining records
    std::ofstream outFile("data/issued_books.txt");
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    std::cout << "🧹 Issued record for Book ID " << bookID << " removed for Student ID " << studentID << ".\n";
}

