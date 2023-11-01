#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<cctype>
using namespace std;

//Add
void Add(string, string, char*, int, int);
const int size_1 = 60;
char courseName[size_1], bcourseName[size_1];
int numStudent, bnumStudent;
int date, bdate;
string zoom, bzoom;
string slot, bslot;
bool reserved = false;
ofstream outFile;

//Date Validation
void dateValidation(int&);
int juneWeekend[4] = { 20,21,27,29 }; // 15-30
int julyWeekend[8] = { 4,5,11,12,18,19,25,26 }; // 1-31
int augWeekend[10] = { 1,2,8,9,15,16,22,23,29,30 }; // 1-30
int septWeekend[6] = { 5,6,12,13,19,20 }; // 1-20
int day;
bool weekend, year, outOfRange;

//Search
void Search();
ifstream inFile;

//Store
void Store(string, string, char*, int, int);

//Check
void Check(bool&, string, string, char*, int, int);
void Reserved(bool&, string, int);

//Update
void updateDetails(int, string, string);
void update(string, string, char*, int, int);

//Delete
void deleteSlot();
ofstream temp;

//Global Var
bool valid = false;
int t;
int n;
int select;

struct menu {
	string line1, line2, line3, line4, line5, line6, line7;
};
menu menuStart = { "","\nWelcome to Zoom booking services!\n" ,"There are two Zoom accounts available: Zoom A and Zoom B.\n" ,
"Only two time slots, 11am ~ 1pm and 2pm ~ 4pm are available from Monday until Friday.\n" ,
"The booking is just available for June trimester starting from 15 June 2020 to 20 September 2020.\n"
"Zoom A can fit in maximum 500 students per session while Zoom B is limited to 250 students per session.\n" ,
"Zoom A is used when Zoom B is not available or the class is having more than 250 students.\n" };

int main(void) {
	do {
		n = 0;
		reserved = false;
		valid = false;
		cout << menuStart.line1 << menuStart.line2 << menuStart.line3
			<< menuStart.line4 << menuStart.line5 << menuStart.line6 << menuStart.line7;
		cout << "\nPlease select a services:\n[1] Book a slot\n[2] Search for booking details\n" <<
			"[3] Update a booked course details(coursename / number of student).\n[4] Delete a booked slot.\n[5] Exit\n> ";
		do {
			if (cin >> select)
				if (select > 0 && select < 6)
					valid = true;
				else
					cout << "\nPlease select from above list: ";
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nIt is not an integer!\nPlease select again: ";
			}
		} while (!valid);
		valid = false;
		cin.ignore();

		if (select == 1) {
			Add(zoom, slot, courseName, numStudent, date);
			system("pause");
			system("CLS");
		}
		else if (select == 2) {
			Search();
			system("pause");
			system("CLS");
		}
		else if (select == 3) {
			// enter date, slot and zoom;
			cout << "\nPlease insert the detals of a slot you wish to update." << endl;
			dateValidation(date);
			cout << "\nSelect a Zoom slot:\n[1] Zoom A\n[2] Zoom B\n> ";
			do {
				if (cin >> select)
					if (select > 0 && select < 3)
						valid = true;
					else
						cout << "\nPlease select from above list: ";
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\nIt is not an integer!\nPlease select again: ";
				}
			} while (!valid);
			valid = false;
			cin.ignore();
			if (select == 1)
				zoom = "Zoom A";
			else
				zoom = "Zoom B";
			cout << "\nSelect a time slot:\n[1] 11am-1pm\n[2] 2pm-4pm\n> ";
			do {
				if (cin >> select)
					if (select > 0 && select < 3)
						valid = true;
					else
						cout << "\nPlease select from above list: ";
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\nIt is not an integer!\nPlease select again: ";
				}
			} while (!valid);
			valid = false;
			cin.ignore();
			if (select == 1)
				slot = "11am-1pm";
			else
				slot = "2pm-4pm";
			updateDetails(date, zoom, slot);

		}
		else if (select == 4) {
			deleteSlot();
		}

	} while (select != 5);
	cout << "\nThanks!" << endl;

	std::system("pause");
	return 0;
}

//================================================================================================
// Function Add;
void Add(string zoom, string slot, char courseName[size_1], int numStudent, int date) {
	cout << "\nInsert course name: ";
	cin.getline(courseName, size_1);
	for (t = 0; t < size_1; t++) {
		courseName[t] = toupper(courseName[t]);
	}
	cout << "\nInsert number of students: ";
	do {
		if (cin >> numStudent)
			if (numStudent > 0 && numStudent < 501)
				valid = true;
			else
				cout << "\nThe number of students are out of range!\nPlease insert again: ";
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nIt is not an integer!\nPlease insert again: ";
		}
	} while (!valid);
	valid = false;
	cin.ignore();

	dateValidation(date); // Add- dateValidation;

	if (numStudent > 250) {
		cout << "\n(Total number of students more than 250)\nZoom A selected!" << endl;
		zoom = "Zoom A";

		cout << "\nSelect a time slot:\n[1] 11am-1pm\n[2] 2pm-4pm\n> ";
		do {
			if (cin >> select)
				if (select > 0 && select < 3)
					valid = true;
				else
					cout << "\nPlease select from above list: ";
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nIt is not an integer!\nPlease select again: ";
			}
		} while (!valid);
		valid = false;
		cin.ignore();

		if (select == 1) {
			slot = "11am-1pm";
			Check(reserved, zoom, slot, courseName, numStudent, date);
			if (!reserved)
				Store(zoom, slot, courseName, numStudent, date);
		}
		else {
			slot = "2pm-4pm";
			Check(reserved, zoom, slot, courseName, numStudent, date);
			if (!reserved)
				Store(zoom, slot, courseName, numStudent, date);
		}
	}
	else {
		// Zoom A is used when Zoom B is under reserved!
		Reserved(reserved, zoom, date);

		if (reserved == true) {
			reserved = false;
			cout << "\n(Total number of students less or equal to 250)\n(Zoom B is under reserved!)\nZoom A selected!";
			zoom = "Zoom A";

			cout << "\nSelect a time slot:\n[1] 11am-1pm\n[2] 2pm-4pm\n> ";
			do {
				if (cin >> select)
					if (select > 0 && select < 3)
						valid = true;
					else
						cout << "\nPlease select from above list: ";
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\nIt is not an integer!\nPlease select again: ";
				}
			} while (!valid);
			valid = false;
			cin.ignore();

			if (select == 1) {
				slot = "11am-1pm";
				Check(reserved, zoom, slot, courseName, numStudent, date);
				if (!reserved)
					Store(zoom, slot, courseName, numStudent, date);
			}
			else {
				slot = "2pm-4pm";
				Check(reserved, zoom, slot, courseName, numStudent, date);
				if (!reserved)
					Store(zoom, slot, courseName, numStudent, date);
			}
		}
		else {
			cout << "\n(Total number of students less or equal to 250)\nSelect a Zoom slot:\n[1] Zoom A\n[2] Zoom B\n> ";
			do {
				if (cin >> select)
					if (select > 0 && select < 3)
						valid = true;
					else
						cout << "\nPlease select from above list: ";
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\nIt is not an integer!\nPlease select again: ";
				}
			} while (!valid);
			valid = false;
			cin.ignore();

			if (select == 1) {
				zoom = "Zoom A";

				cout << "\nSelect a time slot:\n[1] 11am-1pm\n[2] 2pm-4pm\n> ";
				do {
					if (cin >> select)
						if (select > 0 && select < 3)
							valid = true;
						else
							cout << "\nPlease select from above list: ";
					else {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "\nIt is not an integer!\nPlease select again: ";
					}
				} while (!valid);
				valid = false;
				cin.ignore();

				if (select == 1) {
					slot = "11am-1pm";
					Check(reserved, zoom, slot, courseName, numStudent, date);
					if (!reserved)
						Store(zoom, slot, courseName, numStudent, date);
				}
				else {
					slot = "2pm-4pm";
					Check(reserved, zoom, slot, courseName, numStudent, date);
					if (!reserved)
						Store(zoom, slot, courseName, numStudent, date);
				}
			}
			else {
				zoom = "Zoom B";

				cout << "\nSelect a time slot:\n[1] 11am-1pm\n[2] 2pm-4pm\n> ";
				do {
					if (cin >> select)
						if (select > 0 && select < 3)
							valid = true;
						else
							cout << "\nPlease select from above list: ";
					else {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "\nIt is not an integer!\nPlease select again: ";
					}
				} while (!valid);
				valid = false;
				cin.ignore();

				if (select == 1) {
					slot = "11am-1pm";
					Check(reserved, zoom, slot, courseName, numStudent, date);
					if (!reserved)
						Store(zoom, slot, courseName, numStudent, date);

				}
				else {
					slot = "2pm-4pm";
					Check(reserved, zoom, slot, courseName, numStudent, date);
					if (!reserved)
						Store(zoom, slot, courseName, numStudent, date);
				}
			}
		}
	}
	cout << "---------------------------------------------------------------------------------------------------\n";
}
//
// Add- dateValidation;
void dateValidation(int& date) {
	cout << "\nInsert a date ( DDMMYYYY ) > ( 15062020 )\n( DD = Day, MM = Month, YYYY = Year )\n> ";
	do {
		weekend = false;
		year = false;
		outOfRange = false;

		do {
			if (cin >> date)
				valid = true;
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nIt is not an integer!\nPlease insert again: ";
			}
		} while (!valid);
		valid = false;
		cin.ignore();

		day = date / 1000000;
		if (date >= 10000000) {
			if (date % 10000 != 2020)
				year = true;
			if (date / 10000 % 100 == 6) {
				for (t = 0; t < 4; t++) {
					if (day < 15 || day > 30)
						outOfRange = true;
					if (day == juneWeekend[t])
						weekend = true;
				}
			}
			else if (date / 10000 % 100 == 7) {
				for (t = 0; t < 8; t++) {
					if (day < 1 || day > 31)
						outOfRange = true;
					if (day == julyWeekend[t])
						weekend = true;
				}
			}
			else if (date / 10000 % 100 == 8) {
				for (t = 0; t < 10; t++) {
					if (day < 1 || day > 31)
						outOfRange = true;
					if (day == augWeekend[t])
						weekend = true;
				}
			}
			else if (date / 10000 % 100 == 9) {
				for (t = 0; t < 6; t++) {
					if (day < 1 || day > 20)
						outOfRange = true;
					if (day == septWeekend[t])
						weekend = true;
				}
			}
			else
				outOfRange = true;
		}
		else {
			if (date % 10000 != 2020)
				year = true;
			if (date / 10000 % 10 == 6) {
				for (t = 0; t < 4; t++) {
					if (day < 15 || day > 30)
						outOfRange = true;
					if (day == juneWeekend[t])
						weekend = true;
				}
			}
			else if (date / 10000 % 10 == 7) {
				for (t = 0; t < 8; t++) {
					if (day < 1 || day > 31)
						outOfRange = true;
					if (day == julyWeekend[t])
						weekend = true;
				}
			}
			else if (date / 10000 % 10 == 8) {
				for (t = 0; t < 10; t++) {
					if (day < 1 || day > 31)
						outOfRange = true;
					if (day == augWeekend[t])
						weekend = true;
				}
			}
			else if (date / 10000 % 10 == 9) {
				for (t = 0; t < 6; t++) {
					if (day < 1 || day > 20)
						outOfRange = true;
					if (day == septWeekend[t])
						weekend = true;
				}
			}
			else
				outOfRange = true;
		}
		if (year == true)
			cout << "\nIt is not 2020!\nPlease insert again: ";
		else if (weekend == true)
			cout << "\nIt is weekend!\nPlease insert again: ";
		else if (outOfRange == true)
			cout << "\nThe date is out of range!\nPlease insert again: ";

	} while ((weekend || year || outOfRange) == true);
}
//
// Add- Check reserved or not for Update/Keep;
void Check(bool& reserved, string zoom, string slot, char courseName[size_1], int numStudent, int date) {
	inFile.open("booking.txt");
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, bzoom);
			getline(inFile, bslot);
			inFile.getline(bcourseName, size_1);
			inFile >> bnumStudent;
			inFile >> bdate;
			inFile.ignore();
			if (bzoom == "")
				break;

			if (date == bdate) {
				if (zoom == bzoom || slot == bslot) {
					reserved = true;
					cout << "\nReserved Detail  No. " << n + 1 << endl;
					cout << "Zoom               : " << bzoom << endl;
					cout << "Slot               : " << bslot << endl;
					cout << "Coursename         : " << bcourseName << endl;
					cout << "Number of Student  : " << bnumStudent << endl;
					cout << "Date               : " << bdate << endl;
					n++;
				}
			}
		}
		inFile.close();
		if (reserved) {
			cout << "\nThe slot had booked by the above details." << endl;
			cout << "\nPlease select an option to continue:\n[1] Update\n[2] Keep\n> ";
			do {
				if (cin >> select)
					if (select > 0 && select < 3)
						valid = true;
					else
						cout << "\nPlease select from above list: ";
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\nIt is not an integer!\nPlease select again: ";
				}
			} while (!valid);
			if (select == 1) {
				cout << endl;
				update(zoom, slot, courseName, numStudent, date);
			}
			else {
				cout << "\nKeep successfully!\n";
			}
		}
	}
}
//
// Add- Store the information into booking.txt;
void Store(string zoom, string slot, char courseName[size_1], int numStudent, int date) {
	outFile.open("booking.txt", ios::app);
	outFile << zoom << endl;
	outFile << slot << endl;
	outFile << courseName << endl;
	outFile << numStudent << endl;
	outFile << date << endl;
	outFile.close();
	cout << "\nBook successfully!\n";
}
//
// Add- Check either Zoom B had be booked or not;
void Reserved(bool& reserved, string zoom, int date) {
	inFile.open("booking.txt");
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, bzoom);
			getline(inFile, bslot);
			inFile.getline(bcourseName, size_1);
			inFile >> bnumStudent;
			inFile >> bdate;
			inFile.ignore();
			if (bzoom == "")
				break;

			if (date == bdate) {
				if (bzoom == "Zoom B")
					reserved = true;
			}
		}
		inFile.close();
	}
}
//================================================================================================
// Function Search;
void Search() {
	t = 0;
	cout << "\nSearch by:\n[1] Zoom slot\n[2] Time slot\n[3] Course name\n[4] Date\n> ";
	do {
		if (cin >> select)
			if (select > 0 && select < 5)
				valid = true;
			else
				cout << "\nPlease select from above list: ";
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nIt is not an integer!\nPlease select again: ";
		}
	} while (!valid);
	valid = false;
	cin.ignore();

	if (select == 1) {
		cout << "\nSelect a Zoom slot:\n[1] Zoom A\n[2] Zoom B\n> ";
		do {
			if (cin >> select)
				if (select > 0 && select < 3)
					valid = true;
				else
					cout << "\nPlease select from above list: ";
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nIt is not an integer!\nPlease select again: ";
			}
		} while (!valid);
		valid = false;
		cin.ignore();
		cout << endl;

		if (select == 1)
			zoom = "Zoom A";
		else
			zoom = "Zoom B";

		inFile.open("booking.txt");
		if (inFile.is_open()) {
			while (!inFile.eof()) {
				getline(inFile, bzoom);
				getline(inFile, bslot);
				inFile.getline(bcourseName, size_1);
				inFile >> bnumStudent;
				inFile >> bdate;
				inFile.ignore();
				if (bzoom == "")
					break;

				if (zoom == bzoom) {
					cout << "\nReserved Detail  No. " << n + 1 << endl;
					cout << "Zoom               : " << bzoom << endl;
					cout << "Slot               : " << bslot << endl;
					cout << "Coursename         : " << bcourseName << endl;
					cout << "Number of Student  : " << bnumStudent << endl;
					cout << "Date               : " << bdate << endl;
					n++;
					reserved = true;
				}
			}
			inFile.close();
			if (reserved)
				cout << "Above are the booked details!" << endl;
			else
				cout << "No booked details!" << endl;
			reserved = false;
		}
		else
			cout << "\nUnable to open file!" << endl;
	}
	else if (select == 2) {
		cout << "\nSelect a time slot:\n[1] 11am-1pm\n[2] 2pm-4pm\n> ";
		do {
			if (cin >> select)
				if (select > 0 && select < 3)
					valid = true;
				else
					cout << "\nPlease select from above list: ";
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nIt is not an integer!\nPlease select again: ";
			}
		} while (!valid);
		valid = false;
		cin.ignore();
		cout << endl;

		if (select == 1)
			slot = "11am-1pm";
		else
			slot = "2pm-4pm";

		inFile.open("booking.txt");
		if (inFile.is_open()) {
			while (!inFile.eof()) {
				getline(inFile, bzoom);
				getline(inFile, bslot);
				inFile.getline(bcourseName, size_1);
				inFile >> bnumStudent;
				inFile >> bdate;
				inFile.ignore();
				if (bzoom == "")
					break;

				if (slot == bslot) {
					cout << "\nReserved Detail  No. " << n + 1 << endl;
					cout << "Zoom               : " << bzoom << endl;
					cout << "Slot               : " << bslot << endl;
					cout << "Coursename         : " << bcourseName << endl;
					cout << "Number of Student  : " << bnumStudent << endl;
					cout << "Date               : " << bdate << endl;
					n++;
					reserved = true;
				}
			}
			inFile.close();
			if (reserved)
				cout << "Above are the booked details!" << endl;
			else
				cout << "No booked details!" << endl;
			reserved = false;
		}
		else
			cout << "\nUnable to open file!" << endl;
	}
	else if (select == 3) {
		cout << "\nInsert course name: ";
		cin.getline(courseName, size_1);
		for (t = 0; t < size_1; t++) {
			courseName[t] = toupper(courseName[t]);
		}
		inFile.open("booking.txt");
		if (inFile.is_open()) {
			while (!inFile.eof()) {
				getline(inFile, bzoom);
				getline(inFile, bslot);
				inFile.getline(bcourseName, size_1);
				inFile >> bnumStudent;
				inFile >> bdate;
				inFile.ignore();
				if (bzoom == "")
					break;

				if (strcmp(courseName, bcourseName) == 0) {
					cout << "\nReserved Detail  No. " << n + 1 << endl;
					cout << "Zoom               : " << bzoom << endl;
					cout << "Slot               : " << bslot << endl;
					cout << "Coursename         : " << bcourseName << endl;
					cout << "Number of Student  : " << bnumStudent << endl;
					cout << "Date               : " << bdate << endl;
					n++;
					reserved = true;
				}
			}
			inFile.close();
			if (reserved)
				cout << "\nAbove are the booked details!" << endl;
			else
				cout << "\nNo booked details!" << endl;
			reserved = false;
		}
		else
			cout << "\nUnable to open file!" << endl;
	}
	else if (select == 4) {
		dateValidation(date);
		cout << endl;

		inFile.open("booking.txt");
		if (inFile.is_open()) {
			while (!inFile.eof()) {
				getline(inFile, bzoom);
				getline(inFile, bslot);
				inFile.getline(bcourseName, size_1);
				inFile >> bnumStudent;
				inFile >> bdate;
				inFile.ignore();
				if (bzoom == "")
					break;

				if (date == bdate) {
					cout << "\nReserved Detail  No. " << n + 1 << endl;
					cout << "Zoom               : " << bzoom << endl;
					cout << "Slot               : " << bslot << endl;
					cout << "Coursename         : " << bcourseName << endl;
					cout << "Number of Student  : " << bnumStudent << endl;
					cout << "Date               : " << bdate << endl;
					n++;
					reserved = true;
				}
			}
			inFile.close();
			if (reserved)
				cout << "\nAbove are the booked details!" << endl;
			else
				cout << "\nNo booked details!" << endl;
			reserved = false;
		}
		else
			cout << "\nUnable to open file!" << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------\n";
}
//================================================================================================
// Function Update;
void updateDetails(int date, string zoom, string slot) {
	inFile.open("booking.txt");

	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, bzoom);
			getline(inFile, bslot);
			inFile.getline(bcourseName, size_1);
			inFile >> bnumStudent;
			inFile >> bdate;
			inFile.ignore();
			if (bzoom == "")
				break;
			if (date == bdate) {
				if (zoom == bzoom && slot == bslot) {
					cout << "\nReserved Detail  No. " << n + 1 << endl;
					cout << "Zoom               : " << bzoom << endl;
					cout << "Slot               : " << bslot << endl;
					cout << "Coursename         : " << bcourseName << endl;
					cout << "Number of Student  : " << bnumStudent << endl;
					cout << "Date               : " << bdate << endl;
					inFile.close();
					inFile.open("booking.txt");
					temp.open("booking_temp.txt");
					cout << "\nInsert the new course name: ";
					cin.getline(courseName, size_1);
					for (t = 0; t < size_1; t++) {
						courseName[t] = toupper(courseName[t]);
					}
					cout << "\nInsert the new number of students: ";
					do {
						if (zoom == "Zoom A") {
							if (cin >> numStudent)
								if (numStudent > 0 && numStudent < 501)
									valid = true;
								else
									cout << "\nThe number of students are out of range!\nPlease insert again: ";
							else {
								cin.clear();
								cin.ignore(10000, '\n');
								cout << "\nIt is not an integer!\nPlease insert again: ";
							}
						}
						else {
							if (cin >> numStudent)
								if (numStudent > 0 && numStudent < 250)
									valid = true;
								else
									cout << "\nThe number of students are out of range!\nPlease insert again: ";
							else {
								cin.clear();
								cin.ignore(10000, '\n');
								cout << "\nIt is not an integer!\nPlease insert again: ";
							}
						}
					} while (!valid);
					valid = false;
					cin.ignore();

					while (!inFile.eof()) {
						getline(inFile, bzoom);
						getline(inFile, bslot);
						inFile.getline(bcourseName, size_1);
						inFile >> bnumStudent;
						inFile >> bdate;
						inFile.ignore();
						if (bzoom == "")
							break;

						if (date != bdate) {
							if (zoom != bzoom || slot != bslot) {
								temp << bzoom << endl;
								temp << bslot << endl;
								temp << bcourseName << endl;
								temp << bnumStudent << endl;
								temp << bdate << endl;
							}
						}
					}
					temp << zoom << endl;
					temp << slot << endl;
					temp << courseName << endl;
					temp << numStudent << endl;
					temp << date << endl;
					cout << "\nThe details has been updated successfully!" << endl;
					cout << "---------------------------------------------------------------------------------------------------\n";
					inFile.close();
					temp.close();
					remove("booking.txt");
					rename("booking_temp.txt", "booking.txt");
				}
				else {
					cout << "\nPlease just insert the details of ONE slot." << endl;
					inFile.close();
				}
			}
			else
				cout << "\nThere is no booked slot." << endl;
		}
	}
	else
		cout << "\nUnable to open file!" << endl;
	system("pause");
	system("CLS");

}
//
void update(string zoom, string slot, char courseName[size_1], int numStudent, int date) {
	inFile.open("booking.txt");
	temp.open("booking_temp.txt");

	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, bzoom);
			getline(inFile, bslot);
			inFile.getline(bcourseName, size_1);
			inFile >> bnumStudent;
			inFile >> bdate;
			inFile.ignore();
			if (bzoom == "")
				break;
			if (date == bdate) {
				if (zoom == bzoom || slot == bslot) {
					continue;
				}
			}
			temp << bzoom << endl;
			temp << bslot << endl;
			temp << bcourseName << endl;
			temp << bnumStudent << endl;
			temp << bdate << endl;

		}
		temp << zoom << endl;
		temp << slot << endl;
		temp << courseName << endl;
		temp << numStudent << endl;
		temp << date << endl;
		cout << "\nThe booking has been updated successfully!" << endl;
		inFile.close();
		temp.close();
		remove("booking.txt");
		rename("booking_temp.txt", "booking.txt");
	}
	else
		cout << "\nUnable to open file!" << endl;
}
//================================================================================================
// Function Delete;
void deleteSlot() {
	cout << "\nPlease enter the course name you wish to delete: ";
	cin.getline(courseName, size_1);
	for (t = 0; t < size_1; t++) {
		courseName[t] = toupper(courseName[t]);
	}
	inFile.open("booking.txt");
	temp.open("booking_temp.txt");

	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, bzoom);
			getline(inFile, bslot);
			inFile.getline(bcourseName, size_1);
			inFile >> bnumStudent;
			inFile >> bdate;
			inFile.ignore();
			if (bzoom == "")
				break;

			if (strcmp(courseName, bcourseName) != 0) {
				temp << bzoom << endl;
				temp << bslot << endl;
				temp << bcourseName << endl;
				temp << bnumStudent << endl;
				temp << bdate << endl;
			}
			else {
				cout << "\nDeleted Detail  No. " << n + 1 << endl;
				cout << "Zoom               : " << bzoom << endl;
				cout << "Slot               : " << bslot << endl;
				cout << "Coursename         : " << bcourseName << endl;
				cout << "Number of Student  : " << bnumStudent << endl;
				cout << "Date               : " << bdate << endl;
				n++;
			}
		}
		cout << "\nThe booking has been deleted successfully!" << endl;
		cout << "---------------------------------------------------------------------------------------------------\n";
		inFile.close();
		temp.close();
		remove("booking.txt");
		rename("booking_temp.txt", "booking.txt");
	}
	else
		cout << "\nUnable to open file!" << endl;
	system("pause");
	system("CLS");
}
//================================================================================================