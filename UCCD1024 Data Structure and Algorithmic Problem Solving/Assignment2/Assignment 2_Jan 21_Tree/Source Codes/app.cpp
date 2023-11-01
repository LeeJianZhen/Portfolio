#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

BST stuTree;
BST *cloneTree;
Student stuStruct;
ifstream in;

int menu();
bool readFile(char *, BST *);
void ignore(int);
bool redundant(BST *, Student);
bool redundant2(BTNode *, Student);


int main() {
	bool exit = false;

	while (exit != true) {
		int ch;
		ch = menu();
		switch (ch)
		{
		case 1:
			char filename[64];
			strcpy(filename, "student.txt");

			if (!readFile(filename, &stuTree))
				cout << "< File name " << filename << " unable to open >" << endl;
			break;

		case 2:
			if (!stuTree.deepestNodes())
				cout << "\n< Tree is empty... >";
			break;

		case 3:
			int order, source;
			cout << "\n\tOrder choice:-\n";
			cout << "\t(1) Display ascending\n";
			cout << "\t(2) Display descending\n";
			cout << "Please Enter Your Choice To Proceed: ";
			while (!(cin >> order)) {
				cout << "Please only enter number: ";
				cin.clear();
				cin.ignore(123, '\n');
			}
			cin.ignore();
			cout << "\n\tSource choice:-\n";
			cout << "\t(1) Display to screen\n";
			cout << "\t(2) Display to file\n";
			cout << "Please Enter Your Choice To Proceed: ";
			while (!(cin >> source)) {
				cout << "Please only enter number: ";
				cin.clear();
				cin.ignore(123, '\n');
			}
			system("CLS");
			cin.ignore();
			if (!stuTree.display(order, source))
				cout << "\n< Tree is empty... >";
			else {
				if (source == 2)
					cout << "Displayed to Student-info.txt file" << endl;
			}
			break;

		case 4:
			cloneTree = new BST;
			cout << "Please Enter The Student ID: ";
			cin >> stuStruct.id;
			cout << endl;

			if (cloneTree->CloneSubtree(stuTree, stuStruct)) {
				cout << "Clone Successfully" << endl;
				cout << "\n--------------------Tree 1--------------------" << endl;
				stuTree.preOrderPrint();
				cout << "\n--------------------Tree 2--------------------" << endl;
				if (cloneTree->empty())
					cout << "\n< Empty clone tree... >" << endl;
				else
					cloneTree->preOrderPrint();
			}
			else
				cout << "\n< Tree is empty... >" << endl;
			break;

		case 5:
			cout << "Please Enter The Student ID: ";
			cin >> stuStruct.id;
			cout << endl;
			if (!stuTree.printAncestor(stuStruct))
				cout << "\n< Cannot print the Ancestor... >";
			cout << endl;
			break;

		case 6:
			if (!stuTree.printSpiral())
				cout << "\n< Cannont print from empty tree... >" << endl;
			else
				cout << endl;
			break;

		case 7:
			exit = true;
			cout << "\n\tHAVE A NICE DAY!\n";
			break;

		default:
			cout << "Invalid choice";
			break;
		}
		cout << endl << "- - - - - - - - - - - - - - - -\n";
		system("PAUSE");
		system("CLS");
	}
	return 0;
}

// Display Menu
int menu() {
	int num;
	cout << "\n\t---MENU---\n";
	cout << "\t(1) Read data to BST\n";
	cout << "\t(2) Print deepest nodes\n";
	cout << "\t(3) Display student\n";
	cout << "\t(4) Clone Subtree\n";
	cout << "\t(5) Print Ancestor\n";
	cout << "\t(6) Print Spiral\n";
	cout << "\t(7) Exit\n";

	cout << "Please Enter Your Choice To Proceed: ";
	while (!(cin >> num)) {
		cout << "Please only enter number: ";
		cin.clear();
		cin.ignore(123, '\n');
	}
	cin.ignore();
	cout << "\n";
	return num;
}

// Read and store student data inside BST
bool readFile(char *filename, BST *t1) {

	char temp[256];
	int c;
	int id;

	in.open(filename);
	if (!in)
		return false;

	c = 0;
	while (!in.eof()) {
		ignore(2);
		in >> stuStruct.id;
		id = stuStruct.id;

		ignore(2);
		in >> stuStruct.name;
		in.getline(temp, 256);
		strcat(stuStruct.name, temp);

		ignore(2);
		in >> stuStruct.address;
		in.getline(temp, 256);
		strcat(stuStruct.address, temp);

		ignore(2);
		in >> stuStruct.DOB;

		ignore(2);
		in >> stuStruct.phone_no;

		ignore(2);
		in >> stuStruct.course;

		ignore(2);
		in >> stuStruct.cgpa;

		if (!redundant(t1, stuStruct)) {
			t1->insert(stuStruct);
			c++;
		}
	}
	in.close();

	cout << "Total successfully read: " << c << endl;
	stuTree.allocateHeight();

	// rebalance BST until balance
	/*while (stuTree.getBalance(stuTree.root) < -1 || stuTree.getBalance(stuTree.root) > 1) {
		stuTree.balancing(stuTree.root);
		stuTree.allocateHeight();
	}*/
	return true;
}

// Ignore certain amount of words
void ignore(int count) {
	char ignore[64];
	int i;
	for (i = 0; i < count; i++)
		in >> ignore;
}

// check for redundant
bool redundant(BST *tree, Student item) {
	if (tree->root == NULL) return false;	// handle special case
	return redundant2(tree->root, item);	// normal case
}

// recursive function for redundant(BST *, Student)
bool redundant2(BTNode *cur, Student item) {
	if (cur == NULL) return false;		// turn back if the path end
	if (cur->item.compare2(item)) return true;	// found

	// not found, continue check left side
	if (cur->item.compare1(item))
		return redundant2(cur->left, item);

	// check right side
	return redundant2(cur->right, item);
}
