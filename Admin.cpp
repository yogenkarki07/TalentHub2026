
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "Headers/Admin.h"
#include "Headers/student.h"
#include "Headers/menu.h"
#include "Headers/validation.h"

using namespace std;

vector<Admin> admin;

void AddStudent() {

	ofstream file ("../File/students.csv", ios::app);

	vector<Student>students;
	Student s;

	if (!file.is_open()) {
		cerr << "error cannot open 'students.csv' file.\n";
		return;
	}

	cout << "Enter Student ID: ";
	cin >> s.studentID;

	cout << "Enter First Name: ";
	cin >> s.firstname;

	cout << "Enter Last Name: ";
	cin >> s.lastname;

	cout << "Enter Age: ";
	cin >> s.age;

	cin.ignore();

	do {
		cout << "Email: ";
		getline(cin,s.email);

		if (!isValidEmail(s.email)) {
			cout << "Invalid Email !" << endl;
		}

	}while (!isValidEmail(s.email));

	do{
		cout << "Password: ";
		getline(cin,s.password);

		if (!isValidPassword(s.password)){
			cout << " Password must contain: " << endl;
			cout << " - Minimum 8 characters " << endl;
			cout << " - Uppercase character " << endl;
			cout << " - Lowercase character " << endl;
			cout << " - Number" << endl;
			cout << " - Special character \n\n";
		}
	}while (!isValidPassword(s.password));

	cout << "Phone Number: ";
	getline(cin,s.phone);

	cout << "Address: ";
	getline(cin,s.address);

	cout << "Student Type (Domestic/International): ";
	getline(cin,s.type);

	// file << "StudentID,FirstName,LastName,Age,Email,Password,Phone,Address,Type" << endl;

	file << s.studentID << "," << s.firstname << "," << s.lastname << "," << s.age << "," << s.email << "," << s.password << "," << s.phone << "," << s.address << "," << s.type << endl;

	file.close();

	cout << "+===========================================================+\n"
	        "|   Successfully added student to the 'students.cvs file'.  |\n"
	        "+===========================================================+\n";
}


//=================== delete student ============================//
void DeleteStudent() {

	ifstream file("../File/students.csv");

	if (!file.is_open()) {
		cerr << "Error: Could not open 'student.csv' file.\n";
		return;
	}

	vector<string> lines;
	string line, targetEmail;

	bool found = false;

	cout << "+===============================================+" << endl;
	cout << "|               Remove Student                  |" << endl;
	cout << "+===============================================+" << endl;
	cout << "Enter student's email: ";
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
		ofstream outFile("../File/students.csv");
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
		if (line.empty())
			continue;

		stringstream ss(line);

		Admin a;

		getline(ss, a.Firstname, ',');
		getline(ss, a.Lastname,  ',');
		getline(ss, a.age, ',');
		getline(ss, a.Email,',');
		getline(ss, a.Password);

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

void AdminRegistration(vector<Admin>& admin, Admin& loggedIn){

	ifstream check("../File/Admin.csv");

	bool fileHasContent = false;

	if (check.is_open()) {
		check.seekg(0, ios::end);

		if (check.tellg() > 0) {
			fileHasContent = true;
		}

		check.close();
	}

	ofstream file("../File/Admin.csv", ios::app);

	if (!file.is_open()) {
		cout << "Cannot open file to continue.\n";
		return;
	}

	cout <<      "+=====================================================+\n"
	             "|                                                     |\n"
	             "|                   Admin Registration                |\n"
	             "|                                                     |\n"
	             "+=====================================================+\n\n\n";

	Admin a;

	cout << setw(30) << "Enter First name: ";
	cin >> a.Firstname;

	cout << setw(30) << "Enter Last name: ";
	cin >> a.Lastname;

	cout << setw(30) << "Enter Age: ";
	cin >> a.age;

	cout << setw(30) << "Enter Email: ";
	cin >> a.Email;

	do {
		cout << "Email: ";
		getline(cin,a.Email);

		if (!isValidEmail(a.Email)) {
			cout << "Invalid Email !" << endl;
		}

	}while (!isValidEmail(a.Email));

	do{
		cout << setw(30) << "Password: ";
		getline(cin,a.Password);

		if (!isValidPassword(a.Password)){
			cout << "Password must contain: " << endl;
			cout << " - Minimum 8 characters " << endl;
			cout << " - Uppercase character " << endl;
			cout << " - Lowercase character " << endl;
			cout << " - Number" << endl;
			cout << " - Special character \n\n";
		}
	}while (!isValidPassword(a.Password));

	cout << setw(30) << "Enter Password: ";
	cin >> a.Password;

	admin.push_back(a);

	if (!fileHasContent) {
		file << "FirstName,LastName,Age,Email,Password" << endl;
	}

	file << a.Firstname << "," << a.Lastname << "," << a.age << "," << a.Email << "," << a.Password << endl;

	file.close();

	cout << "Admin registered successfully !" << " Welcome " << a.Firstname << " " << a.Lastname << " to the Talent Hub" << endl << endl;

}

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
		     cout << "                       Enter your choice: ";
		     cin >> menu;

		switch (menu){
			case 1:
				AdminRegistration(admin,loggedIn);
				break;

			case 2: {
				admin.clear();
				AdminLogin( admin);

				string inputEmail, inputPassword;

				cout << setw(25) << "Enter Email: ";
				cin >> inputEmail;

				cout << setw(25) << "Enter Password: ";
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
				cout << "Invalid choice !" << endl;
				break;
		}
	}
}

// void AdminProfile(Admin& a) {
// 	cout <<      "+===================================================+\n"
// 	             "|           Welcome to Admin profile                 |\n"
// 	             "+===================================================+\n\n\n";
//
// 	cout << setw(25) << " Firstname: " << a.Firstname << "\n";
// 	cout << setw(25) << " Lastname:  " << a.Lastname  << "\n";
// 	cout << setw(25) << " Age:       " << a.age       << "\n";
// 	cout << setw(25) << " Email:     " << a.Email     << "\n";
// 	cout << setw(25) << " Password:  " << a.Password  << "\n\n";
//
// 	cout << "+===================================================+\n";
// }

string toLower(const string& text) {
	string result = text;
	for (char& c : result) {
		c = tolower(c);
	}
	return result;
}


void SearchStudent() {
	vector<Student> students;
	Student s;

	string query;

	cout << "+===============================================+" << endl;
	cout << "|               Searching Student ?             |" << endl;
	cout << "+===============================================+" << endl;
	cout << " Enter student's name: ";

	cin.ignore();
	getline(cin, query);

	ifstream file ("../File/students.csv");

	if (!file.is_open()) {
		cout << "Cannot open 'students.csv' file. " << endl;
		return;
	}

	string line;
	getline(file, line); 	//skips the header row

	auto trim = [](string& str) {
		str.erase(0, str.find_first_not_of(" \r\n"));
		str.erase(str.find_last_not_of(" \r\n") + 1);
	};

	// Search through every student
	bool found = false;

	while (getline(file, line)) {

		// Split the line by commas into individual fields
		stringstream ss(line);
		Student s;
		string idStr, ageStr;

		getline(ss, idStr,        ',');
		getline(ss, s.firstname,  ',');
		getline(ss, s.lastname,   ',');
		getline(ss, ageStr,       ',');
		getline(ss, s.email,      ',');
		getline(ss, s.password,   ',');
		getline(ss, s.phone,      ',');
		getline(ss, s.address,    ',');
		getline(ss, s.type);

		trim(idStr); trim(s.firstname); trim(s.lastname); trim(ageStr);
		trim(s.email); trim(s.password); trim(s.phone); trim(s.address); trim(s.type);

		try {
			s.studentID = idStr.empty() ? 0 : stoi(idStr);
			s.age       = ageStr.empty() ? 0 : stoi(ageStr);
		}
		catch (const invalid_argument& e){
			cout << "Debug Error: 'stoi' failed ! " << endl;
			continue;
		}

		// Check if the search query appears in first OR last name
		string fullName = s.firstname + " " + s.lastname;

		if (toLower(fullName).find(toLower(query)) != string::npos) {

			// Step 6: Print searched student details
			cout << "+=====================================+\n";
			cout << "Student ID: " << s.studentID << endl;
			cout << "Name: " << s.firstname << " " << s.lastname  << endl;
			cout << "Email: " << s.email << endl;
			cout << "Address: " << s.address << endl;
			cout << "Type: " << s.type << endl;
			cout << "+=====================================+\n";

			found = true;
		}
	}

	file.close();

	// Step 7: If nothing was found, let the admin know
	if (!found) {
		    cout << "\n==============================================\n"
					"\nNo student found with the name " << query <<
					"\n===============================================\n" << endl;
	}
}

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
				"|      3. International Students       |      4. Domestic Students      |\n"
				"|                                      |                                |\n"
				"|      5. Search Student               |      6. Exit                   |\n"
				"|                                      |                                |\n"
				"+=======================================================================+\n";
		cout << "                               Enter your choice: ";
		cin >> view;

		switch (view) {
			case 1:
				AddStudent();
				break;

			case 2:
				DeleteStudent();
				break;

			case 3: {
				ifstream file ("../File/students.csv");
                string line;

                 if (!file.is_open()) {
                    cout << "Cannot locate file\n";
                 	break;
                 }
				vector<Student> students;

				getline(file, line); // skip header

				while (getline(file, line)) {
					if (line.empty())
						continue;

				stringstream ss(line);
					Student s;
					string IDStr, ageStr;

        getline(ss, IDStr,',');
        getline(ss, s.firstname,',');
        getline(ss, s.lastname,',');
        getline(ss, ageStr,',');
        getline(ss, s.email,',');
        getline(ss, s.password,',');
        getline(ss, s.phone,',');
        getline(ss, s.address,',');
        getline(ss, s.type);

      auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" \r\n"));
            str.erase(str.find_last_not_of(" \r\n") + 1);
        };

        trim(IDStr);
        trim(s.firstname);
        trim(s.lastname);
        trim(ageStr);
        trim(s.email);
        trim(s.password);
        trim(s.phone);
        trim(s.address);
        trim(s.type);


        // then convert to int
        s.studentID = IDStr.empty() ? 0 : stoi(IDStr);
        s.age       = ageStr.empty()       ? 0 : stoi(ageStr);

        students.push_back(s);
    }

    file.close();

    ranges::sort(students, [](const Student& a, const Student& b) {
        return a.type < b.type;
    });

    // print international
    std::cout << "+===========================================================+\n";
    std::cout << "|          List of International Students                  |\n";
    std::cout << "+===========================================================+\n";
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
				ostream operator<<(const ostream & lhs, const vector<std::string> & rhs);
}
				break;

			case 4: {
    ifstream file ("../File/students.csv");
    string line;

    if (!file.is_open()) {
        cout << "Cannot locate file\n";
        break;
    }

    vector<Student> students;  // this was previously declared but never filled in!

    getline(file, line); // skip header

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        Student s;
        string IDStr, ageStr;

        getline(ss, IDStr,',');
        getline(ss, s.firstname,',');
        getline(ss, s.lastname,',');
        getline(ss, ageStr,',');
        getline(ss, s.email,',');
        getline(ss, s.password,',');
        getline(ss, s.phone,',');
        getline(ss, s.address,',');
        getline(ss, s.type);

        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" \r\n"));
            str.erase(str.find_last_not_of(" \r\n") + 1);
        };

        trim(IDStr);
        trim(s.firstname);
        trim(s.lastname);
        trim(ageStr);
        trim(s.email);
        trim(s.password);
        trim(s.phone);
        trim(s.address);
        trim(s.type);

        s.studentID = IDStr.empty() ? 0 : stoi(IDStr);
        s.age       = ageStr.empty() ? 0 : stoi(ageStr);

        students.push_back(s);
    }

    file.close();

    cout << "+============================================================+\n";
    cout << "|                  List of Domestic Students                 |\n";
    cout << "+============================================================+\n";
    bool foundDomestic = false;
    for (const auto& s : students) {
        if (s.type == "Domestic") {
            cout << "============================================================\n";
            cout << "Student ID: "<< s.studentID << endl;
            cout << "Name:    " << s.firstname << " " << s.lastname << endl;
            cout << "Age:     " << s.age << endl;
            cout << "Email:   " << s.email << endl;
            cout << "Phone:   " << s.phone << endl;
            cout << "Address: " << s.address << endl;
            cout << "============================================================\n";
            foundDomestic = true;
        }
    }
    if (!foundDomestic) {
        cout << "No domestic students found.\n";
    }
}
				break;

					case 5:
				    SearchStudent();
					break;

					case 6:
					cout <<
						"+==========================================+\n"
						"|      You are logging out. Thank you!     |\n"
						"+==========================================+\n";
					DisplayMenu();
					break;

					default:
					cout << "Invalid Choice ! " << endl;
					break;
				}
		}
	}