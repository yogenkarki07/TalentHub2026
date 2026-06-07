#include <iostream>
#include <limits>
#include "Headers/menu.h"
#include "Headers/student.h"
// #include "Headers/filehandler.h"
using namespace std;

 int main() {
     int choice;

     do {
         vector<Student> students;
         DisplayMenu();
         cin >> choice;

         cin.ignore(numeric_limits<streamsize>::max(), '\n');             //proper input buffer clearing

         switch (choice){
         case 1:
             StudentRegistration(students);
             break;
         case 2:
         //    AdminLogin();
             break;
         case 3:
             StudentLogin(students);
             break;
         case 4:
             cout << "Thank you for visiting Talent Hub ! \n";
             break;
         default:
             cout << "Invalid Choice. Please, choose Between 1 to 4. \n";
             break;
         }
     } while (choice != 4);
     return 0;
 }
