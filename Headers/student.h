#pragma once
#include <iostream>
#include <vector>
using namespace std;

 struct Student{
    int studentID{};
    string firstname;
    string lastname;
    int age{};
    string email;
    string password;
    string phone;
    string address;
    string type;

    vector<string> enrolledCourses;
 };

void StudentRegistration(vector<Student>& students);

void StudentLogin(vector<Student>& students);
