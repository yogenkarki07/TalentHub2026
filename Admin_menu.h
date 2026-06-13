#ifndef ADMIN2_0_ADMIN_MENU_H
#define ADMIN2_0_ADMIN_MENU_H
#include <string>
#include <vector>

struct Admin
{
    std::string Firstname;
    std::string Lastname;
    std::string age;
    std::string Email;
    std::string Password;
};

extern std::vector<Admin> admin;

void admin_menu(Admin& loggedIn);
void main_view(Admin& loggedIn);
void login(std::vector<Admin>& admin);
void signup();
void profile(Admin& a);
void course_menu(Admin& loggedin);
void student_enrollment();
void Remove_courses();
void student_courses();
void student_details();

#endif //ADMIN2_0_ADMIN_MENU_H