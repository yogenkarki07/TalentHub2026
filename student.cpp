#include <iostream>
#include <vector>
#include <iomanip>

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
    cout << "\n" << setw(55) << "Student ID: " << s.studentID << endl;

    cout << "\n" << setw(55) << " First name: ";
    cin >> s.firstname;

    cout << "\n" << setw(55) << " Last name: ";
    cin >> s.lastname;

    cout << "\n" << setw(55) << " Age: ";
    cin >> s.age;

    cin.ignore();

    do {
        cout << "\n" << setw(55) << " Email: ";
        getline(cin,s.email);

        if (!isValidEmail(s.email)) {
            cout << "\n" << setw(65) << " Invalid Email !" << endl;
        }

    }while (!isValidEmail(s.email));

    // Check duplicate email
    for (const Student& existing : students) {
        if (existing.email == s.email) {
            cout << "\n" << setw(70) << "This email is already registered.\n";
            return;
        }
    }

    do{
        cout << "\n" << setw(55) << " Password: ";
        getline(cin,s.password);

        if (!isValidPassword(s.password)){
            cout << "\n" << setw(70) << " Password must contain: " << endl;
            cout << "\n" << setw(70) << " - Minimum 8 characters " << endl;
            cout << "\n" << setw(70) << " - Uppercase character " << endl;
            cout << "\n" << setw(70) << " - Lowercase character " << endl;
            cout << "\n" << setw(60) << " - Number" << endl;
            cout << "\n" << setw(70) << " - Special character \n\n";
        }
    }while (!isValidPassword(s.password));

    cout << "\n" << setw(55) << " Phone Number: ";
    getline(cin,s.phone);

    cout << "\n" << setw(55) << " Address: ";
    getline(cin,s.address);

    cout << "\n" << setw(55) << " Student Type (Domestic/International): ";
    getline(cin,s.type);

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

    cout << "\n" << setw(55) << " Email: ";
    getline(cin, email);

    cout << "\n" << setw(55) << " Password: ";
    getline(cin, password);

    for (Student& s : students){
        if ( s.email == email && s.password == password){

            cout << "\n+-------------------------------------------------------------------------------------------------+ \n\n";

            cout << "|                               Student Logged-In Successfully !                                  | \n\n";

            cout << "+-------------------------------------------------------------------------------------------------+ \n\n";

            coursesFlow(s, students);
            return;
        }
    }
    cout << "\n+-------------------------------------------------------------------------------------------------+ \n\n";

    cout << "|                                Invalid Email / Password !                                       | \n\n";

    cout << "+-------------------------------------------------------------------------------------------------+ \n\n";

}