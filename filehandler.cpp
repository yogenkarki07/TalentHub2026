
#include <iomanip>
#include<fstream>
#include<vector>

#include "Headers/filehandler.h"
using namespace std;

void SaveStudentInfo(vector<Student>& students) {
    Student s;
    ofstream file ("students.csv");
    if (!file.is_open()){
        cout << "\n[ERROR] Could not save data! 'students.csv' could not be opened.\n";
        cout << "Please ensure the file is closed in Excel/Notepad and try again.\n\n";
        return;
    }

    for ( Student s : students) {
        //file << setw(10) << s.firstname << ", " << s.lastname << ", " << s.age << ", " << s.email << ", " << s.password << ", " << s.phone << ", " << s.type << endl;
         file << s.lastname << endl;
         file << s.firstname << endl;
         file << s.age << endl;
         file << s.email << endl;
         file << s.password << endl;
         file << s.phone << endl;
         file << s.type << endl;
    }
    file.close();
}
