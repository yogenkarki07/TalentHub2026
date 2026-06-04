
#include <iomanip>
#include<fstream>
#include<vector>

#include "Headers/filehandler.h"
using namespace std;

void SaveStudentInfo(vector<Student>& students) {
    Student s;
    ofstream file ("../File/students.csv", ios ::app);
    if (!file.is_open()){
        cout << "\n[ERROR] Could not save data! 'students.csv' could not be opened.\n";
        return;
    }

    for ( Student s : students) {

        file << s.firstname << ", " << s.lastname << ", " << s.age << ", " << s.email << ", " << s.password << ", " << s.phone << ", " << s.type << endl;

    }
    file.close();
}
