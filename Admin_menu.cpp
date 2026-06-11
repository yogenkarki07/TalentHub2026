#include "Admin_menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<Admin> admin;

//=================== add student ===============================//
void Addstudent() {

	std::ofstream file ("../File/students.csv", std::ios::app);

	std::vector<Student> students;
	Student s;

	if (!file.is_open()) {
		std::cerr << "error cannot open file to add a student\n";
		return;
	}

	std::cout << "Please enter your firstname: ";
	std::cin >> s.firstname;

	std::cout << "Please enter your Lastname: ";
	std::cin >> s.lastname;

	std::cout << "Please enter your age: ";
	std::cin >> s.age;

	std::cout << "Please enter your Email: ";
	std::cin >> s.email;

	std::cout << "Please enter your Password: ";
	std::cin >> s.password;

	int col = 15;
	file << std::left
		 << std::setw(col) << s.firstname << " | "
		 << std::setw(col) << s.lastname  << " | "
		 << std::setw(col) << s.age       << " | "
		 << std::setw(col) << s.email     << " | "
		 << std::setw(col) << s.password  << " | " << std::endl;

	file.close();
	std::cout << "==============================================\n"
	             "  Student successfully added to the database!\n"
	             "==============================================\n" << std::endl;
}


//=================== delete student ============================//
void Deletestudent() {
	std::ifstream file("../File/students.csv");
	if (!file.is_open()) {
		std::cerr << "Error: Could not open database for deletion.\n";
		return;
	}

	std::vector<std::string> lines;
	std::string line, targetEmail;
	bool found = false;

	std::cout << "Enter the Email of the student to delete: ";
	std::cin >> targetEmail;

	while (std::getline(file, line)) {
		if (line.find(targetEmail) == std::string::npos) {
			lines.push_back(line);
		} else {
			found = true;
		}
	}
	file.close();

	if (found) {
		std::ofstream outFile("../File/students.csv", std::ios::trunc);
		for (const auto& l : lines) {
			outFile << l << "\n";
		}
		outFile.close();
		std::cout << "Student with email " << targetEmail << " has been deleted.\n";
	} else {
		std::cout << "Student record not found.\n";
	}
}

//==================== Load admins from CSV =================//
void login(std::vector<Admin>& admin){
	std::ifstream file("../Admin.csv");
	std::string line;

	std::getline(file, line); // skip header row

	while (getline(file, line)) {
		if (line.empty()) continue;
		std::stringstream ss(line);

		Admin a;

		getline(ss, a.Firstname, '|');
		getline(ss, a.Lastname,  '|');
		getline(ss, a.age,       '|');
		getline(ss, a.Email,     '|');
		getline(ss, a.Password,  '|');

		auto trim = [](std::string& s) {
			s.erase(0, s.find_first_not_of(" \r\n"));
			s.erase(s.find_last_not_of(" \r\n") + 1);
		};

		trim(a.Firstname);
		trim(a.Lastname);
		trim(a.age);
		trim(a.Email);
		trim(a.Password);

		admin.push_back(a);
	}
}


//==================== Signup ===================================//
void signup()
{
	int col = 15;
	std::string separator(col * 3, '-');

	// Check if file already has content BEFORE opening for append
	std::ifstream check("../Admin.csv");
	bool fileHasContent = check.peek() != std::ifstream::traits_type::eof();
	check.close();

	std::ofstream file("../Admin.csv", std::ios::app);
	if (!file.is_open()) {
		std::cout << "Cannot open file to continue.\n";
		return;
	}

	std::cout << "====================================\n"
	             "||                                ||\n"
	             "||     Welcome to Admin Signup    ||\n"
	             "||                                ||\n"
	             "====================================\n";

	Admin a;

	std::cout << "Please enter your First name: ";
	std::cin >> a.Firstname;

	std::cout << "Please enter your Last name: ";
	std::cin >> a.Lastname;

	std::cout << "Please enter your Age: ";
	std::cin >> a.age;

	std::cout << "Please enter your Email: ";
	std::cin >> a.Email;

	std::cout << "Please enter your Password: ";
	std::cin >> a.Password;

	admin.push_back(a);

	if (!fileHasContent) {
		file << separator << "\n";
		file << std::left
			 << std::setw(col) << "Firstname" << " | "
			 << std::setw(col) << "Lastname"  << " | "
			 << std::setw(col) << "Age"       << " | "
			 << std::setw(col) << "Email"     << " | "
			 << std::setw(col) << "Password"  << " | \n";
		file << separator << "\n";
	}

	file << std::left
		 << std::setw(col) << a.Firstname << " | "
		 << std::setw(col) << a.Lastname  << " | "
		 << std::setw(col) << a.age       << " | "
		 << std::setw(col) << a.Email     << " | "
		 << std::setw(col) << a.Password  << " | \n";
	file << separator << "\n";

	file.close();
}

//==================== Admin menu (login / register) ==============================//
void admin_menu(Admin& loggedIn)
{
	int menu = 0;
	while (menu != 3) {
		std::cout << "====================================\n"
		             "||                                ||\n"
		             "||     Welcome to Admin menu      ||\n"
		             "||                                ||\n"
		             "====================================\n"
		             "||              ||               ||\n"
		             "||  1. Login    ||  2. Register  ||\n"
		             "||              ||               ||\n"
		             "||  3. Exit     ||  4. Student   ||\n"
		             "||              ||               ||\n"
		             "====================================\n";
		std::cin >> menu;

		switch (menu)
		{
			case 1: {
				admin.clear();
				login(admin);

				std::string inputEmail, inputPassword;
				std::cout << "Please enter your Email: ";
				std::cin >> inputEmail;

				std::cout << "Please enter your Password: ";
				std::cin >> inputPassword;

				bool found = false;

				for (const Admin& a : admin) {
					if (inputEmail == a.Email && inputPassword == a.Password) {
						loggedIn = a;
						found = true;
						break;
					}
				}

				if (found) {
					std::cout << "+========================================+\n"
					             "          Login successful!              \n"
					             "+========================================+\n";
					main_view(loggedIn);
				} else {
					std::cout << "+====================================================+\n"
					             "  Incorrect email or password. Please Sign Up first. \n"
					             "+====================================================+\n";
				}
				break;
			}
			case 2: { signup(); break; }
			case 3: {
				std::cout << "+========================================+\n"
				             "       Exiting from the program!         \n"
				             "+========================================+\n";
				exit(0);
			}
			case 4: { break; }
		}
	}
}

//===================== Admin Profile ========================================//
void profile(Admin& a) {
	std::cout << "+===================================================+\n"
	             "           Welcome to your profile                  \n"
	             "+===================================================+\n";

	std::cout << "Your Firstname: " << a.Firstname << "\n";
	std::cout << "Your Lastname:  " << a.Lastname  << "\n";
	std::cout << "Your Age:       " << a.age       << "\n";
	std::cout << "Your Email:     " << a.Email     << "\n";
	std::cout << "Your Password:  " << a.Password  << "\n";

	std::cout << "+===================================================+\n";
}

//=================== Admin Dashboard ======================================//
void main_view(Admin& loggedIn) {

	int view = 0;
	while (view != 4) {
		std::cout << "==========================================\n"
		             "||                                      ||\n"
		             "||           Admin Dashboard            ||\n"
		             "||                                      ||\n"
		             "==========================================\n"
		             "||                  ||                  ||\n"
		             "||   1. Delete      ||   2. Add         ||\n"
		             "||                  ||                  ||\n"
		             "||   3. Courses     ||   4. logging out ||\n"
		             "||                  ||                  ||\n"
		             "||   5. Student     ||   6. Profile     ||\n"
		             "||      Profile     ||                  ||\n"
		             "||                  ||                  ||\n"
		             "==========================================\n";
		std::cin >> view;

		switch (view) {
			case 1: { Deletestudent(); break; }
			case 2: { Addstudent(); break; }
			case 3: { break; }
			case 4: {
				std::cout << "+==========================================+\n"
				             "  You are logging out. Thank you!          \n"
				             "+==========================================+\n";
				admin_menu(loggedIn);
				break;
			}
			case 5: { break; }
			case 6: { profile(loggedIn); break; }
		}
	}
}