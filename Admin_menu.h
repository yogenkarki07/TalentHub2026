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

inline std::vector<Admin> admin;

void admin_menu(Admin& loggedIn);

void main_view();

void login(std::vector<Admin>& admin);

void signup();

void main_view();

#endif //ADMIN2_0_ADMIN_MENU_H