
#include <iomanip>
#include<fstream>
#include<vector>

#include "Headers/filehandler.h"
using namespace std;

// Save and store data after registration
void SaveStudentInfo(vector<Student>& students) {
    Student s;
    ofstream file ("../File/students.csv", ios ::app);
    if (!file.is_open()){
        cout << "\nError! Could not save data! 'students.csv' could not be opened.\n";
        return;
    }

    for ( Student s : students) {

        file << s.firstname << ", " << s.lastname << ", " << s.age << ", " << s.email << ", " << s.password << ", " << s.phone << ", " << s.type << endl;

    }
    file.close();
}

// Load the stored data to Log-in
void LoadStudentInfo(vector<Student>& students) {
    Student s;
    ifstream file ("../File/students.csv", ios ::in);
    if (!file.is_open()) {
        cout << "File does not exist." << endl;
    }

    for (Student s : students) {

    }
}