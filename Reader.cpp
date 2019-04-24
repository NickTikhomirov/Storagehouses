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
	if (counter < 25) return false;
	k.first = counter;
	k.second = stoi(a[1]);
	return true;
}


string Reader::readString() {
	string t;
	cout << "> ";
	do	getline(cin, t);
	while (t.empty());
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