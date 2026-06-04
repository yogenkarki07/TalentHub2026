
#include <iomanip>
#include<fstream>
#include<vector>

#include "Headers/filehandler.h"
using namespace std;

void SaveStudentsInfo(vector<Student>& students) {
    Student s;
    ofstream file ("students.csv");
    for (Student& s : students) {
        //file << setw(10) << s.firstname << ", " << s.lastname << ", " << s.age << ", " << s.email << ", " << s.phone << ", " << s.type << endl;
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
