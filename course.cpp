#include "Headers/course.h"
#include <iostream>
#include <limits>
#include <vector>
#include "Headers/Globals.h"
#include "Headers/menusManager.h"
#include "Headers/student.h"

using namespace std;

void initializeCourses(Course& c)
{

    c.availableCourses = {
        "IT Fundamentals",
        "Database Systems",
        "Cisco Networking",
        "Microsoft certification",
        "Leadership & Management",
        "English Language Studies"
    };
}

void showCourses(const Course& c)
{
    cout << "\n==============================================================================================\n";
    cout << "|                                  ALL AVAILABLE COURSES                                     |\n";
    cout << "==============================================================================================\n\n";

    for (int i = 0; i < c.availableCourses.size(); i++)
    {
        cout << i + 1 << ". " << c.availableCourses[i] << endl;
    }
    cout << "\n";
}

void enrollCourse(Course& c, int choice)
{
    cout << "current course count: "
    << App::currentStudentCourseCount
    << endl;
    if (choice < 1 || choice > c.availableCourses.size())
    {
        cout << "Invalid choice!\n";
        return;
    }

    string selectedCourse = c.availableCourses[choice - 1];

    for (string course : c.enrolledCourses)
    {
        if (course == selectedCourse)
        {
            cout << "You have already enrolled in this course!\n\n";
            return;
        }
    }

    if (App::currentStudentCourseCount >= 3)
    {
        cout << "Maximum 3 courses allowed!\n";
        return;
    }

    c.enrolledCourses.push_back(selectedCourse);

    App::currentStudentCourseCount++;

    cout << "\n========> "<< selectedCourse
         << " Enrolled successfully! <========\n\n";

    cout << "Courses Enrolled : "
     << App::currentStudentCourseCount
     << "/3\n\n";
}

void showMyCourses(const Course& c)
{
    cout << "\n==============================================================================================\n";
    cout << "|                              MY CURRENT COURSES                                            |\n";
    cout << "==============================================================================================\n\n";

    if (c.enrolledCourses.empty())
    {
        cout << "\n========> No courses enrolled yet <========.\n\n";
        return;
    }

    for (int i = 0; i < c.enrolledCourses.size(); i++)
    {
        cout << i + 1 << ". " << c.enrolledCourses[i] << endl;
    }
}


void coursesFlow(Student& student) {
    Course c;


    initializeCourses(c);

    int choice;

    while (true) {
        displayMainMenu();

        cout << "\nEnter choice: ";
        if (!(cin >> choice))
        {
            cout << "Invalid input! Please enter a number: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                showCourses(c);
                break;

            case 2:
            {
                int enrolledCount = c.enrolledCourses.size();
                int remainingCourses = 3 - enrolledCount;

                cout << "\n==============================================================================================\n";
                cout << "| Courses Enrolled : " << enrolledCount << "                                                                        |"<<endl;
                cout << "| Courses Remaining to choose: " << remainingCourses << "                                                                        |"<< endl;
                cout << "==============================================================================================\n\n";

                if (enrolledCount >= 3)
                {
                    cout << "Maximum 3 courses allowed!\n\n";
                    break;
                }

                int courseChoice;

                showCourses(c);

                cout << "\nSelect course number to enroll: ";

                if (!(cin >> courseChoice))
                {
                    cout << "\nInvalid input! Please enter a number.\n";

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                enrollCourse(c, courseChoice);
                break;
            }


            case 3:

                StudentDetails(student);
                showMyCourses(c);
                break;

            case 4:
                cout << "\n===============================================================================================\n";
                cout << "|                                EXITING TALENTHUB                                            |\n";
                cout << "===============================================================================================\n\n";

                return;



            default:
                cout << "Invalid choice!\n";
        }
    }
}


