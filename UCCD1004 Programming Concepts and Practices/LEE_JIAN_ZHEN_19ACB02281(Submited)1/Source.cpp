#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
int main(void) { // update the name(clear the name)
	//Course Code and Name.
	string CN, CN1, CN2, CN3, CN4;
	CN = "", CN1 = "", CN2 = "", CN3 = "", CN4 = "";
	//Number of Students.
	int NS, NS1, NS2, NS3, NS4;
	NS = 0, NS1 = 0, NS2 = 0, NS3 = 0, NS4 = 0;
	//Time Slots.
	int TS = 0;
	string TSC, TSD;
	TSC = "11a.m.-1p.m.";
	TSD = "2a.m.-4p.m.";
	int C = 0, D = 0;
	//ZOOM Accounts.
	int ZA = 0;
	string ZAA = "ZOOM A";
	string ZAB = "ZOOM B";
	int A = 0, B = 0;
	//Booked account.
	int AC, AD, BC, BD;
	AC = 0, AD = 0, BC = 0, BD = 0;
	//Display.
	string Dcn = "<> Course code and name";
	string Dns = "<> Number of students";
	string Dts = "<> Time slot";
	string Dza = "<> Zoom account";
	//Count.
	int NB = 0, UB = 0, CB = 0, TB = 0;
	//Decisions.
	int select;
	bool valid = false, end_valid = false;
	do {
		cout << "\n_______________________________________________________________________________________________\n";
		cout << "<> Welcome to ZOOM booking services.\n";
		cout << "<> There are only two ZOOM accounts available : ZOOM A and ZOOM B\n";
		cout << "<> Only two time slots are available :  11a.m. ~ 1p.m. and 2p.m. ~ 4p.m.\n";
		cout << "<> ZOOM A is able to accept maximum 500 students per session.\n";
		cout << "<> ZOOM B is able to accept less than 250 students per session.\n";
		cout << "-----------------------------------------------------------------------------------------------\n";
		cout << "<> Fill in the information.\n";
		cout << setw(24) << left << Dcn << ": ";
		getline(cin, CN);
		cout << setw(24) << left << Dns << ": ";
		do {
			if (cin >> NS) {
				cin.ignore();
				if (NS > 0 && NS < 501) {
					valid = true;
				}
				else {
					cout << " \n< ERROR > Number is out of limit.\n" << " Please [ ENTER ] the number of students again.\n" << ">";
					continue;
				}
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << " \n< ERROR > Input invalid.\n" << " Please [ ENTER ] the number of students again.\n" << ">";
			}
		} while (!valid);
		valid = false;
		if (NS > 250) {
			cout << "\n<> Number of students more than 250.\n" << "<> ZOOM A selected.\n";
			cout << "<> [ SELECT ] A time slot.\n" << " [1] " << TSC << "\n [2] " << TSD << "\n>";
			do {
				if (cin >> TS) {
					cin.ignore();
					if (TS > 0 && TS < 3) {
						valid = true;
					}
					else {
						cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] the time slot again.\n" << ">";
						continue;
					}
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] the time slot again.\n" << ">";
				}
			} while (!valid);
			valid = false;
			if (TS == 1) {
				if (A == 1 || C == 1) {
					if (CN1 == CN) {
						cout << "\n<> You had booked the entire slot! \n";
					}
					else if (AD == 1 && BC == 1) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN2 << endl;
						cout << setw(24) << left << Dcn << ": " << CN3 << endl;
					}
					else if (AC == 1) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN1 << endl;
					}
					else if (BC == 0) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN2 << endl;
					}
					else if (AD == 0) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN3 << endl;
					}
					cout << " \n Do you want to update or cancel the booking?\n" << " [1] Update the booked slot.\n" << " [2] Cancel the booked slot.\n"<<" [3] Remain the booked slot.\n" << ">";
					do {
						if (cin >> select) {
							cin.ignore();
							if (select > 0 && select < 4) {
								valid = true;
							}
							else {
								cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
								continue;
							}
						}
						else {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
						}
					} while (!valid);
					valid = false;
					if (select == 1) {
						if (AD == 1 && BC == 1) {
							AD = 0, BC = 0, A = 0, B = 0, C = 0, D = 0;
						}
						else if (BC == 0) {
							AD = 0, A = 0, D = 0;
						}
						else if (AD == 0) {
						}
						AC = 1, A = 1, C = 1;
						UB++;
						cout << "\n<> Update Successfully.\n";
						CN1 = CN, NS1 = NS;
					}
					else if (select == 2) {
						if (AD == 1 && BC == 1) {
							AD = 0, BC = 0, A = 0, B = 0, C = 0, D = 0;
							CN2 = "", CN3 = "";
						}
						else if (AC == 1) {
							AC = 0, A = 0, C = 0;
							CN1 = "";
						}
						else if (BC == 0) {
							AD = 0, A = 0, D = 0;
							CN2 = "";
						}
						else if (AD == 0) {
							BC = 0, B = 0, C = 0;
							CN3 = "";
						}
						CB++, TB--;
						cout << "\n<> Slot cancelled.\n";
					}
				}
				else {
					NB++, TB++;
					cout << "\n<> Book Successful.\n";
					AC = 1, A = 1, C = 1;
					CN1 = CN, NS1 = NS;
				}
				cout << "\n Please [SELECT] to continue:\n" << " [1] Book new slot.\n" << " [2] Exit.\n" << ">";
				do {
					if (cin >> select) {
						cin.ignore();
						if (select > 0 && select < 3) {
							valid = true;
						}
						else {
							cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
							continue;
						}
					}
					else {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
					}
					if (select == 2) {
						end_valid = true;
					}
				} while (!valid);
				valid = false;
				system("cls");
			}
			else {
				if (A == 1 || D == 1) {
					if (CN2 == CN) {
						cout << "\n<> You had booked the entire slot! \n";
					}
					else if (AC == 1 && BD == 1) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN1 << endl;
						cout << setw(24) << left << Dcn << ": " << CN4 << endl;
					}
					else if (AD == 1) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN2 << endl;
					}
					else if (BD == 0) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN1 << endl;
					}
					else if (AC == 0) {
						cout << "\n<> This slot was booked by: \n";
						cout << setw(24) << left << Dcn << ": " << CN4 << endl;
					}
					cout << " \n Do you want to update or cancel the booking?\n" << " [1] Update the booked slot.\n" << " [2] Cancel the booked slot.\n" << " [3] Remain the booked slot.\n" << ">";
					do {
						if (cin >> select) {
							cin.ignore();
							if (select > 0 && select < 4) {
								valid = true;
							}
							else {
								cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
								continue;
							}
						}
						else {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
						}
					} while (!valid);
					valid = false;
					if (select == 1) {
						if (AC == 1 && BD == 1) {
							AC = 0, BD = 0, A = 0, C = 0, B = 0, D = 0;
						}
						else if (BD == 0) {
							AC = 0, A = 0, C = 0;
						}
						else if (AC == 0) {
							BD = 0, B = 0, D = 0;
						}
						AD = 1, A = 1, D = 1;
						UB++;
						cout << "\n<> Update Successfully.\n";
						CN2 = CN, NS2 = NS;
					}
					else if (select == 2) {
						if (AC == 1 && BD == 1) {
							AC = 0, BD = 0, A = 0, C = 0, B = 0, D = 0;
							CN1 = "", CN4 = "";
						}
						else if (AD == 1) {
							AD = 0, A = 0, D = 0;
							CN2 = "";
						}
						else if (BD == 0) {
							AC = 0, A = 0, C = 0;
							CN1 = "";
						}
						else if (AC == 0) {
							BD = 0, B = 0, D = 0;
							CN4 = "";
						}
						CB++, TB--;
						cout << "\n<> Slot cancelled.\n";
					}
				}
				else {
					NB++, TB++;
					cout << "\n<> Book Successfully.\n";
					AD = 1, A = 1, D = 1;
					CN2 = CN, NS2 = NS;
				}
				cout << "\n Please [SELECT] to continue:\n" << " [1] Book new slot.\n" << " [2] Exit.\n" << ">";
				do {
					if (cin >> select) {
						cin.ignore();
						if (select > 0 && select < 3) {
							valid = true;
						}
						else {
							cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
							continue;
						}
					}
					else {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
					}
					if (select == 2) {
						end_valid = true;
					}
				} while (!valid);
				valid = false;
				system("cls");
			}
		}
		else {
			cout << "\n<> Number of students less than or equal to 250.";
			cout << "\n [ SELECT ] A ZOOM account." << "\n [1] ZOOM A" << "\n [2] ZOOM B" << "\n>";
			do {
				if (cin >> ZA) {
					cin.ignore();
					if (ZA > 0 && ZA < 3) {
						valid = true;
					}
					else {
						cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] the ZOOM account again.\n" << ">";
						continue;
					}
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] the ZOOM account again.\n" << ">";
				}
			} while (!valid);
			valid = false;
			cout << "\n<> [ SELECT ] A time slot.\n" << " [1] " << TSC << "\n [2] " << TSD << "\n>";
			do {
				if (cin >> TS) {
					cin.ignore();
					if (TS > 0 && TS < 3) {
						valid = true;
					}
					else {
						cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] the time slot again.\n" << ">";
						continue;
					}
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] the time slot again.\n" << ">";
				}
			} while (!valid);
			valid = false;
			if (ZA == 1) {
				if (TS == 1) {
					if (A == 1 || C == 1) {
						if (CN1 == CN) {
							cout << "\n<> You had booked the entire slot! \n";
						}
						else if (AD == 1 && BC == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN2 << endl;
							cout << setw(24) << left << Dcn << ": " << CN3 << endl;
						}
						else if (AC == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN1 << endl;
						}
						else if (BC == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN2 << endl;
						}
						else if (AD == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN3 << endl;
						}
						cout << " \n Do you want to update or cancel the booking?\n" << " [1] Update the booked slot.\n" << " [2] Cancel the booked slot.\n" << " [3] Remain the booked slot.\n" << ">";
						do {
							if (cin >> select) {
								cin.ignore();
								if (select > 0 && select < 4) {
									valid = true;
								}
								else {
									cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
									continue;
								}
							}
							else {
								cin.clear();
								cin.ignore(10000, '\n');
								cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
							}
						} while (!valid);
						valid = false;
						if (select == 1) {
							if (AD == 1 && BC == 1) {
								AD = 0, BC = 0, A = 0, B = 0, C = 0, D = 0;
							}
							else if (BC == 0) {
								AD = 0, A = 0, D = 0;
							}
							else if (AD == 0) {
								BC = 0, B = 0, C = 0;
							}
							AC = 1, A = 1, C = 1;
							UB++;
							cout << "\n<> Update Successfully.\n";
							CN1 = CN, NS1 = NS;
						}
						else if (select == 2) {
							if (AD == 1 && BC == 1) {
								AD = 0, BC = 0, A = 0, B = 0, C = 0, D = 0;
								CN2 = "", CN3 = "";
							}
							else if (AC == 1) {
								AC = 0, A = 0, C = 0;
								CN1 = "";
							}
							else if (BC == 0) {
								AD = 0, A = 0, D = 0;
								CN2 = "";
							}
							else if (AD == 0) {
								BC = 0, B = 0, C = 0;
								CN3 = "";
							}
							CB++, TB--;
							cout << "\n<> Slot cancelled.\n";
						}
					}
					else {
						NB++, TB++;
						cout << "\n<> Book Successful.\n";
						AC = 1, A = 1, C = 1;
						CN1 = CN, NS1 = NS;
					}
					cout << "\n Please [SELECT] to continue:\n" << " [1] Book new slot.\n" << " [2] Exit.\n" << ">";
					do {
						if (cin >> select) {
							cin.ignore();
							if (select > 0 && select < 3) {
								valid = true;
							}
							else {
								cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
								continue;
							}
						}
						else {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
						}
						if (select == 2) {
							end_valid = true;
						}
					} while (!valid);
					valid = false;
					system("cls");
				}
				else {
					if (A == 1 || D == 1) {
						if (CN2 == CN) {
							cout << "\n<> You had booked the entire slot! \n";
						}
						else if (AC == 1 && BD == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN1 << endl;
							cout << setw(24) << left << Dcn << ": " << CN4 << endl;
						}
						else if (AD == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN2 << endl;
						}
						else if (BD == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN1 << endl;
						}
						else if (AC == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN4 << endl;
						}
						cout << " \n Do you want to update or cancel the booking?\n" << " [1] Update the booked slot.\n" << " [2] Cancel the booked slot.\n" << " [3] Remain the booked slot.\n" << ">";
						do {
							if (cin >> select) {
								cin.ignore();
								if (select > 0 && select < 4) {
									valid = true;
								}
								else {
									cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
									continue;
								}
							}
							else {
								cin.clear();
								cin.ignore(10000, '\n');
								cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
							}
						} while (!valid);
						valid = false;
						if (select == 1) {
							if (AC == 1 && BD == 1) {
								AC = 0, BD = 0, A = 0, C = 0, B = 0, D = 0;
							}
							else if (BD == 0) {
								AC = 0, A = 0, C = 0;
							}
							else if (AC == 0) {
								BD = 0, B = 0, D = 0;
							}
							AD = 1, A = 1, D = 1;
							UB++;
							cout << "\n<> Update Successfully.\n";
							CN2 = CN, NS2 = NS;
						}
						else if (select == 2) {
							if (AC == 1 && BD == 1) {
								AC = 0, BD = 0, A = 0, C = 0, B = 0, D = 0;
								CN1 = "", CN4 = "";
							}
							else if (AD == 1) {
								AD = 0, A = 0, D = 0;
								CN2 = "";
							}
							else if (BD == 0) {
								AC = 0, A = 0, C = 0;
								CN1 = "";
							}
							else if (AC == 0) {
								BD = 0, B = 0, D = 0;
								CN4 = "";
							}
							CB++, TB--;
							cout << "\n<> Slot cancelled.\n";
						}
					}
					else {
						NB++, TB++;
						cout << "\n<> Book Successfully.\n";
						AD = 1, A = 1, D = 1;
						CN2 = CN, NS2 = NS;
					}
					cout << "\n Please [SELECT] to continue:\n" << " [1] Book new slot.\n" << " [2] Exit.\n" << ">";
					do {
						if (cin >> select) {
							cin.ignore();
							if (select > 0 && select < 3) {
								valid = true;
							}
							else {
								cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
								continue;
							}
						}
						else {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
						}
						if (select == 2) {
							end_valid = true;
						}
					} while (!valid);
					valid = false;
					system("cls");
				}
			}
			else {
				if (TS == 1) {
					if (B == 1 || C == 1) {
						if (CN3 == CN) {
							cout << "\n<> You had booked the entire slot! \n";
						}
						else if (BD == 1 && AC == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN4 << endl;
							cout << setw(24) << left << Dcn << ": " << CN1 << endl;
						}
						else if (BC == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN3 << endl;
						}
						else if (AC == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN4 << endl;
						}
						else if (BD == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN1 << endl;
						}
						cout << " \n Do you want to update or cancel the booking?\n" << " [1] Update the booked slot.\n" << " [2] Cancel the booked slot.\n" << " [3] Remain the booked slot.\n" << ">";
						do {
							if (cin >> select) {
								cin.ignore();
								if (select > 0 && select < 4) {
									valid = true;
								}
								else {
									cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
									continue;
								}
							}
							else {
								cin.clear();
								cin.ignore(10000, '\n');
								cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
							}
						} while (!valid);
						valid = false;
						if (select == 1) {
							if (BD == 1 && AC == 1) {
								BD = 0, AC = 0, A = 0, B = 0, C = 0, D = 0;
							}
							else if (BD == 0) {
								AC = 0, A = 0, C = 0;
							}
							else if (AC == 0) {
								BD = 0, B = 0, D = 0;
							}
							BC = 1, A = 1, C = 1;
							UB++;
							cout << "\n<> Update Successfully.\n";
							CN3 = CN, NS3 = NS;
						}
						else if (select == 2) {
							if (BD == 1 && AC == 1) {
								BD = 0, AC = 0, A = 0, B = 0, C = 0, D = 0;
								CN4 = "", CN1 = "";
							}
							else if (BC == 1) {
								BC = 0, B = 0, C = 0;
								CN3 = "";
							}
							else if (BD == 0) {
								AC = 0, A = 0, C = 0;
								CN1 = "";
							}
							else if (AC == 0) {
								BD = 0, B = 0, D = 0;
								CN4 = "";
							}
							CB++, TB--;
							cout << "\n<> Slot cancelled.\n";
						}
					}
					else {
						NB++, TB++;
						cout << "\n<> Book Successful.\n";
						BC = 1, B = 1, C = 1;
						CN3 = CN, NS3 = NS;
					}
					cout << "\n Please [SELECT] to continue:\n" << " [1] Book new slot.\n" << " [2] Exit.\n" << ">";
					do {
						if (cin >> select) {
							cin.ignore();
							if (select > 0 && select < 3) {
								valid = true;
							}
							else {
								cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
								continue;
							}
						}
						else {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
						}
						if (select == 2) {
							end_valid = true;
						}
					} while (!valid);
					valid = false;
					system("cls");
				}
				else {
					if (B == 1 || D == 1) {
						if (CN4 == CN) {
							cout << "\n<> You had booked the entire slot! \n";
						}
						else if (AD == 1 && BC == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN2 << endl;
							cout << setw(24) << left << Dcn << ": " << CN3 << endl;
						}
						else if (BD == 1) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN4 << endl;
						}
						else if (BC == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN2 << endl;
						}
						else if (AD == 0) {
							cout << "\n<> This slot was booked by: \n";
							cout << setw(24) << left << Dcn << ": " << CN3 << endl;
						}
						cout << " \n Do you want to update or cancel the booking?\n" << " [1] Update the booked slot.\n" << " [2] Cancel the booked slot.\n" << " [3] Remain the booked slot.\n" << ">";
						do {
							if (cin >> select) {
								cin.ignore();
								if (select > 0 && select < 4) {
									valid = true;
								}
								else {
									cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
									continue;
								}
							}
							else {
								cin.clear();
								cin.ignore(10000, '\n');
								cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
							}
						} while (!valid);
						valid = false;
						if (select == 1) {
							if (AD == 1 && BC == 1) {
								AD = 0, BC = 0, A = 0, C = 0, B = 0, D = 0;
							}
							else if (AD == 0) {
								BC = 0, B = 0, C = 0;
							}
							else if (BC == 0) {
								AD = 0, A = 0, D = 0;
							}
							AD = 1, A = 1, D = 1;
							UB++;
							cout << "\n<> Update Successfully.\n";
							CN4 = CN, NS4 = NS;
						}
						else if (select == 2) {
							if (AD == 1 && BC == 1) {
								AD = 0, BC = 0, A = 0, C = 0, B = 0, D = 0;
								CN2 = "", CN3 = "";
							}
							else if (BD == 1) {
								BD = 0, B = 0, D = 0;
								CN4 = "";
							}
							else if (BC == 0) {
								BC = 0, B = 0, C = 0;
								CN3 = "";
							}
							else if (AD == 0) {
								AD = 0, A = 0, D = 0;
								CN2 = "";
							}
							CB++, TB--;
							cout << "\n<> Slot cancelled.\n";
						}
					}
					else {
						NB++, TB++;
						cout << "\n<> Book Successfully.\n";
						BD = 1, B = 1, D = 1;
						CN4 = CN, NS4 = NS;
					}
					cout << "\n Please [SELECT] to continue:\n" << " [1] Book new slot.\n" << " [2] Exit.\n" << ">";
					do {
						if (cin >> select) {
							cin.ignore();
							if (select > 0 && select < 3) {
								valid = true;
							}
							else {
								cout << " \n< ERROR > Out of selection.\n" << " Please [ SELECT ] again.\n" << ">";
								continue;
							}
						}
						else {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << " \n< ERROR > Input invalid.\n" << " Please [ SELECT ] again.\n" << ">";
						}
						if (select == 2) {
							end_valid = true;
						}
					} while (!valid);
					valid = false;
					system("cls");
				}
			}
		}
	} while (!(end_valid));
	cout << "\n\n-----------------------------------------------------------------------------------------------\n";
	cout << "Total New Booking       :" << NB << endl;
	cout << "Total Updated Booking   :" << UB << endl;
	cout << "Total Cancelled Booking :" << CB << endl;
	cout << "Total Booking           :" << TB << endl << endl;
	if (AC == 1) {
		cout << setw(24) << left << Dcn << ": " << CN1 << endl;
		cout << setw(24) << left << Dns << ": " << NS1 << endl;
		cout << setw(24) << left << Dts << ": " << TSC << endl;
		cout << setw(24) << left << Dza << ": " << ZAA << endl << endl;
	}
	if (AD == 1) {
		cout << setw(24) << left << Dcn << ": " << CN2 << endl;
		cout << setw(24) << left << Dns << ": " << NS2 << endl;
		cout << setw(24) << left << Dts << ": " << TSD << endl;
		cout << setw(24) << left << Dza << ": " << ZAA << endl << endl;
	}
	if (BC == 1) {
		cout << setw(24) << left << Dcn << ": " << CN3 << endl;
		cout << setw(24) << left << Dns << ": " << NS3 << endl;
		cout << setw(24) << left << Dts << ": " << TSC << endl;
		cout << setw(24) << left << Dza << ": " << ZAB << endl << endl;
	}
	if (BD == 1) {
		cout << setw(24) << left << Dcn << ": " << CN4 << endl;
		cout << setw(24) << left << Dns << ": " << NS4 << endl;
		cout << setw(24) << left << Dts << ": " << TSD << endl;
		cout << setw(24) << left << Dza << ": " << ZAB << endl << endl;
	}
	cout << "\nSee you next time!";
	cout << "\n_______________________________________________________________________________________________\n";
	std::system("pause");
	return 0;
}