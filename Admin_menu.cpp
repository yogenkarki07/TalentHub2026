#include "Admin_menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//=================== add student ===============================//
void Addstudent() {

	std::ofstream file ("../File/students.csv", std::ios::app); //creates and appends if doesn't exist

	std::vector<Student> students;

	Student s;

	if (!file.is_open()) {
		std::cerr <<  "error cannot open file to add a student\n";
		return;
	}

	//add student
	std::cout << "Please enter your firstname: ";
	std::cin >> s.Firstname;

	std::cout << "Please enter your Lastname: ";
	std::cin >> s.Lastname;

	std::cout << "Please enter your age: ";
	std::cin >> s.age;

	std::cout << "Please enter your Email: ";
	std::cin >> s.Email;

	std::cout << "Please enter your Password: ";
	std::cin >> s.Password;

	//proper choice between domestic and international
	int residencyChoice = 0;
	do {
		std::cout << "\n====================================\n";
		std::cout << "|| Select Student Residency Type: ||\n";
		std::cout << "|| 1. Domestic                    ||\n";
		std::cout << "|| 2. International               ||\n";
		std::cout << "====================================\n";
		std::cout << "Enter choice (1-2): ";
		std::cin >> residencyChoice;

		if (residencyChoice == 1) {
			s.domistic = "Yes";
			s.international = "No";
		}
		else if (residencyChoice == 2) {
			s.domistic = "No";
			s.international = "Yes";
		}
		else {
			std::cout << "Invalid choice! Please enter 1 for Domestic or 2 for International.\n";
			// Clear input buffer in case user typed letters to prevent infinite loop
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}while (residencyChoice != 1 && residencyChoice != 2);

	// Write data to file matching your pipeline '|' layout
	int col = 15;
	file << std::left
		 << std::setw(col) << s.Firstname     << " | "
		 << std::setw(col) << s.Lastname      << " | "
		 << std::setw(col) << s.age           << " | "
		 << std::setw(col) << s.Email         << " | "
		 << std::setw(col) << s.Password      << " | "
		 << std::setw(col) << s.domistic      << " | "
		 << std::setw(col) << s.international << " | "
		 << std::setw(col) << s.courses       << " | " << std::endl;

	file.close();
	std::cout << "\nStudent successfully added to the database!\n";
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

		// Read all lines from the file
		while (std::getline(file, line)) {
			// Only keep the line if the target email is NOT found within it
			if (line.find(targetEmail) == std::string::npos) {
				lines.push_back(line);
			} else {
				found = true;
			}
		}
		file.close();

		if (found) {
			// Re-open in truncate mode to overwrite the file with the new list
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

//==================== Using database for login =================//
void login(std::vector<Admin>& admin){
	std::ifstream file("../Admin.csv");
	std::string line;

	std::getline(file, line); //skips the header row

	while(getline(file, line)){

		if (line.empty()) continue;
		std::stringstream ss (line);

		Admin a;
		std::string age;

		getline(ss, a.Firstname, '|');
		getline(ss, a.Lastname, '|');
		getline(ss, a.age, '|');
		getline(ss, a.Email, '|');
		getline(ss, a.Password, '|');

		//strip spaces and /r from each field
		auto trim = [](std::string& s)
		{
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

    std::string seperator (col * 3, '-');

     std::ofstream file ("../Admin.csv", std::ios::app); //creates file and overites it

	//checking if file has content before opening
	std::ifstream check("../Admin.csv");
	bool fileHasContent = check.peek() != std::ifstream::traits_type::eof(); //check content header
	check.close();

     if(!file.is_open())
    {
        std::cout << "Cannot create file must create file to continue \n";
         return;
    }

    std::cout << "====================================" << std::endl;
    std::cout << "||                                ||" << std::endl;
    std::cout << "||     Welcome to Admin Signup    ||" << std::endl;
    std::cout << "||                                ||" << std::endl;
    std::cout << "====================================" << std::endl;

    Admin a; // creates from vector

    std::cout << "please enter your First name: " << std::endl;
    std::cin >> a.Firstname;

    std::cout << "please enter your Last name: " << std::endl;
    std::cin >> a.Lastname;

    std::cout << "please enter your Age: " << std::endl;
    std::cin >> a.age;

    std::cout << "please enter your Email: " << std::endl;
    std::cin >> a.Email;

    std::cout << "please enter your Password: " << std::endl;
    std::cin >>a.Password;

    admin.push_back(a); // create one admin per admin

	if (!fileHasContent){

    //Header inside CSS file
    file << seperator << std::endl;
    file << std::left
		 << std::setw(col) << "Firstname" << " | "
		 << std::setw(col) << "Lastname" << " | "
		 << std::setw(col) << "Age"   << " | "
		 << std::setw(col) << "Email"     << " | "
		 << std::setw(col) << "Password"  << " | " << "\n";
    file << seperator << "\n";

	}

    //Footer inside css file
    file << std::left
		 << std::setw(col) << a.Firstname << " | "
         << std::setw(col) << a.Lastname << " | "
         << std::setw(col) << a.age << " | "
         << std::setw(col) << a.Email <<" | "
         << std::setw(col) << a.Password << " | " << std::endl;
    file << seperator << std::endl;

    file.close(); // closes file
}

//==================== Admin Sign up registration ==============================//
void admin_menu(Admin& loggedIn)
{
    int menu;
	while (menu != 3){
		std::cout << "====================================\n";
		std::cout << "||                                ||\n";
		std::cout << "||     Welcome to Admin menu      ||\n";
		std::cout << "||                                ||\n";
		std::cout << "====================================\n";
		std::cout << "||              ||               ||\n";
		std::cout << "||  1. Login    ||  2. Register  ||\n";
		std::cout << "||              ||               ||\n";
		std::cout << "||  3. Exit     ||  4. Student   ||\n";
		std::cout << "||              ||               ||\n";
		std::cout << "====================================\n";
	    std::cin >> menu;

	    switch (menu)
	    {
    		case 1: {login(admin);

    			std::string inputEmail, inputPassword;

    			std::cout << "Please enter your Email: ";
    			std::cin >> inputEmail;

    			std::cout << "Please enter your Password: ";
    			std::cin >> inputPassword;

    			Admin loggedIn;

    			bool found = false;

    			for (const Admin& a : admin) {

    				if (inputEmail == a.Email && inputPassword == a.Password) {
    					loggedIn = a;
    					found = true;
    					break;
    				}
    			}

    			if (found) {
    				std::cout << "Login successful!" << std::endl;
    				main_view();
    				admin.clear();
    				login(admin);
    			} else {
    				std::cout << "Incorrect email or password. Please Sign Up first." << std::endl;
    			}
    			break;
    			} //login into main menu
	        case 2: {signup(); break;} // registration selection
	        case 3: {std::cout << "Exiting from the program\n";  exit(0);} // exits out of menu
			case 4: {} //student menu
	    }
    }
}

void profile(){

}

//=================== Admin main menu ======================================//

void main_view(){

	int view = 0;
	while (view != 4){
		std::cout << "====================================\n";
		std::cout << "||                                ||\n";
		std::cout << "||       Admin Dashboard          ||\n";
		std::cout << "||                                ||\n";
		std::cout << "====================================\n";
		std::cout << "||             	 	||               ||\n";
		std::cout << "||  1. Delete   	 	||  2. Add       ||\n";
		std::cout << "||              	 	||               ||\n";
		std::cout << "||  3. Courses  		||  4. Sign/up   ||\n";
		std::cout << "||              		||               ||\n";
		std::cout << "||  5.StudentProfile 	||	6. Profile	 ||\n";
		std::cout << "||              		||               ||\n";
		std::cout << "====================================\n";
		std::cin >> view;

		switch (view){

			case 1: {Deletestudent(); break;};//delete student
			case 2: {Addstudent(); break;};//add student
			case 3: {break;};//view courses of students
			case 4: {Admin loggedIn;
				admin_menu(loggedIn); break;};//login/signup menu
			case 5: {	break;}
			case 6: {	break;}

		}
	}
}