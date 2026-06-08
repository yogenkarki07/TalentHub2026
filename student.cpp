#include <iostream>
#include <vector>

#include "Headers/student.h"
#include "Headers/validation.h"
#include "Headers/filehandler.h"
#include "Headers/menu.h"

void StudentRegistration(vector<Student>& students) {

    Student s;

    cout << "+==============================================================+\n";
    cout << "|                                                              |\n";
    cout << "|                  Student Registration Form                   |\n";
    cout << "|                                                              |\n";
    cout << "+==============================================================+\n\n";

    cout << "                   First name: ";
    cin >> s.firstname;

    cout << "                   Last name: ";
    cin >> s.lastname;

    cout << "                   Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "                   Email: ";
    getline(cin,s.email);

    do{
        cout << "                   Password: ";
        getline(cin,s.password);

        if (!isValidPassword(s.password)){
            cout << "                   Password must contain: " << endl;
            cout << "                   - Minimum 8 characters " << endl;
            cout << "                   - Uppercase character " << endl;
            cout << "                   - Lowercase character " << endl;
            cout << "                   - Number" << endl;
            cout << "                   - Special character \n\n";
        }
    }while (!isValidPassword(s.password));

    cout << "                   Phone Number: ";
    getline(cin,s.phone);

    cout << "                   Address: ";
    getline(cin,s.address);

    cout << "                   Student Type (Domestic/International): ";
    getline(cin,s.type);

    students.push_back(s);
    SaveStudentInfo(students);

    cout << "+----------------------------------------------------------------+ \n\n";

    cout << "|                      Registration successful.                  | \n\n";

    cout << "+----------------------------------------------------------------+ \n\n";

}

void StudentLogin(vector<Student>& students) {
    Student s;
    string password, email;

    cout << "+==============================================================+\n";
    cout << "|                                                              |\n";
    cout << "|                      Student Login                           |\n";
    cout << "|                                                              |\n";
    cout << "+==============================================================+\n\n";

    cout << "                   Email: ";
    getline(cin, email);

    cout << "                   Password: ";
    getline(cin, password);

    for (Student& s : students){
        if ( s.email == email && s.password == password){
            cout << "+--------------------------------------------------------------+\n\n";

            cout << "|                Log-in successful.                           |\n\n";

            cout << "+-------------------------------------------------------------+\n\n";

            StudentDashboard(students);

            return;
        }
    }
    cout << "+--------------------------------------------------------------+\n\n";

    cout << "|                  Invalid Email/Password.                     |\n\n";

    cout << "+--------------------------------------------------------------+\n\n";
}

void StudentDashboard(vector<Student>& students) {
     // Student s;
    int choice;

    cout << "+==============================================================+\n";
    cout << "|                                                              |\n";
    cout << "|                      Student Dashboard                       |\n";
    cout << "|                                                              |\n";
    cout << "+==============================================================+\n\n";
    cout << "+--------------------------------------------------------------+\n\n";
    cout << "     " << "1. Student Details" <<"     " << "2. Available Courses" << endl << endl;
    cout << "     " << "3. Enroll Courses" << "     " << "4. Logout" << endl << endl;
    cout << "+--------------------------------------------------------------+\n\n";
    cout << "               " << "Enter your choice: ";
    cin >> choice;

    do {
        switch (choice) {
            case 1:
                 // StudentDetails(student);
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                DisplayMenu();
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } while (choice != 4);
}

// void StudentDetails(Student& student) {
//
//     cout << "+==============================================================+\n";
//     cout << "|                                                              |\n";
//     cout << "|                      Student Details                         |\n";
//     cout << "|                                                              |\n";
//     cout << "+==============================================================+\n\n";
//
//     cout << "+--------------------------------------------------------------+\n\n";
//     cout << "                   Name: " << student.firstname << " " << student.lastname << endl;
//     cout << "                   Age: " << student.age  << endl;
//     cout << "                   Email: " << student.email  << endl;
//     cout << "                   Password: " << student.password  << endl;
//     cout << "                   Phone: " << student.phone  << endl;
//     cout << "                   Address: " << student.address  << endl;
//     cout << "                   Student Type: " << student.type  << endl;
//     cout << "+--------------------------------------------------------------+\n\n";
//
// }