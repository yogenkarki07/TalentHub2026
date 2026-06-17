#include<fstream>
#include<vector>
#include<sstream>
#include <iomanip>

#include "Headers/Universal.h"

using namespace std;

// Store data after registration
void SaveStudentInfo(vector<Student>& students) {
    ofstream file ("../File/students.csv");

    if (!file.is_open()){
        cout << "+============================================+"
             <<" |      students.csv could not be opened.     |"
             << "+============================================+" << endl;
        return;
    }

    file << left
         << setw(20) << "StudentID" << " | "
         << setw(20) << "FirstName" << " | "
         << setw(20) << "LastName"  << " | "
         << setw(20) << "Age" << " | "
         << setw(20) << "Email" << " | "
         << setw(20) << "Password" << " | "
         << setw(20) << "Phone" << "|"
         << setw(20) << "Address" << " | "
         << setw(20) << "Type" << " | " << endl;

    for (Student s: students) {
        file << left << setw(20) <<  s.studentID << " | " << s.firstname << " | " << s.lastname << " | " << s.age << " | "
        << s.email << " | " << s.password << " | " << s.phone << " | " << s.address << " | "  << s.type << endl;
    }

    file.close();
}

// Load the stored data to Log-in
void LoadStudentInfo(vector<Student>& students) {
    students.clear();

    ifstream file ("../File/students.csv");
    if (!file) {
        return;
    }

    string line;

    getline(file, line);  //To skip the header line from the csv file

    while (getline(file, line)){

    if (line.empty()){
        continue;
    }

    Student s;

    stringstream ss(line);
    string ageStr;
    string idStr;

    getline(ss, idStr, '|');
    getline(ss, s.firstname, '|');
    getline(ss, s.lastname, '|');
    getline(ss, ageStr, '|');
    getline(ss, s.email, '|');
    getline(ss, s.password, '|');
    getline(ss, s.phone, '|');
    getline(ss, s.address, '|');
    getline(ss, s.type, '|');

    if (s.firstname.empty() || s.lastname.empty()) continue;

    try {
        if (!ageStr.empty()){
            s.age = stoi(ageStr);
        }
        if (!idStr.empty()){
            s.studentID = stoi(idStr);
        }
    }

    catch (const invalid_argument& e){
            cout << "+==================================+"
                    "| Debug Error: 'stoi' failed !     |"
                    "+==================================+"<< endl;
            s.age = 0;
            s.studentID = 0;
    }

    catch (const out_of_range& e){
        cout << "+===========================================+"
                "|  Debug Error: Value out of range for int. |"
                "+===========================================+"   << endl;
        s.studentID = 0;
        s.age = 0;
    }
         students.push_back(s);
     }

    file.close();
}

void SaveCourseEnrollments( vector<Student>& students) {
    ofstream file ("../File/enrollments.csv");

    if (!file. is_open()) {
        cout << " 'enrollments.csv' file cannot be opened. " << endl;
        return;
    }

    file << "Student ID,Course" << endl;

    for ( Student& s: students) {
        for ( string& course : s.enrolledCourses) {
            cout << s.studentID << "," << course << endl;
        }
    }

    file.close();
}

void LoadCourseEnrollments (vector<Student>& students) {
    ifstream file ("../File/enrollments.csv");

    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);         //to skip the header line

    while ( getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
        string idStr;
        string course;

        getline(ss, idStr, ',');
        getline( ss, course );

        int StudentID = stoi (idStr);

        for (Student s : students) {
            if (s.studentID == StudentID) {
                s.enrolledCourses.push_back(course);
                break;
            }
        }

    }

    file.close();

}