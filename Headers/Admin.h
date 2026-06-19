
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

void AdminMenu(Admin& loggedIn);

void AdminDashboard(Admin& loggedIn);

void AdminLogin(vector<Admin>& admin);

void AdminRegistration(vector<Admin>& admin, Admin& loggedIn);

void AdminProfile(Admin& a);

void SearchStudent();

void AddStudent();

void DeleteStudent();