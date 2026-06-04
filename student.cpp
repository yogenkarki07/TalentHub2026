#include <iostream>
#include <vector>

#include "Headers/student.h"
#include "Headers/validation.h"
#include "Headers/filehandler.h"

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

    cout << "---------------------------------------------------------------- \n\n";

    cout << "|                      Registration successfull.               | \n\n";

    cout << "---------------------------------------------------------------- \n\n";

}

void StudentLogin(vector<Student>& students) {
    Student s;

    cout << "+==============================================================+\n";
    cout << "|                                                              |\n";
    cout << "|                      Student Login successfull.              |\n";
    cout << "|                                                              |\n";
    cout << "+==============================================================+\n\n";

    cin.ignore();

    cout << "                   Email: ";
    getline(cin,s.email);

    cout << "                   Password: ";
    getline(cin,s.password);

    for (Student& s : students) {
        string password, email;
        if ( s.email == email && s.password == password){
            cout << "--------------------------------------------------------------\n\n";

            cout << "|               log-in successfull.                     |\n\n";

            cout << "--------------------------------------------------------------\n\n";
        }
        else {
            cout << "\n            Invalid login credentials!\n";

        }
    }

}