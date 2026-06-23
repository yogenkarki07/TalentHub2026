
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>

#include "Headers/Admin.h"
#include "Headers/student.h"
#include "Headers/menu.h"
#include "Headers/validation.h"
#include "Headers/filehandler.h"

using namespace std;

vector<Admin> admin;

void AddStudent() {

	ofstream file ("../File/students.csv", ios::app);

	vector<Student>students;
	LoadStudentInfo ( students);
	Student s;

	if (!file.is_open()) {
		cerr << "error cannot open 'students.csv' file.\n";
		return;
	}

	cout << "\n+===============================================+" << endl;
	cout << "|               To register Student:            |" << endl;
	cout << "|            Fill the form given below          |" << endl;
	cout << "+===============================================+" << endl <<endl;

	s.studentID = GenerateStudentID(students);
	cout << "\n" <<" Student ID: " << s.studentID << endl;

	cout << "\n" << " First Name: ";
	cin >> s.firstname;

	cout << "\n" << " Last Name: ";
	cin >> s.lastname;

	cout << "\n" << " Age: ";
	cin >> s.age;

	cin.ignore();

	do {
		cout << "\n" << " Email: ";
		getline(cin,s.email);

		if (!isValidEmail(s.email)) {
			cout << "\n" << " Invalid Email !" << endl << endl;
		}

	}while (!isValidEmail(s.email));

	do{
		cout << "\n" << " Password: ";
		getline(cin,s.password);

		if (!isValidPassword(s.password)){
			cout << "\n" << " Password must contain: " << endl;
			cout << " - Minimum 8 characters " << endl;
			cout << " - Uppercase character " << endl;
			cout << " - Lowercase character " << endl;
			cout << " - Number" << endl;
			cout << " - Special character \n\n";
		}
	}while (!isValidPassword(s.password));

	cout << "\n" << " Phone Number: ";
	getline(cin,s.phone);

	cout << "\n" << " Address: ";
	getline(cin,s.address);

	cout << "\n" << " Student Type (Domestic/International): ";
	getline(cin,s.type);

	file << s.studentID << "," << s.firstname << "," << s.lastname << "," << s.age << "," << s.email << "," << s.password << "," << s.phone << "," << s.address << "," << s.type << endl;

	file.close();

	cout << "\n+===========================================================+\n"
	        "|             New student registered Successfully.          |\n"
	        "+===========================================================+\n\n";
}

void RemoveStudentEnrollments(const string& studentID) {
	if (studentID.empty()) {
		return;
	}

	ifstream inFile("../File/enrollments.csv");

	if (!inFile.is_open()) {
		return;
	}

	vector<string> keptLines;
	string line;
	bool isHeader = true;

	while (getline(inFile, line)) {
		if (isHeader) {
			keptLines.push_back(line);
			isHeader = false;
			continue;
		}

		if (line.empty()) {
			continue;
		}

		size_t commaPos = line.find(',');
		string lineStudentID = (commaPos != string::npos) ? line.substr(0, commaPos) : line;

		if (lineStudentID != studentID) {
			keptLines.push_back(line);
		}

	}
	inFile.close();

	ofstream outFile("../File/enrollments.csv");
	for (const auto& l : keptLines) outFile << l << "\n";
	outFile.close();

}

void DeleteStudent() {

	ifstream file("../File/students.csv");

	if (!file.is_open()) {
		cerr << "Error: Could not open 'student.csv' file.\n";
		return;
	}

	vector<string> lines;
	string line, targetEmail;

	bool found = false;
	string DeletedStudentID;

	cout << "\n+===============================================+" << endl;
	cout <<   "|               To Delete Student:              |" << endl;
	cout <<   "|            Provide Student's Email.           |" << endl;
	cout <<   "+===============================================+" << endl <<endl;
	cout << "             Email: ";
	cin >> targetEmail;

	while (getline(file, line)) {
		if (line.find(targetEmail) == string::npos) {
			lines.push_back(line);
		}
		else {
			found = true;
			size_t commaPos = line.find(',');
			if (commaPos != string::npos) {
				DeletedStudentID = line.substr(0, commaPos);
			}
		}
	}

	file.close();

	if (found) {
		ofstream outFile("../File/students.csv");
		for (const auto& l : lines) {
			outFile << l << "\n";
		}
		outFile.close();

		RemoveStudentEnrollments(DeletedStudentID);

		cout << "     Student with email" << " ' " << targetEmail  << " ' " << "has been deleted along with enrolled courses.\n";
	}
	else {
		cout << "     Student record not found.\n";
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

	bool writeHeader = false;

	if (!check.good()) {
		writeHeader = true;
	}
	else {

		string firstLine;

		if (!getline(check, firstLine) || firstLine.empty()) {
			writeHeader = true;
		}
	}

	check.close();

	ofstream file("../File/Admin.csv", ios::app);

	if (!file.is_open()) {
		cout << "Cannot open file to continue.\n";
		return;
	}

	cout <<      "\n+=====================================================+\n"
	             "|                                                     |\n"
	             "|                   Admin Registration                |\n"
	             "|                                                     |\n"
	             "+=====================================================+\n\n\n";

	Admin a;

	cout << "\n" << setw(30) << " First name: ";
	cin >> a.Firstname;

	cout << "\n" << setw(30) << " Last name: ";
	cin >> a.Lastname;

	cout << "\n" << setw(30) << " Age: ";
	cin >> a.age;

	cin.ignore();

	do {
		cout << "\n" << setw(30) << "Email: ";
		getline(cin,a.Email);

		if (!isValidAdminEmail(a.Email)) {
			cout << "\n" << setw(40) << "Invalid Email !" << endl << endl;
		}

	}while (!isValidAdminEmail(a.Email));

	ranges::transform(a.Email, a.Email.begin(), ::tolower);

	do{
		cout << "\n" << setw(30) << "Password: ";
		getline(cin,a.Password);

		if (!isValidPassword(a.Password)){
			cout << "\n" << setw(30) << "Password must contain: " << endl;
			cout << "\n" << setw(30) << " - Minimum 8 characters " << endl;
			cout << "\n" << setw(30) << " - Uppercase character " << endl;
			cout << "\n" << setw(30) << " - Lowercase character " << endl;
			cout << "\n" << setw(30) << " - Number" << endl;
			cout << "\n" << setw(30) << " - Special character \n\n";
		}
	}while (!isValidPassword(a.Password));


	for (const Admin& existing : admin) {
		if (existing.Email == a.Email) {
			cout << "\n" << setw(30) << "Invalid Email! " << a.Email << " is already registered." << endl << endl;
			return;
		}
	}

	admin.push_back(a);

	if (writeHeader) {
		file << "FirstName,LastName,Age,Email,Password" << endl;
	}

	file << a.Firstname << "," << a.Lastname << "," << a.age << "," << a.Email << "," << a.Password << endl;

	file.close();

	cout << "\n" << setw(15) << "Admin registered successfully !" << " Welcome " << a.Firstname << " " << a.Lastname << " to the Talent Hub" << endl << endl;

}

void AdminMenu(Admin& loggedIn){
	int menu =0;
	 do {
		     cout << "\n+==========================================================+\n"
		             "|                                                          |\n"
		             "|                   Welcome to Admin Dashboard             |\n"
		             "|                                                          |\n"
		             "+==========================================================+\n"
		             "|                                 |                        |\n"
		             "|       1.Admin Registration      |   2.  Admin Login      |\n"
		             "|                                 |                        |\n"
		             "+==========================================================+\n\n";
		     cout << "                       Enter your choice: ";

		if (!(cin >> menu)){
			cout << "\n           Invalid input! Please enter a number: " << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (menu){
			case 1:
				AdminRegistration(admin,loggedIn);
				break;

			case 2: {
				admin.clear();
				AdminLogin( admin);

				string inputEmail, inputPassword;

				cout << "\n" << setw(25) << " Email: ";
				cin >> inputEmail;

				cout << "\n" << setw(25) << " Password: ";
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
		             "\n+==========================================================+\n"
					 "|                   Login successful!                      |\n"
					 "+==========================================================+\n\n";
					AdminDashboard(loggedIn);
					return;
				} else {
					cout <<
		                         "\n+==========================================================+\n"
								 "|              Incorrect email / password.                   |\n"
								 "+============================================================+\n\n";
					AdminMenu(loggedIn);
				}
				break;
			}

			default:
				cout << "\n" << setw(25) << "Invalid choice !" << endl;
				break;
		}
	}while (menu != 4);
}

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

	cout << "\n+=========================================================+" << endl;
	cout << "|                   Searching Student ?                    |" << endl;
	cout << "+==========================================================+" << endl <<endl;
	cout << "               Enter student's name: ";

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
			cout << "\n+==========================================================+\n";
			cout << setw(30) << "Student ID: " << s.studentID << "\n";
			cout << setw(30) << "      Name: " << s.firstname << " " << s.lastname << "\n";
			cout << setw(30) << "       Age: " << s.age << "\n";
			cout << setw(30) << "     Email: " << s.email << "\n";
			cout << setw(30) << "     Phone: " << s.phone << "\n";
			cout << "+==========================================================+\n\n";

			found = true;
		}
	}

	file.close();

	// Step 7: If nothing was found, let the admin know
	if (!found) {
		    cout << "\n+==========================================================+\n"
					"\n  No student found with the name " << "'" << query << "'\n" <<
					"\n+==========================================================+\n" << endl;
	}
}

void AdminDashboard(Admin& loggedIn) {
	int view = 0;

	while (view != 6) {
		cout << "\n+========================================================================+\n"
				"|                                                                        |\n"
				"|                               Admin Dashboard                          |\n"
				"|                                                                        |\n"
				"+========================================================================+\n"
				"|                                      |                                 |\n"
				"|      1. Add Student                  |      2. Remove Student          |\n"
				"|                                      |                                 |\n"
				"|      3. International Students       |      4. Domestic Students       |\n"
				"|                                      |                                 |\n"
				"|      5. Search Student               |      6. Exit                    |\n"
				"|                                      |                                 |\n"
				"+========================================================================+\n\n";
		cout << "                               Enter your choice: ";

		if (!(cin >> view)){
			cout << setw(60) << "\n Invalid input! Please enter a number: " << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}


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
    cout << "\n+===========================================================+\n";
    cout << "|          List of International Students                   |\n";
    cout << "+===========================================================+\n\n";
    for (const auto& s : students) {
        if (s.type == "International") {
            cout << setw(30) << "Student ID: " << s.studentID << "\n";
            cout << setw(30) << "      Name: " << s.firstname << " " << s.lastname << "\n";
            cout << setw(30) << "       Age: " << s.age << "\n";
            cout << setw(30) << "     Email: " << s.email << "\n";
            cout << setw(30) << "     Phone: " << s.phone << "\n";
            cout << "==========================================================\n\n";
        }
    }
				ostream operator<<(const ostream & lhs, const vector<string> & rhs);
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

    cout << "\n+============================================================+\n";
    cout << "|                  List of Domestic Students                 |\n";
    cout << "+============================================================+\n\n";
    bool foundDomestic = false;
    for (const auto& s : students) {
        if (s.type == "Domestic") {
            cout << setw(30) << "Student ID: "<< s.studentID << endl;
            cout << setw(30) << "      Name: " << s.firstname << " " << s.lastname << endl;
            cout << setw(30) << "       Age: " << s.age << endl;
            cout << setw(30) << "     Email: " << s.email << endl;
            cout << setw(30) << "     Phone: " << s.phone << endl;
            cout << setw(30) << "   Address: " << s.address << endl;
            cout << "+============================================================+\n\n";
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
						"\n+========================================================================+\n"
						"|                      You are logging out. Thank you!                    |\n"
				        "\n+========================================================================+\n\n";
					break;

					default:
					cout << "\n" << setw(50) << "Invalid Choice ! " << endl;
					break;
				}
		}
	}