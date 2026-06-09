#pragma once
#include <vector>
#include <string>
#include "student.h"

using namespace std;

struct Course
{
    vector<string> availableCourses;
    vector<string> enrolledCourses;
};

void initializeCourses(Course&);
void showCourses(const Course&);
void enrollCourse(Course& , int);
void showMyCourses(const Course& );
void coursesFlow(Student& student);
