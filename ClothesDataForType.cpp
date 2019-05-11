#pragma once
#include "ClothesDataForType.h"
#include "ClothesDataPiece.h"
#include <iostream>
#include "Reader.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

#define SMALL_CLOTHES 41


//Всё в заголовочном файле

void ClothesDataForType::addPosition(ClothesDataPiece p) { data.insert(p); }

bool ClothesDataForType::hasSmallSizes() const {
	if (data.size() == 0) return false;
	for (const ClothesDataPiece& p : data) {
		if (p.getSize() < SMALL_CLOTHES && p.getAmount() > 0)
			return true;
	}
	return false;
}


int ClothesDataForType::countAmount() const noexcept {
	int result = 0;
	for (const ClothesDataPiece& p : data)
		result += p.getAmount();
	return result;
}



void ClothesDataForType::rm(){
	data.clear();
}

string ClothesDataForType::fileFill() const noexcept {
	string n;
	char r;
	short t;
	for (auto& i : data) {
		n += to_string(i.getAmount());
		r = i.getSize() - 35 + 'A';
		t = i.getHeight() - 100;
		if (t % 2) r = tolower(r);
		t = t / 2;
		n+=r;
		n+=(t + 'A');
	}
	return n;
}

int ClothesDataForType::setSize() const noexcept { return data.size(); }


void ClothesDataForType::cutFromString(string& s) {
	int i;
	string t;
	char c1,c2;
	ClothesDataPiece p;
	while (Reader::isDigit(s[0])) {
		i = 0;
		while (Reader::isDigit(s[i])) i++;
		i++;
		t = s.substr(0, i-1);
		c1 = s[i-1];
		c2 = s[i];
		p.setAmount(stoi(t));
		if (Reader::isLowerLetter(c1)) {
			p.setSize((short)(c1 - 'a') + 35);
			p.setHeight(((short)(c2 - 'A'))*2 + 101);
		} else {
			p.setSize((short)(c1 - 'A') + 35);
			p.setHeight(((short)(c2 - 'A')) * 2 + 100);
		}
		data.insert(p);
		s = s.substr(i + 1, s.length() - i - 1);
		if (s.empty()) break;
	}
}

void ClothesDataForType::contOut() const noexcept {
	for (const auto& pp : data)
		cout << "    S:" << pp.getSize() <<"::"<< pp.getHeight()<< " x" << pp.getAmount() << endl;
}
