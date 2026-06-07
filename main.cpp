#include <iostream>
#include "Headers/course.h"
#include "Headers/menusManager.h"

using namespace std;

void coursesFlow() {
    Course c;
    initializeCourses(c);

    int choice;

    while (true) {
        displayMainMenu();

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showCourses(c);
                break;

            case 2:
            {
                int courseChoice;

                showCourses(c);

                cout << "\nSelect course number to enroll: ";
                cin >> courseChoice;

                enrollCourse(c, courseChoice);
                break;
            }

            case 3:
                showMyCourses(c);
                break;

            case 4:
                cout << "\n===============================================================================================\n";
                cout << "|                                EXITING TALENTHUB                                            |\n";
                cout << "===============================================================================================\n\n";

              exit(0);



            default:
                cout << "Invalid choice!\n";
        }
    }
}


int main() {
          coursesFlow();

    }

