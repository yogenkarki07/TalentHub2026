#include <iostream>
#include <iomanip>

#include <limits>
#include "Headers/menu.h"
#include "Headers/student.h"
#include "Headers/filehandler.h"
#include "Headers/Admin.h"

using namespace std;

 int main() {
     vector<Student> students;
     LoadStudentInfo(students);
     LoadCourseEnrollments(students);

     int choice;

     do {
         DisplayMenu();
         if (!(cin >> choice)){
             cout << "\n                                           Invalid input! Please enter a number: " << endl << endl;
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');      //proper input buffer clearing
             continue;
         }

         switch (choice){
         case 1:
             StudentRegistration(students);
             break;

         case 2: {
             Admin loggedIn;
             AdminMenu(loggedIn, students);
             break;
         }

         case 3:
             StudentLogin(students);
             break;

         case 4:
                 cout << "\n+===================================================================+\n";
                 cout << "|                                                                   |\n";
                 cout << "|                   THANK YOU FOR USING TALENT HUB                  |\n";
                 cout << "|                                                                   |\n";
                 cout << "+===================================================================+\n\n";
             break;

         default:
             cout << "\n                                           Invalid Choice. Please, choose Between 1 to 4. \n\n";
             break;
         }
     } while (choice != 4);
     return 0;
 }



