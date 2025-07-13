#ifndef ADMIN_H
#define ADMIN_H

#include "Library.h"

void showAdminMenu(Library& lib);
void viewIssuedRecords();
void deleteStudentByID(const std::string& studentID);

#endif
