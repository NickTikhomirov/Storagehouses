#include "Reader.h"
#include <iostream>


using std::cout;
using std::cin;
using std::endl;

using std::islower;
using std::getline;
using std::stoi;
using std::stod;
using std::pair;



//Всё описано в заголовочном файле


bool Reader::isDigit(char r) {
	return (r >= '0' && r <= '9');
}

bool Reader::isLowerLetter(char p) {
	return(p >= 'a' && p <= 'z');
}

bool Reader::isNotUpperLetter(char p) {
	return(p < 'A' || p > 'Z');
}


bool Reader::isCharFromSizeString(char r) {
	if (r >= '0' && r <= '9') return true;
	if (r == '-') return true;
	return false;
}


bool Reader::checkStringTxt(string a) {
	if (a.length() < 5) return false;
	else return a.substr(a.length() - 4, 4) == ".txt";
}

void Reader::fixstring(string &a) {
	if (!checkStringTxt(a)) a += ".txt";
}



bool Reader::readDataForType_shoes(string s, pair<short, int>& k) {
	short p1 = 0;
	short counter = 0;

	if (s.length() < 3) return false;
	for (int i = 0; i < s.length(); i++) {
		if (!isCharFromSizeString(s[i])) return false;
		if (s[i] == '-') {
			if (i == 0 || i == s.length() - 1) return false;
			if (counter == 1) return false;
			p1 = i;
			counter++;
		}
	}
	if (counter != 1) return false;

	counter = 0;
	string a[2];
	for (int i = 0; i < s.length(); i++)
		if (i == p1) counter++;
		else a[counter] += s[i];

	counter = (short)stoi(a[0]);
	if (!correctSize(counter,'s')) return false;
	k.first = counter;
	k.second = stoi(a[1]);
	return true;
}


string Reader::readString() {
	string t;
	cout << "> ";
	do	getline(cin, t);
	while (t.empty());
	if (t == "halt") throw 1;
	return t;
}

string Reader::readName() {
	string t;
	bool k;
	do {
		k = false;
		t = readString();
		if (isNotUpperLetter(t[0])) {
			cout << "First symbol has to be uppercase letter." << endl;
			k = true;
		}
		for (int i = 0; i < t.size(); i++) 
			if (isDigit(t[i])) {
				cout << "No digits!" << endl;
				k = true;
				break;
			} else if (t[i] == '|') {
				cout << "The symbol \"|\" is not permitted." << endl;
				k = true;
				break;
			}
	} while (k);
	return t;
}


string Reader::readCity() {
	return readName();
}


int Reader::readInt() {
	string t;
	bool k;
	do {
		k = false;
		t = readString();
		for(int i=0; i<t.length();i++)
			if (!isDigit(t[i])){
				cout << "Only digits!"<<endl;
				k = true;
				break;
			}
	} while (k);
	return stoi(t);
}




bool Reader::read_0_or_1() {
	string p;
	bool m;
	do {
		m = false;
		p = readString();
		if (p != "0" && p != "1") {
			cout << "Incorrect input." << endl;
			m = true;
		}
	} while (m);
	return p == "1";
}



double Reader::readDouble() {
	string t;
	bool k;
	bool r = false;
	do {
		k = false;
		t = readString();
		for (int i = 0; i < t.length(); i++) {
			if (t[i] == ',') t[i] = '.';
			if (!isDigit(t[i]) && t[i] != '.') {
				cout << "Only digits and point!" << endl;
				k = true;
				break;
			} else if(t[i]=='.'){
				if (r) {
					cout << "Too many points!" << endl;
					k = true;
					break;
				} else r=true;
			}
		}
	} while (k);
	return stod(t);
}


int Reader::readCapacity() {
	int a;
	do {
		a = readInt();
		if (a == 0) cout << "No zeroes please." << endl;
	} while (a == 0);
	return a;
}




bool Reader::correctSize(int a, char b) {
	if (b == 's') {               // s for shoes
		if (a > 22 && a < 55) return true;
	} else if(b == 'c') {	      // c for clothes' size
		if (a > 33 && a < 66) return true;
	} else if(b == 'C') {	      // C for clothes' height
		if (a > 99 && a < 201) return true;
	}
	return false;
}



int Reader::readInteractionBase() {
	do {
		string p = readString();
		for (int i = 0; i < p.length(); i++)
			p[i] = toupper(p[i]);
		if (p == "EXIT") return 0;
		if (p == "QUIT") return 0;
		if (p == "Q") return 0;
		if (p == "E") return 0;
		if (p == "0") return 0;

		if (p == "LIST") return 1;
		if (p == "SHOW") return 1;
		if (p == "ALL") return 1;
		if (p == "SHOW ALL") return 1;
		if (p == "LIST ALL") return 1;
		if (p == "1") return 1;

		if (p == "FIND") return 2;
		if (p == "SEARCH") return 2;
		if (p == "GOOGLE") return 2;
		if (p == "2") return 2;

		if (p == "ADD") return 3;
		if (p == "APPEND") return 3;
		if (p == "3") return 3;

		if (p == "DELETE") return 4;
		if (p == "4") return 4;

		if (p == "SORT BY NAME") return 5;
		if (p == "SORT NAME") return 5;
		if (p == "NAME") return 5;
		if (p == "5") return 5;

		if (p == "SORT BY CAPACITY") return 6;
		if (p == "SORT CAPACITY") return 6;
		if (p == "CAPACITY") return 6;
		if (p == "6") return 6;

		if (p == "SAVE") return 7;
		if (p == "7") return 7;

		if (p == "EXTRACT") return 8;
		if (p == "8") return 8;

		if (p == "HELP") {
			helpBase();
			continue;
		}

		return 78;
	} while (true);
}


void Reader::helpBase() {
	cout << "This is your base manager helper" << endl;
	cout << "If you need to exit, type EXIT or QUIT" << endl;
	cout << "If you need to list all positions, type LIST or SHOW" << endl;
	cout << "If you need to find a position, type SEARCH or FIND" << endl;
	cout << "If you need to add a position, type ADD" << endl;
	cout << "If you need to delete a position, type DELETE" << endl;
	cout << "If you need to sort positions by name, type NAME" << endl;
	cout << "If you need to sort positions by capacity, type CAPACITY" << endl;
	cout << "If you need to save database, type SAVE" << endl;
	cout << "If you need to sort extract some positions and form a new database, type EXTRACT" << endl;
}

int Reader::readInteraction() {
	do {
		string p = readString();
		for (int i = 0; i < p.length(); i++)
			p[i] = toupper(p[i]);
		if (p == "EXIT") return 0;
		if (p == "QUIT") return 0;
		if (p == "Q") return 0;
		if (p == "E") return 0;
		if (p == "0") return 0;

		if (p == "LIST") return 1;
		if (p == "SHOW") return 1;
		if (p == "ALL") return 1;
		if (p == "SHOW ALL") return 1;
		if (p == "LIST ALL") return 1;
		if (p == "1") return 1;

		if (p == "ADD") return 2;
		if (p == "CREATE") return 2;
		if (p == "2") return 2;

		if (p == "INTERACT") return 3;
		if (p == "READ") return 3;
		if (p == "OPEN") return 3;
		if (p == "3") return 3;

		if (p == "DELETE") return 4;
		if (p == "4") return 4;

		if (p == "HELP") {
			helpMain();
			continue;
		}

		return 78;
	} while (true);

}


void Reader::helpMain() {
	cout << "This is your helper" << endl;
	cout << "If you need to exit, type EXIT or QUIT" << endl;
	cout << "If you need to list all bases, type LIST or SHOW" << endl;
	cout << "If you need to add a database, type ADD or CREATE" << endl;
	cout << "If you need to interact with certain database, type INTERACT or READ" << endl;
	cout << "If you need to delete a databse, type DELETE" << endl;
	}

