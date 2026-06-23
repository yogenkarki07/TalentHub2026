#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "Headers/student.h"
#include "Headers/validation.h"
#include "Headers/filehandler.h"
#include "Headers/course.h"

int GenerateStudentID(vector<Student>& students) {
    int maxID = 100;
    for (Student& s : students) {
        if (s.studentID > maxID) {
            maxID = s.studentID;
        }
    }
    return maxID +1 ;
}

void StudentRegistration(vector<Student>& students) {

    Student s;

    cout << "\n+===============================================================================================+\n";
    cout << "|                                                                                               |\n";
    cout << "|                                  Student Registration Form                                    |\n";
    cout << "|                                                                                               |\n";
    cout << "+===============================================================================================+\n\n";

    s.studentID = GenerateStudentID(students);
    cout << setw(55) << "Student ID: " << s.studentID << endl;

    cout << setw(55) << "\n First name: ";
    cin >> s.firstname;

    cout << setw(55) << "\n Last name: ";
    cin >> s.lastname;

    cout << setw(55) << "\n Age: ";
    cin >> s.age;

    cin.ignore();

    do {
        cout << setw(55) << "\n Email: ";
        getline(cin,s.email);

        if (!isValidEmail(s.email)) {
            cout << setw(55) << "\n Invalid Email !" << endl;
        }

    }while (!isValidEmail(s.email));

    do{
        cout << setw(55) << "\n Password: ";
        getline(cin,s.password);

        if (!isValidPassword(s.password)){
            cout << setw(55) << "\n Password must contain: " << endl;
            cout << setw(55) << " - Minimum 8 characters " << endl;
            cout << setw(55) << " - Uppercase character " << endl;
            cout << setw(55) << " - Lowercase character " << endl;
            cout << setw(55) << " - Number" << endl;
            cout << setw(55) << " - Special character \n\n";
        }
    }while (!isValidPassword(s.password));

    cout << setw(55) << "\n Phone Number: ";
    getline(cin,s.phone);

    cout << setw(55) << "\n Address: ";
    getline(cin,s.address);

    cout << setw(55) << "\n Student Type (Domestic/International): ";
    getline(cin,s.type);

    for (const Student& existing : students) {
        if (existing.email == s.email) {
            cout << setw(55) << "Invalid email ! " << s.email << " is already registered." << endl;
            return;
        }
    }

    students.push_back(s);

    SaveStudentInfo(students);

    cout << "\n+-----------------------------------------------------------------------------------------------------------+ \n\n";

    cout << "|                                  Student Registered Successfully !                                        | \n\n";

    cout << "+-----------------------------------------------------------------------------------------------------------+ \n\n";

}

void StudentLogin(vector<Student>& students) {
    string password, email;

    cout << "\n+===============================================================================================+\n";
    cout << "|                                                                                               |\n";
    cout << "|                                        Student Login                                          |\n";
    cout << "|                                                                                               |\n";
    cout << "+===============================================================================================+\n\n";

    cin.ignore();         // input buffer clearing

    cout << setw(55) << "\n Email: ";
    getline(cin, email);

    cout << setw(55) << "\n Password: ";
    getline(cin, password);

    for (Student& s : students){
        if ( s.email == email && s.password == password){

            cout << "\n+-------------------------------------------------------------------------------------------------+ \n\n";

            cout << "|                               Student Logged-In Successfully !                                  | \n\n";

            cout << "+-------------------------------------------------------------------------------------------------+ \n\n";

            coursesFlow( s, students);
            return;
        }
    }
    cout << "\n+-------------------------------------------------------------------------------------------------+ \n\n";

    cout << "|                                Invalid Email / Password !                                       | \n\n";

    cout << "+-------------------------------------------------------------------------------------------------+ \n\n";

}