#include <iostream>
#include <vector>

#include "Headers/student.h"

void StudentRegistration(vector<Student>& students) {

    Student s;

    cout << "+==============================================================+\n";
    cout << "|                                                              |\n";
    cout << "|                  Student Registration Form                   |\n";
    cout << "|                                                              |\n";
    cout << "+==============================================================+\n\n";

    cout << "---------------------------------------------------------------\n\n";

    cout << "|                   Enter first name:     ";
    cin >> s.firstname;

    cout << "                   Enter last name:                       ";
    cin >> s.lastname;

    cout << "                   Enter age:                             ";
    cin >> s.age;

    cin.ignore();

    cout << "                   Enter email address:                    ";
    getline(cin,s.email);

    cout << "                   Enter password:                        ";
    getline(cin,s.password);

    cout << "                   Enter phone number:                      ";
    getline(cin,s.phone);

    cout << "                   Enter Address:                      ";
    getline(cin,s.address);

    cout << "                   Student Type: (Domestic or International):                      ";
    getline(cin,s.type);

    students.push_back(s);

    cout << "-------------------------------------------------------------- \n\n";

    cout << "                   Student Registered successfully !           \n\n";

    cout << "---------------------------------------------------------------\n\n";

}

void StudentLogin(vector<Student>& students) {
    Student s;

    cin.ignore();
    cout << "Enter email address ." << endl;
    getline(cin,s.email);

    cout << "Enter password ." << endl;
    getline(cin,s.password);

    students.push_back(s);
    cout << "Student sign-in successfully ! \n";
}