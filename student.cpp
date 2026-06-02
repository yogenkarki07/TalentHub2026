#include <iostream>
#include <vector>

#include "Headers/student.h"
#include "Headers/validation.h"

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

    cout << "-------------------------------------------------------------- \n\n";

    cout << "|                  Student Registered successfully !           | \n\n";

    cout << "---------------------------------------------------------------\n\n";

}

void StudentLogin(vector<Student>& students) {
    Student s;
    string email, password;

    cout << "+==============================================================+\n";
    cout << "|                                                              |\n";
    cout << "|                      Student Login                           |\n";
    cout << "|                                                              |\n";
    cout << "+==============================================================+\n\n";

    cin.ignore();

    cout << "                   Email: ";
    getline(cin,s.email);

    cout << "                   Password: ";
    getline(cin,s.password);

    students.push_back(s);

    for (Student& s, students){
        if (s.email == email && s.password == password)
        {
            cout << "--------------------------------------------------------------\n\n";

            cout << "|              Student log-in successfully !               |\n\n";

            cout << "--------------------------------------------------------------\n\n";
        }
        else
        {
             cout << "\n            Invalid login credentials!\n";        }
        }


}