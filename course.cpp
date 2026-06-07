#include "Headers/course.h"
#include <iostream>
#include <vector>
#include "Headers/Globals.h"

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
    cout << "current course count:" << App::currentStudentCourseCount << endl;
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

    if (c.enrolledCourses.size() >= 3)
    {
        cout << "Maximum 3 courses allowed!\n";
        return;
    }

    c.enrolledCourses.push_back(selectedCourse);

    cout << "\n========> "<< selectedCourse
         << " Enrolled successfully! <========\n\n";
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
