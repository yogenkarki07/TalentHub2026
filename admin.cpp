#include "Headers/student.h"
#include "Headers/admin.h"

#include <iostream>
#include <vector>

using namespace  std;

void AdminLogin(vector<Student>& students) {
    string email;
    cin.ignore();

    cout << "Enter Admin's Email : " ;
    getline(cin,email);

    if (email == "kevindowd@talenthub.com") {
        cout << "Admin logged-in successfully !" << endl;
        AdminDashboard(students);
    }
    else {
        cout << "Invalid Email. Access denied !" << endl;
    }
}

void AdminDashboard(vector<Student>& students) {
    cout << "+================================================================+" << endl;
    cout << "|                                                                |" << endl;
    cout << "|                      Admin Dashboard                           |" << endl;
    cout << "|                                                                |" << endl;
    cout << "+================================================================+" << endl << endl;

    cout << "+================================================================+" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   1. Search Student       |    2. Remove Student               |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   3. Domestic Students    |    4. International Students       |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|                        5. Exit                                 |" << endl;
    cout << "|                                                                |" << endl;
    cout << "+================================================================+" << endl;



}

