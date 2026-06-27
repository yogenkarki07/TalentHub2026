
#pragma once

#include <string>
#include <vector>
#include "student.h"

using namespace std;

struct Admin{
    string Firstname;
    string Lastname;
    string age{};
    string Email;
    string Password;
};

extern vector<Admin> admin;

void AdminMenu(Admin& loggedIn, vector<Student>& students);

void AdminDashboard(Admin& loggedIn, vector<Student>& students);

void AdminLogin(vector<Admin>& admin);

void AdminRegistration(vector<Admin>& admin, Admin& loggedIn);

void AdminProfile();

void SearchStudent();

void AddStudent(vector<Student>& students);

void DeleteStudent();

 void RemoveStudentEnrollments(const string& studentID);