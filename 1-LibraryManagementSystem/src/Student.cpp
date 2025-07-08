#include "../include/Student.h"
#include<sstream>
#include<fstream>

Student::Student(const std::string& id, const std::string& name, const std::string& password)
    : id(id), name(name), password(password) {}

    //Getters
    std::string Student::getId() const{
      return id;
    }
    std::string Student::getName() const{
      return name;
    }
    std::string Student::getPassword() const{
      return password;
    }

    //Register new student

   void Student::inputStudent() {
    std::cout << "\n👩‍🎓 Register New Student\n";
    std::cout << "Enter Student ID: ";
    std::cin >> id;
    std::cin.ignore();  // clear input buffer

    std::cout << "Enter Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    std::cout << "✅ Student registered successfully!\n";
}

//Convert string format for file writing 
std::string Student::serialize() const {
  return id+","+name+","+password;
}

//Convert string line from file to student object
void Student::deserialize(const std::string& data){
  std::stringstream ss(data);
  std::getline(ss, id, ',');
  std::getline(ss, name, ',');  
  std::getline(ss, password, ',');
}

//Authenticate student
bool Student::authenticate(const std::string& enteredId, const std::string& enteredPassword) {
std::ifstream file("data/students.txt");
if(!file){
  std::cout << "❌ Cannot open students.txt for reading.\n";
        return false;
}
std::string line;
while(std::getline(file,line)){
  Student temp;
temp.deserialize(line);
if(temp.id == enteredId && temp.password == enteredPassword){
  this->id = temp.id;
  this->name = temp.name;
  this->password = temp.password;
  return true;
}
}
return false;

}

//Register new student
void Student::registerStudent(){
  this->inputStudent();

  std::ofstream file("data/students.txt", std::ios::app);
  if(!file){
     std::cout << "❌ Could not open students.txt for writing.\n";
        return;
  }
  file <<this->serialize()<<"\n";
  file.close();
  std::cout << "✅ Student registered successfully!\n";
}