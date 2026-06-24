#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>

#include "Headers/Globals.h"
#include "Headers/course.h"
#include "Headers/filehandler.h"
#include "Headers/menu.h"

using namespace std;

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

void showCourses(Course& c){
    cout << "\n+==============================================================================================+ \n";
    cout << "|                                   ALL AVAILABLE COURSES                                      | \n";
    cout << "+==============================================================================================+ \n\n";

    for (int i = 0; i < c.availableCourses.size(); i++){
        cout << setw(35) << i + 1 << "." << c.availableCourses[i] << endl << endl;
    }
    cout << "+==============================================================================================+ \n\n";
}

void enrollCourse(Course& c, Student& currentStudent, vector<Student>& students, int choice){
    cout << setw(55) << "Current Course Count: " << App::currentStudentCourseCount << endl << endl;

    if (choice < 1 || choice > c.availableCourses.size()){
        cout << setw(55) << "\nInvalid choice!\n\n";
        return;
    }

    string selectedCourse = c.availableCourses[choice - 1];

    for (auto course : currentStudent.enrolledCourses){
        if (course == selectedCourse){
            cout << setw(65) << "You have already enrolled in this course!" << endl << endl;
            return;
        }
    }

    if (App::currentStudentCourseCount >= 3){
        cout << setw(55) << "Maximum 3 courses allowed!" << endl << endl;
        return;
    }

    currentStudent.enrolledCourses.push_back(selectedCourse);
    SaveCourseEnrollments( students);
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
        cout << setw(35) << i + 1 << "." << currentStudent.enrolledCourses[i] << endl << endl;
    }
}

void coursesFlow(Student& currentStudent, vector<Student>& students){
    Course c;
    int choice;

    do {
        CourseMenu();
        if (!(cin >> choice)){
            cout << setw(70) << "\n Invalid input! Please enter a number: " << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                showCourses(c);
                break;

            case 2:{
                int enrolledCount = currentStudent.enrolledCourses.size();
                int remainingCourses = 3 - enrolledCount;

                cout << "\n+================================================================================================+\n\n";
                cout << setw(60) << " Courses Enrolled : " << enrolledCount << endl << endl;
                cout << setw(60) << " Courses Remaining to choose: " << remainingCourses << endl << endl;
                cout << "+================================================================================================+\n\n";

                if (enrolledCount >= 3){
                    cout << setw(65) << "Maximum only 3 courses allowed to enroll." << endl << endl;
                    break;
                }

                int courseChoice;

                showCourses(c);

                cout << setw(65) << "Select course number to enroll: ";

                if (!(cin >> courseChoice)){
                    cout << setw(50) << "\nInvalid input! Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                enrollCourse( c, currentStudent, students, courseChoice);
                break;
            }

            case 3:
                showMyCourses(currentStudent);
                break;

            case 4:
                cout << "\n+===============================================================================================+\n";
                cout << "|                                                                                               |\n";
                cout << "|                           You are logging out. Thank you!                                     |\n";
                cout << "|                                                                                               |\n";
                cout << "+===============================================================================================+\n\n";
                break;

            default:
                cout << setw(50) << "\nInvalid choice ! " << endl;
                break;
        }
    } while (choice != 4);
}




