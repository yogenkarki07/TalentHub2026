#include "Admin_menu.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


std::string toLower(const std::string& text) {
	std::string result = text;
	for (char& c : result) {
		c = tolower(c);
	}
	return result;
}

std::vector<Student> students;
Student s;

std::vector<Admin> admin;

void course_menu(Admin& loggedIn) {
	int course;
	std::cout << "+=========================================================+\n"
				 "|                                                         |\n"
				 "|              Welcome to courses!!!                      |\n"
				 "|                                                         |\n"
				 "+=========================================================+\n"
				 "| 1. List of Student Enrollment  | 2. Remove from Courses |\n"
				 "|                                                         |\n"
				 "| 3.Student Details			   | 4. Main Menu			|\n"
				 "|                                                         |\n"
				 "+=========================================================+\n";
	std::cin >> course;

	switch (course) {
		case 1: {student_enrollment();	break;}	//list of students
	case 2:	{
				std::string courseName;
				std::cout << "Enter Student ID: ";
				std::cin >> s.studentID;
				std::cout << "Enter Course Name: ";
				std::cin >> courseName;

				Remove_courses(students, s.studentID, courseName, true);
				break;	}	//students remove from courses
		case 3:	{student_details();		break;} //show student details
		case 4: {std::cout << "+==========================================+\n"
							 "| You are returning to menu, thank you!    |\n"
							 "+==========================================+\n";
			admin_menu(loggedIn);	break;}
	}
}


//========================= Student enrollment list ====================================//
void student_enrollment() {
	std::ifstream file ("../File/students.csv");
    std::string line;

    if (!file.is_open()) {
        std::cout << "Cannot locate file\n";
        return;
    }

    std::vector<Student> students;

    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);

        Student s;
        std::string studentIDStr, ageStr;

        std::getline(ss, studentIDStr, '|');
        std::getline(ss, s.firstname,  '|');
        std::getline(ss, s.lastname,   '|');
        std::getline(ss, ageStr,       '|');
        std::getline(ss, s.email,      '|');
        std::getline(ss, s.password,   '|');
        std::getline(ss, s.phone,      '|');
        std::getline(ss, s.address,    '|');
        std::getline(ss, s.type,       '|');

        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" "));
            str.erase(str.find_last_not_of(" ") + 1);
        };

        // only trim strings, NOT s.age
        trim(studentIDStr);
        trim(s.firstname);
        trim(s.lastname);
        trim(ageStr);
        trim(s.email);
        trim(s.password);
        trim(s.phone);
        trim(s.address);
        trim(s.type);

        // then convert to int
        s.studentID = studentIDStr.empty() ? 0 : std::stoi(studentIDStr);
        s.age       = ageStr.empty()       ? 0 : std::stoi(ageStr);

        students.push_back(s);
    }

    file.close();

    std::ranges::sort(students, [](const Student& a, const Student& b) {
        return a.type < b.type;
    });

    // print domestic
    std::cout << "===========================================================\n";
    std::cout << "           DOMESTIC STUDENTS\n";
    std::cout << "============================================================\n";
    for (const auto& s : students) {
        if (s.type == "Domestic") {
            std::cout << "ID:      " << s.studentID << "\n";
            std::cout << "Name:    " << s.firstname << " " << s.lastname << "\n";
            std::cout << "Age:     " << s.age << "\n";
            std::cout << "Email:   " << s.email << "\n";
            std::cout << "Phone:   " << s.phone << "\n";
            std::cout << "========================================================\n";
        }
    }

    // print international
    std::cout << "\n========================================================\n";
    std::cout << "           INTERNATIONAL STUDENTS\n";
    std::cout << "===========================================================\n";
    for (const auto& s : students) {
        if (s.type == "International") {
            std::cout << "ID:      " << s.studentID << "\n";
            std::cout << "Name:    " << s.firstname << " " << s.lastname << "\n";
            std::cout << "Age:     " << s.age << "\n";
            std::cout << "Email:   " << s.email << "\n";
            std::cout << "Phone:   " << s.phone << "\n";
            std::cout << "==========================================================\n";
        }
    }
}


std::ostream operator<<(const std::ostream & lhs, const std::vector<std::string> & rhs);

//========================= Student details ===========================================//
void student_details() {

	std::vector<Student> students;
	Student s;

	//Name to search
	std::string query;
	std::cout << "===============================================\n"
			  <<"			Welcome to your search Menu			\n"
			  << "===============================================\n" << std::endl;
	std::cout <<"Enter the student name: " << std::endl;
	std::cin.ignore();
	std::getline(std::cin, query);

	//Open the file but not overwriting
	std::ifstream file ("../File/students.csv");

	if (!file.is_open()) {
		std::cout << "=============================\n"
				  <<"		Cannot locate file	   \n"
				  <<"===============================\n"	<< std::endl;
		return;
	}

	std::cout << "Student ID,FirstName,Lastname,Type\n";

	//skips the header row
	std::string line;
	stringstream ss(line);
	string idStr;

	std::getline(file, line);

	// Step 4: Search through every student
	bool found = false;

	while (getline(file, line)) {

		// Split the line by commas into individual fields
		std::stringstream ss(line);

		getline(ss, idStr, ',');
		std::getline(ss, s.firstname, ',');
		getline(ss, s.lastname,  ',');
		getline(ss, s.type,      ',');

		try {
			if (!idStr.empty()){
				s.studentID = stoi(idStr);
			}
		}

		catch (const invalid_argument& e){
			cout << "Debug Error: 'stoi' failed ! " << endl;
		}

		// Step 5: Check if the search query appears in first OR last name
		std::string fullName = s.firstname + " " + s.lastname;

		if (toLower(fullName).find(toLower(query)) != std::string::npos) {

			// Step 6: Print all details for this student
			std::cout << "\n=====================================\n";
			std::cout << "Student ID: " << s.studentID << "\n";
			std::cout << "First Name: " << s.firstname << "\n";
			std::cout << "Last Name : " << s.lastname  << "\n";
			std::cout << "Type      : " << s.type      << "\n";
			std::cout << "\n=====================================\n";

			found = true;
		}
	}

	file.close();

	// Step 7: If nothing was found, let the admin know
	if (!found) {
		std::cout << "\n==============================================\n"
					"\nNo student found with the name \n" << query <<
					"\n===============================================\n" << std::endl;
	}
}

//========================= Student remove from course =================================//

void Remove_courses(std::vector<Student>& students, int StudentID, const std::string& coursename, bool isAdmin) {

	std::cout << "\n+=========================================+\n"
    		  << "\n|										  |\n"
			  << "\n|		Welcome to Student Removal		  |\n"
			  << "\n|										  |\n"
			  << "\n+=========================================+\n" << std::endl;

	if (!isAdmin)
	{
		std::cout << "+==============================================+"
		          << "\n|											 |\n"
				  << "	|		Admin is Required for Student removal|"
		          << "\n|											 |\n"
				  << "+==============================================+" <<std::endl;
		return;
	}

	//============================ Find a student by ID ===================================
	for (Student& student : students)
	{
		if (student.studentID == StudentID)
		{
			//Search inside enrolled courses
			for (size_t i = 0; i < student.enrolledCourses.size(); i++)
			{
				if (student.enrolledCourses[i] == coursename)
				{
					student.enrolledCourses.erase(student.enrolledCourses.begin() + i);
					std::cout << "Removed" << student.firstname << " " << student.lastname
					<< " From " << coursename << ".\n";
					return;
				}
			}

				//Student found in course but not enrolled
				std::cout << "+===================================================+"
						  << "|													  |"
						  << "|		Student have not been found in course		  |"
					      << "|													  |"
						  << "+===================================================+" << coursename << "\n" << std::endl;
			return;
		}
	}

	//No student have been found
	std::cout << "+===================================================+"
			  << "|													  |"
			  << "|		Student Id have not been found				  |"
			  << "|													  |"
	          << "+===================================================+" << s.studentID << std::endl;

}

//=================== add student ======================================================//
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


//=================== delete student ==========================================================//
void Deletestudent() {
	std::ifstream file("../File/students.csv");
	if (!file.is_open()) {
		std::cerr << "\n=========================================\n"
				  <<"Error: Could not open database for deletion.\n"
		          << "\n=========================================\n";
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
		std::ofstream file("../File/students.csv", std::ios::trunc);
		for (const auto& l : lines) {
		file << l << "\n";
	}
		file.close();
		std::cout << "Student with email " << targetEmail << " has been deleted.\n";
	} else {
		std::cout << "\n==========================================================\n"
				  <<"			Student record not found.						 \n"
				  <<"\n===========================================================\n" << std::endl;
	}
}

//==================== Load admins from CSV ==================================================//
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


//==================== Signup ==================================================================//
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

//==================== Admin menu (login / register) ===============================================//
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
					 "||  3. Exit     ||               ||\n"
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
				    			 " 	Welcome to you application\n	" <<
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
		}
	}
}

//===================== Admin Profile =====================================================================//
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

//=================== Admin Dashboard ===================================================================//
void main_view(Admin& loggedIn) {

	int view = 0;
	while (view != 4) {
		std::cout << "==========================================\n"
				 "||                                      ||\n"
				 "||           Admin Dashboard            ||\n"
				 "||                                      ||\n"
				 "==========================================\n"
				 "||                  ||                  ||\n"
				 "||   1. Delete      ||   2. Add Student ||\n"
				 "||                  ||                  ||\n"
				 "||   3. Courses     ||   4. Log out     ||\n"
				 "||                  ||                  ||\n"
				 "||   5. Profile     ||                  ||\n"
				 "||                  ||                  ||\n"
				 "==========================================\n";
		std::cin >> view;

		switch (view) {
			case 1: { Deletestudent(); break; }
			case 2: { Addstudent(); break; }
			case 3: {course_menu(loggedIn); break; }
			case 4: {
				std::cout << "+==========================================+\n"
				             "  You are logging out. Thank you!          \n"
				             "+==========================================+\n";
				admin_menu(loggedIn);
				break;
			}
			case 5: {profile(loggedIn); break; }
		}
	}
}