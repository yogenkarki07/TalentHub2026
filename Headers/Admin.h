#ifndef ADMIN2_0_ADMIN_MENU_H
#define ADMIN2_0_ADMIN_MENU_H
#pragma once

#include <string>
#include <vector>

using namespace std;

struct Admin{
    string Firstname;
    string Lastname;
    string age;
    string Email;
    string Password;
};

extern vector<Admin> admin;

void AdminMenu(Admin& loggedIn);

void AdminDashboard(Admin& loggedIn);

void AdminLogin(vector<Admin>& admin);

void AdminRegistration(vector<Admin>& admin);

void AdminProfile(Admin& a);

#endif //ADMIN2_0_ADMIN_MENU_H