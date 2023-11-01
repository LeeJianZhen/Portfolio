#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;

bool ReadFile(string, List *);
bool DeleteRecord(List *, const char *);
bool Display(List*, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, const char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();
void DisplayRecords(List *);
char authorname[50][30];
unsigned int juliandate(unsigned int year, unsigned int month, unsigned int day);


int main() {
	bool end = false;
	List list;
	List type1;
	List type2;
	LibStudent stu;
	char stuid[10];
	while (end != true)
	{
		int choice;
		choice = menu();
		switch (choice)
		{
		case 1:
			ReadFile("student.txt", &list);
			break;

		case 2:
			cout << "Please Enter The Student ID To Search:\n";
			cin.ignore();
			cin.getline(stuid, 10);
			cout << "\n";
			if (!DeleteRecord(&list, stuid))
				cout << "\nNo Item To Delete...\n";
			else
				cout << stuid << " record have been deleted\n";
			break;

		case 3:
			cout << "Please Enter The Student ID To Search:\n";
			cin.ignore();
			cin.getline(stuid, 10);
			cout << "\n";
			SearchStudent(&list, stuid, stu);
			cout << "Id: " << stu.id << "\n";
			cout << "Name: " << stu.name << "\n";
			cout << "Course: " << stu.course << "\n";
			cout << "Phone No: " << stu.phone_no << "\n";
			break;

		case 4:
			if (InsertBook("book.txt", &list))
				cout << "Books inserted successfully to student list.\n";
			break;

		case 5:
			int source, detail;
			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;
			cout << endl;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;
			if ((source > 2 || source < 1) || (detail > 2 || detail < 1)) {
				cout << "\nInvalid Input\n";
				break;
			}
			if (Display(&list, source, detail) == false)
				cout << "\nEmpty list found\n";
			else
				cout << "\nSuccessfully display output\n";
			break;

		case 6:
			if (computeAndDisplayStatistics(&list) == false)
				cout << "\nEmpty list found\n";
			else
				cout << "\nSuccessfully display output\n";
			break;

		case 7:
			char bookid[20];
			cout << "Insert book's call number to search which student had borrowed: ";
			cin >> bookid;
			if (printStuWithSameBook(&list, bookid) == false)
				cout << "\nEmpty list found\n";
			else
				cout << "\nSuccessfully display output\n";
			break;

		case 8:
			if (displayWarnedStudent(&list, &type1, &type2) == false)
				cout << "\nEmpty list found\n";
			else
				cout << "\nSuccessfully display output\n";
			break;

		case 9:
			end = true;
			break;

		default:
			printf("ERROR: Invalid.\n\n");
			break;
		}
	}


	cout << "\n\n";
	system("pause");
	return 0;
}


int menu() {
	int i;
	cout << "\nMenu\n\n";
	cout << "1. Read file.\n";
	cout << "2. Delete record.\n";
	cout << "3. Search student.\n";
	cout << "4. Insert book.\n";
	cout << "5. Display output\n";
	cout << "6. Compute and Display Statistics\n";
	cout << "7. Student with Same Book\n";
	cout << "8. Display Warned Student\n";
	cout << "9. Exit.\n\n";

	cout << "Please Enter Your Choice To Proceed: ";
	cin >> i;
	cout << "\n";
	return i;
}

bool ReadFile(string textfile, List *list) {
	ifstream in;
	in.open(textfile);
	if (!in)
		cout << "Fail To Open student.txt file!\n";
	else {
		while (!in.eof()) {

			string fstudentid, fname, fcourse, fphoneno;    //read the data from the textfile 
			getline(in, fstudentid);
			if (fstudentid == "") {
				continue;
			}
			getline(in, fname);
			getline(in, fcourse);
			getline(in, fphoneno);

			LibStudent student;
			strcpy(student.id, fstudentid.substr(13).c_str());
			strcpy(student.name, fname.substr(7).c_str());
			strcpy(student.course, fcourse.substr(9).c_str());
			strcpy(student.phone_no, fphoneno.substr(15).c_str());
			list->insert(student);

		}
		cout << list->size() << " records have been successfully read.\n";
		in.close();
		return true;
	}
	return false;

}

bool DeleteRecord(List *list, const char id[10]) {
	Node	*cur;
	cur = list->head;

	for (int count = 1; count <= list->size(); count++) {
		if (strcmp(id, cur->item.id) == 0) {
			list->remove(count);
			return true;
		}
		cur = cur->next;
	}

	return false;
}

bool SearchStudent(List *list, const char id[10], LibStudent &stu) {
	Node	*cur;
	cur = list->head;

	for (int count = 1; count <= list->size(); count++) {
		if (strcmp(id, cur->item.id) == 0) {
			stu = cur->item;
			return true;
		}
		cur = cur->next;
	}

	return false;
}
// test
bool SearchStudent(List *list, char *keyword, LibStudent &stu) {
	Node	*cur;
	cur = list->head;

	for (int count = 1; count <= list->size(); count++) {
		if (strcmp(keyword, cur->item.name) == 0|| strcmp(keyword, cur->item.phone_no) == 0|| strcmp(keyword, cur->item.ic_no) == 0) {
			stu = cur->item;
			return true;
		}
		cur = cur->next;
	}
	return false;
}

bool InsertBook(string bookfile, List *list) {
	string id, author, title, publisher, call_Number, ISBN, Year_Published, Borrow_Date, Due_Date;
	ifstream in;
	in.open(bookfile);
	if (!in)
		cout << "Fail To Open student.txt file!\n";
	else {

		int authorcount = 0;
		while (in >> id >> author >> title >> publisher >> ISBN >> Year_Published >> call_Number >> Borrow_Date >> Due_Date) {
			LibBook book;
			string delimiter = "/";

			size_t pos = 0;
			string token;
			int authorpos = 0;

			while ((pos = author.find(delimiter)) != string::npos) { //delete the / when read the data
				token = author.substr(0, pos);
				strcpy(authorname[authorcount], token.c_str());
				book.author[authorpos] = authorname[authorcount];

				author.erase(0, pos + delimiter.length());
				authorpos++;
				authorcount++;
			}
			if (author != "") {
				strcpy(authorname[authorcount], author.c_str());
				book.author[authorpos] = authorname[authorcount];
				authorcount++;
			}

			strcpy(book.title, title.c_str());
			strcpy(book.publisher, publisher.c_str());
			strcpy(book.ISBN, ISBN.c_str());
			book.yearPublished = stoi(Year_Published);
			strcpy(book.callNum, call_Number.c_str());

			size_t datepos = Borrow_Date.find("/");
			book.borrow.day = stoi(Borrow_Date.substr(0, datepos));
			Borrow_Date.erase(0, datepos + 1);
			datepos = Borrow_Date.find("/");
			book.borrow.month = stoi(Borrow_Date.substr(0, datepos));
			Borrow_Date.erase(0, datepos + 1);
			book.borrow.year = stoi(Borrow_Date);

			size_t datepos1 = Due_Date.find("/");
			book.due.day = stoi(Due_Date.substr(0, datepos1));
			Due_Date.erase(0, datepos1 + 1);
			datepos1 = Due_Date.find("/");
			book.due.month = stoi(Due_Date.substr(0, datepos1));
			Due_Date.erase(0, datepos1 + 1);
			book.due.year = stoi(Due_Date);

			unsigned int currentdate = juliandate(2020, 3, 29);
			unsigned int duedate = juliandate(book.due.year, book.due.month, book.due.day);
			if (currentdate <= duedate) {
				book.fine = 0;
			}
			else
				book.fine = (currentdate - duedate) * 0.5;



			Node	*cur;
			cur = list->head;

			for (int count = 1; count <= list->size(); count++) {
				if (strcmp(id.c_str(), cur->item.id) == 0) {
					cur->item.book[cur->item.totalbook] = book;
					cur->item.totalbook++;
					cur->item.calculateTotalFine();
					break;
				}
				cur = cur->next;
			}
		}


		in.close();
		return true;
	}
	return false;



}

//Function to take date of installation and convert it to a julian date
unsigned int juliandate(unsigned int year, unsigned int month, unsigned int day)
{//Passes in Installation date
	//Declare variables to be used in converting date
	int julianDate;
	int Y;
	int M;
	int D;
	Y = year;
	M = month;
	D = day;

	//Formula to convert gregorian date to julian date
	julianDate = 367 * Y - (7 * (Y + 5001 + (M - 9) / 7)) / 4 + (275 * M) / 9 + D + 1729777;

	return julianDate;
}

bool Display(List *list, int source, int detail) {
	if (list->size() == 0)
		return false;
	system("CLS");
	Node	*cur;
	cur = list->head;
	bool bookinfo = false;

	cout << "\nDISPLAY OUTPUT\n";
	// display to screen
	if (source == 2) {
		// display student details
		for (int count = 0; count < list->size(); count++) {
			cout << "\nSTUDENT " << count + 1;
			cur->item.print(cout);
			// display book details
			if (detail == 1) {
				cout << "\nBOOK LIST:\n";
				for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
					cout << "\nBook " << bookcount + 1 << "\n";
					cur->item.book[bookcount].print(cout);
				}
			}
			cout << "\n*****************************************************************************\n";
			cur = cur->next;
		}
		return true;
	}
	// display to txt file
	else if (source == 1) {
		ofstream out;
		out.open("student_info.txt");
		// display student details
		for (int count = 0; count < list->size(); count++) {
			out << "\nSTUDENT " << count + 1;
			cur->item.print(out);
			// display book details
			if (detail == 1) {
				out.open("student_booklist.txt");
				bookinfo = true;
				out << "\nBOOK LIST:\n";
				for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
					out << "\nBook " << bookcount + 1 << "\n";
					cur->item.book[bookcount].print(out);
				}
			}
			out << "\n*****************************************************************************\n";
			cur = cur->next;
		}
		out.close();
		if (!bookinfo)
			cout << "\nSuccessfully display output to student_info.txt\n";
		else
			cout << "\nSuccessfully display output to student_booklist.txt\n";
		return true;
	}
}

bool computeAndDisplayStatistics(List *list) {
	system("CLS");

	char coursetype[3];
	int nCourse = 0, tBook = 0, tOBook = 0;
	double tOFine = 0;
	Node	*cur;
	cur = list->head;
	// display all the attributes
	cout << "\nCourse\tNumber of\tTotal Books\tTotal\t\tTotal";
	cout << "\n\tStudents\tBorrowed\tOverdue\t\tOverdue";
	cout << "\n\t\t\t\t\tBooks\t\tFine (RM)\n";
	//loop for 5 time to determine the 5 course type
	for (int loop = 0; loop < 5; loop++) {
		if (loop == 0)
			strcpy(coursetype, "CS");
		if (loop == 1)
			strcpy(coursetype, "IA");
		if (loop == 2)
			strcpy(coursetype, "IB");
		if (loop == 3)
			strcpy(coursetype, "CN");
		if (loop == 4)
			strcpy(coursetype, "CT");
		// read list
		for (int count = 0; count < list->size(); count++) {
			// determine the course type
			if (strcmp(cur->item.course, coursetype) == 0) {
				//read book
				for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
					// calculate total overdue book
					if (cur->item.book[bookcount].fine > 0)
						tOBook++;
				}
				nCourse++;
				tBook += cur->item.totalbook;
				tOFine += cur->item.total_fine;
			}
			cur = cur->next;
		}
		// display the statistics
		cout << coursetype << "\t";
		cout << nCourse << "\t\t";
		cout << tBook << "\t\t";
		cout << tOBook << "\t\t";
		cout << tOFine;
		cout << endl;
		nCourse = 0, tBook = 0, tOBook = 0, tOFine = 0;
		strcpy(coursetype, " ");
		cur = list->head;
	}
	if (list->size() == 0)
		return false;
	else
		return true;
}

bool printStuWithSameBook(List *list, char *callNum) {
	if (list->size() == 0)
		return false;
	system("CLS");

	Node	*cur;
	cur = list->head;
	int nBorrow = 0;
	bool dupli = false;

	// calculate number student that borrow the same book
	for (int count = 0; count < list->size(); count++) {
		for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
			if (strcmp(cur->item.book[bookcount].callNum, callNum) == 0) {
				if (!dupli) {
					nBorrow++;
					dupli = true;
				}
			}
		}
		cur = cur->next;
	}
	cur = list->head;
	cout << "There are " << nBorrow << " students that borrow the book with call number " << callNum << " as shown below:\n";
	nBorrow = 0;
	// display the information of student which borrow the same book
	for (int count = 0; count < list->size(); count++) {
		for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
			if (strcmp(cur->item.book[bookcount].callNum, callNum) == 0) {
				nBorrow++;
				cout << "\nSTUDENT " << nBorrow << "\n\n";
				cout << "Student Id: " << cur->item.id << "\n";
				cout << "Name: " << cur->item.name << "\n";
				cout << "Course: " << cur->item.course << "\n";
				cout << "Phone Number: " << cur->item.phone_no << "\n";
				cout << "Borrow Date: ";
				cur->item.book[bookcount].borrow.print(cout);
				cout << "\n";
				cout << "Due Date: ";
				cur->item.book[bookcount].due.print(cout);
				cout << "\n";
				cout << "\n*****************************************************************************\n";
			}
		}
		cur = cur->next;
	}
	return true;
}

bool displayWarnedStudent(List *list, List *type1, List *type2) {
	if (list->size() == 0)
		return false;
	system("CLS");

	Node	*cur, *cur1, *cur2;
	type result;
	cur = list->head;
	bool dupli1, dupli2;
	int tDBook = 0;

	// start to read list
	for (int count = 0; count < list->size(); count++) {
		dupli1 = false;
		dupli2 = false;
		// read each student's books
		for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
			// determine type1 warning
			if (cur->item.book[bookcount].fine >= 5) {
				tDBook++;
			}
			if (tDBook > 2) {
				// copy to type1 list
				if (!dupli1) {
					type1->insert(cur->item);
					dupli1 = true;
				}
			}
			// determine type2 warning
			if ((tDBook == cur->item.totalbook) && (cur->item.total_fine > 50)) {
				// copy to type2 list
				if (!dupli2) {
					type2->insert(cur->item);
					dupli2 = true;
				}
			}
		}
		tDBook = 0;
		// read next student
		cur = cur->next;
	}
	// display list type1 and list type2
	if (type1->size() != 0) {
		cout << "\nTYPE 1 WARNING:\n\n";
		cur = type1->head;
		for (int count = 0; count < type1->size(); count++) {
			cout << "STUDENT " << count + 1;
			cur->item.print(cout);
			for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
				cur->item.book[bookcount].print(cout);
			}
			cout << "\n*****************************************************************************\n";
			cur = cur->next;
		}
	}
	else
		cout << "\nNO TYPE 1 WARNING.\n\n";
	if (type2->size() != 0) {
		cout << "\nTYPE 2 WARNING:\n\n";
		cur = type2->head;
		for (int count = 0; count < type2->size(); count++) {
			cout << "STUDENT " << count + 1;
			cur->item.print(cout);
			for (int bookcount = 0; bookcount < cur->item.totalbook; bookcount++) {
				cur->item.book[bookcount].print(cout);
			}
			cout << "\n*****************************************************************************\n";
			cur = cur->next;
		}
	}
	else
		cout << "\nNO TYPE 2 WARNING.\n\n";
	// empty list type1 and list type2
	for (int count = 0; count < type1->size(); count++) {
		type1->remove(type1->size());
	}
	for (int count = 0; count < type2->size(); count++) {
		type2->remove(type2->size());
	}
	return true;
}
