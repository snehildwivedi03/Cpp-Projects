#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<string>

class Student {
  private:
  std::string id;
  std::string name;
  std::string password;
 
  public:
  //constructors
  Student() = default;
  Student(const std::string& id, const std::string& name, const std::string& password);

  //Accessors
    std::string getId() const;
    std::string getName() const;
    std::string getPassword() const;

    //Input and Auth
    void inputStudent();
    bool authenticate(const std::string& id, const std::string& password);

    //Register new student
    void registerStudent ();
    //file handling
    std::string serialize() const;
    void deserialize(const std::string& data);
  
  
};


#endif