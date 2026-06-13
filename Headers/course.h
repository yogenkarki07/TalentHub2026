#pragma once
#include <vector>
#include <string>

#include "student.h"

using namespace std;

struct Course{
    vector<string> availableCourses = {
        "IT Fundamentals",
        "Database Systems",
        "Cisco Networking",
        "Microsoft certification",
        "Leadership & Management",
        "English Language Studies"};
};

void CourseMenu();
// void initializeCourses(Course&);
void showCourses(const Course&);
void enrollCourse(Course& c, Student& currentStudent, vector<Student>& students, int choice);
void showMyCourses(const Student& currentStudent);
void coursesFlow(Student& currentStudent, vector<Student>& students);
