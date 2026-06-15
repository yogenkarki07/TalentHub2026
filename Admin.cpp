
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Headers/Admin.h"
#include "Headers/student.h"
#include "Headers/menu.h"
#include "Headers/course.h"

using namespace std;

vector<Admin> admin;

void AddStudent() {

	ofstream file ("../File/students.csv", ios::app);

	vector<Student>students;
	Student s;

	if (!file.is_open()) {
		cerr << "error cannot open file to add a student\n";
		return;
	}

	cout << "Please enter your firstname: ";
	cin >> s.firstname;

	cout << "Please enter your Lastname: ";
	cin >> s.lastname;

	cout << "Please enter your age: ";
	cin >> s.age;

	cout << "Please enter your Email: ";
	cin >> s.email;

	cout << "Please enter your Password: ";
	cin >> s.password;

	int col = 15;
	file << s.firstname << "," << s.lastname << "," << s.age << "," << s.email << "," << s.password << endl;

	file.close();

	cout << "+===========================================================+\n"
	        "|   Successfully added student to the 'students.cvs file'.  |\n"
	        "+===========================================================+\n";
}


//=================== delete student ============================//
void DeleteStudent() {
	ifstream file("../File/students.csv");

	if (!file.is_open()) {
		cerr << "Error: Could not open database for deletion.\n";
		return;
	}

	vector<string> lines;
	string line, targetEmail;

	bool found = false;

	cout << "Enter the Email of the student to delete: ";
	cin >> targetEmail;

	while (getline(file, line)) {
		if (line.find(targetEmail) == string::npos) {
			lines.push_back(line);
		}
		else {
			found = true;
		}
	}

	file.close();

	if (found) {
		ofstream outFile("../File/students.csv", ios::trunc);
		for (const auto& l : lines) {
			outFile << l << "\n";
		}
		outFile.close();

		cout << "Student with email " << targetEmail << " has been deleted.\n";
	}
	else {
		cout << "Student record not found.\n";
	}
}

void AdminLogin(vector<Admin>& admin){
	ifstream file("../File/Admin.csv");
	string line;

	getline(file, line); // skip header row

	while (getline(file, line)) {
		if (line.empty()) continue;
		stringstream ss(line);

		Admin a;

		getline(ss, a.Firstname, ',');
		getline(ss, a.Lastname,  ',');
		getline(ss, a.age, ',');
		getline(ss, a.Email,',');
		getline(ss, a.Password,',');

		auto trim = [](std::string& s){
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
void AdminRegistration(vector<Admin>& admin){
	int col = 15;
	string separator(col * 3, '-');

	// Check if file already has content BEFORE opening for append
	ifstream check("../File/Admin.csv");
	bool fileHasContent = check.peek() != ifstream::traits_type::eof();
	check.close();

	ofstream file("../File/Admin.csv", ios::app);
	if (!file.is_open()) {
		cout << "Cannot open file to continue.\n";
		return;
	}

	cout <<      "+=====================================================+\n"
	             "|                                                     |\n"
	             "|                   Admin Registration                |\n"
	             "|                                                     |\n"
	             "+=====================================================+\n";

	Admin a;

	cout << "Please enter your First name: ";
	cin >> a.Firstname;

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
		file << "Firstname,Lastname,Age,Email,Password" << endl;
		file << separator << "\n";
	}

	file << a.Firstname << "," << a.Lastname << "," << a.age << "," << a.Email << "," << a.Password ;
	file << separator << "\n";

	file.close();
}

// Admin menu (login / register)
void AdminMenu(Admin& loggedIn){
	int menu =0;
	while (menu != 4) {
		     cout << "+==========================================================+\n"
		             "|                                                          |\n"
		             "|                   Welcome to Admin Dashboard             |\n"
		             "|                                                          |\n"
		             "+==========================================================+\n"
		             "|                                 |                        |\n"
		             "|       1.Admin Registration      |   2.  Admin Login      |\n"
		             "|                                 |                        |\n"
		             "+==========================================================+\n\n";
		     cout << "                         Enter your choice: ";
		     cin >> menu;

		switch (menu){
			case 1:
				AdminRegistration(admin);
				break;

			case 2: {
				admin.clear();
				AdminLogin( admin);

				string inputEmail, inputPassword;

				cout << "Please enter your Email: ";
				cin >> inputEmail;

				cout << "Please enter your Password: ";
				cin >> inputPassword;

				bool found = false;

				for (const Admin& a : admin) {
					if (inputEmail == a.Email && inputPassword == a.Password) {
						loggedIn = a;
						found = true;
						break;
					}
				}

				if (found) {
					cout <<
						"+====================================================+\n"
						"|                   Login successful!                |\n"
						"+====================================================+\n";
					AdminDashboard(loggedIn);
				} else {
					cout <<
								 "+====================================================+\n"
								 "|              Incorrect email / password.           |\n"
								 "+====================================================+\n";
				}
				break;
			}

			default:
				break;
		}
	}
}

//===================== Admin Profile ========================================//
void AdminProfile(Admin& a) {
	cout <<      "+===================================================+\n"
	             "|           Welcome to Admin profile                 |\n"
	             "+===================================================+\n";

	cout << "Your Firstname: " << a.Firstname << "\n";
	cout << "Your Lastname:  " << a.Lastname  << "\n";
	cout << "Your Age:       " << a.age       << "\n";
	cout << "Your Email:     " << a.Email     << "\n";
	cout << "Your Password:  " << a.Password  << "\n";

	cout << "+===================================================+\n";
}

//=================== Admin Dashboard ======================================//
void AdminDashboard(Admin& loggedIn) {

	int view = 0;
	while (view != 6) {
		     cout << "+========================================================================+\n"
		             "|                                                                        |\n"
		             "|                               Admin Dashboard                          |\n"
		             "|                                                                        |\n"
		             "+=======================================================================+\n"
		             "|                                      |                                |\n"
		             "|      1. Add Student                  |      2. Remove Student         |\n"
		             "|                                      |                                |\n"
		             "|      3. Student Profile              |      4. Admin Profile          |\n"
		             "|                                      |                                |\n"
		             "|      5. Courses                      |      6. logging out            |\n"
		             "|                                      |                                |\n"
		             "+=======================================================================+\n";
		cin >> view;

		switch (view) {
			case 1:
				AddStudent();
				break;

			case 2:
				DeleteStudent();
				break;

			case 3:
				break;

			case 4:
				AdminProfile(loggedIn);
				break;

			case 5:
				//  showCourses(c);
				// showCourses(Course& c);
				break;

			case 6:
				cout <<
                    "+==========================================+\n"
                    "|      You are logging out. Thank you!     |\n"
				    "+==========================================+\n";
				DisplayMenu();
				break;

			Default:
				cout << "Invalid Choice ! "<< endl;
				break;
			}
		}
	}