#ifndef ADMIN_H
#define ADMIN_H

#include "./Library.h"

bool authenticateAdmin(const std::string& adminID, const std::string& password);
void showAdminMenu(Library& lib);
void viewIssuedRecords();
void deleteStudentByID(const std::string& studentID);
void registerNewAdmin();

#endif
