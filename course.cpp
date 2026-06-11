#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>

#include "Headers/Globals.h"
#include "Headers/course.h"
#include "Headers/filehandler.h"

using namespace std;

void initializeCourses(Course& c){
    c.availableCourses = {
        "IT Fundamentals",
        "Database Systems",
        "Cisco Networking",
        "Microsoft certification",
        "Leadership & Management",
        "English Language Studies"
    };
}

void CourseMenu() {
    cout << "+===============================================================================================+\n";
    cout << "|                                                                                               |\n";
    cout << "|                                   COURSE MENU                                                 |\n";
    cout << "|                                                                                               |\n";
    cout << "+===============================================================================================+\n";

    cout << "_______________________________________________________________________________________________\n";
    cout << "|                                           |                                                  |\n";
    cout << "|    1. Show All Available Courses          |     2. Enroll in Additional Courses              |\n";
    cout << "|                                           |                                                  |\n";
    cout << "_______________________________________________________________________________________________\n";
    cout << "______________________________________________________________________________________________\n";
    cout << "|                                           |                                                  |\n";
    cout << "|    3. Show Enrolled Courses               |     4. Exit                                      |\n";
    cout << "|                                           |                                                  |\n";
    cout << "_______________________________________________________________________________________________\n\n";
    cout << "                                   Enter your choice : ";

}

void showCourses(const Course& c){
    cout << "+==============================================================================================+ \n";
    cout << "|                                   ALL AVAILABLE COURSES                                      | \n";
    cout << "+==============================================================================================+ \n";

    for (int i = 0; i < c.availableCourses.size(); i++){
        cout << setw(35) << i + 1 << "." << c.availableCourses[i] << endl << endl;
    }
}

void enrollCourse(Course& c, int choice,Student& currentStudent, vector<Student>& students){
    cout << setw(55) << "Current Course Count: " << App::currentStudentCourseCount << endl << endl;

    if (choice < 1 || choice > c.availableCourses.size()){
        cout << setw(55) << "Invalid choice!\n";
        return;
    }

    string selectedCourse = c.availableCourses[choice - 1];

    for (auto course : c.enrolledCourses){
        if (course == selectedCourse){
            cout << setw(65) << "You have already enrolled in this course!" << endl;
            return;
        }
    }

    if (App::currentStudentCourseCount >= 3){
        cout << setw(55) << "Maximum 3 courses allowed!" << endl;
        return;
    }

    currentStudent.enrolledCourses.push_back(selectedCourse);
    SaveCourseEnrollments(students);
    App::currentStudentCourseCount++;

    cout << "         =================>  Successfully Enrolled in " << selectedCourse << ". <================== \n\n";

    cout << setw(55) << "Enrolled Courses: " << App::currentStudentCourseCount << "\n\n";
}

void showMyCourses(const Student& currentStudent){
    cout << "+===============================================================================================+\n";
    cout << "|                                                                                               |\n";
    cout << "|                              MY CURRENT COURSES                                               |\n";
    cout << "|                                                                                               |\n";
    cout << "+===============================================================================================+\n\n";

    if (currentStudent.enrolledCourses.empty()){
        cout << "        ====================> Not enrolled in any course yet <===================== \n\n";
        return;
    }

    for (int i = 0; i < currentStudent.enrolledCourses.size(); i++){
        cout << setw(35) << i + 1 << "." << currentStudent.enrolledCourses[i] << endl;
    }
}

void coursesFlow(int currentStudent, vector<Student>& students){
    Course c;
    initializeCourses(c);
    int choice;
    do {
        CourseMenu();
        if (!(cin >> choice)){
            cout << "Invalid input! Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                showCourses(currentStudent);
                break;

            case 2:
            {
                int enrolledCount = currentStudent.enrolledCourses.size();
                int remainingCourses = 3 - enrolledCount;

                cout << "+================================================================================================+\n";
                cout << setw(60) << " Courses Enrolled : " << enrolledCount << endl;
                cout << setw(60) << " Courses Remaining to choose: " << remainingCourses << endl;
                cout << "+================================================================================================+\n\n";

                if (enrolledCount >= 3){
                    cout << setw(65) << "Maximum only 3 courses allowed to enroll." << endl;
                    break;
                }

                int courseChoice;

                showCourses(c);

                cout << setw(65) << "Select course number to enroll: ";

                if (!(cin >> courseChoice)){
                    cout << setw(50) << "Invalid input! Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                enrollCourse(c, currentStudent, courseChoice, students);
                break;
            }

            case 3:
                showMyCourses(c);
                break;

            case 4:
                CourseMenu();
                break;

            default:
                cout << setw(50) << "Invalid choice ! " << endl;
                break;
        }
    } while (choice != 4);
}




