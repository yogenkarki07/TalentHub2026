#pragma once
#include <vector>
#include <string>

using namespace std;

struct Course
{
    vector<string> availableCourses;
    vector<string> enrolledCourses;
};

void initializeCourses(Course& c);
void showCourses(const Course& c);
void enrollCourse(Course& c, int choice);
void showMyCourses(const Course& c);
