#ifndef ADMIN2_0_UNIVERSAL_H
#define ADMIN2_0_UNIVERSAL_H
#include <iostream>
#include <vector>

//=================================================================================================//
//====================================== Student Login and Registration ==========================//
//===============================================================================================//
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

//=============================================================//
//=========================== Menu ===========================//
//===========================================================//
void DisplayMenu();

//=============================================================//
//========================== Verification ====================//
//===========================================================//
bool isValidPassword(string& password);

bool isValidEmail(string& email);

bool isEmailExist(string& email);

//=================================================================//
//============================= File Handling ====================//
//===============================================================//
void SaveStudentInfo (vector<Student>& students);

void LoadStudentInfo (vector<Student>& students);

void SaveCourseEnrollments (vector<Student>& students);

void LoadCourseEnrollments (vector<Student>& students);

#include "course.h"
#endif //ADMIN2_0_UNIVERSAL_H