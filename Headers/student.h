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
};

void StudentRegistration(vector<Student>& students);

void StudentLogin(vector<Student>& students);

void StudentDashboard(vector<Student>& students);
