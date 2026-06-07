#include<fstream>
#include<vector>
#include<sstream>

#include "Headers/filehandler.h"
using namespace std;

// Store data after registration
void SaveStudentInfo(vector<Student>& students) {
    Student s;
    ofstream file ("../File/students.csv", ios ::trunc);

    if (!file.is_open()){
        cout << " 'students.csv' could not be opened. " << endl;
        return;
    }
    for (Student s: students) {
        file << s.firstname << "," << s.lastname << "," << s.age << "," << s.email << "," << s.password << "," << s.phone << "," << s.address << ","  << s.type << endl;
    }


    file.close();
}

// Load the stored data to Log-in
void LoadStudentInfo(vector<Student>& students) {
    students.clear();
    Student s;

    ifstream file ("../File/students.csv");
    if (!file) {
        cout << " 'students.csv' file could not be opened." << endl;
        return;
    }

    string line;
    getline(file, line);

     while (getline(file, line)) {
         Student s;

    if (line.empty()){
        continue;
    }

    stringstream ss(line);
    string ageStr;

    getline(ss, s.firstname, ',');
    getline(ss, s.lastname, ',');
    getline(ss, ageStr, ',');
    getline(ss, s.email, ',');
    getline(ss, s.password, ',');
    getline(ss, s.phone, ',');
         getline(ss, s.address, ',');
    getline(ss, s.type, ',');

    try {
        if (!ageStr.empty()) {
        s.age = stoi(ageStr);
        }
        else{
            s.age = 0;
        }
    }
    catch (invalid_argument& e){
            cout << "Debug Error: 'stoi' failed! " << endl;s.age = 0;
    }

         students.push_back(s);
     }
    file.close();
}