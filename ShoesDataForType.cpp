#include <iostream>
#include <ostream>
#include "Reader.h"
#include "ShoesDataForType.h"


using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::to_string;

using std::ostream;


#define SMALL_SHOES 37

//В основном, всё описано в заголовочном файле


void ShoesDataForType::addPosition(pair<short, int> p) {
	addPosition(p.first,p.second);
}


void ShoesDataForType::addPosition(short size, int amount) {
	if (amount >= 0) {
		auto searcher = data.find(size);
		if (searcher == data.end())
			data.insert(make_pair(size, amount));
		else (*searcher).second += amount;
	}
}




bool ShoesDataForType::hasSmallSizes() const {
	if (data.size() == 0) return false;
	for (const pair<short, int>& p : data)
		if (p.first < SMALL_SHOES) 	return true;
	return false;
}



void ShoesDataForType::contOut() const noexcept{
	for (const pair<short, int>& pp : data)
		cout << "    S:" << pp.first << " x" << pp.second << endl;
}


int ShoesDataForType::countAmount() const noexcept {
	int result = 0;
	for (const pair<short, int>& p : data)
		result += p.second;
	return result;
}

void ShoesDataForType::rm(){
	data.clear();
}

string ShoesDataForType::fileFill() const noexcept{
	string n;
	for(const pair<short,int>& i : data) {
		n += to_string(i.second);
		n+= (i.first - 25 + 'A');
	}
	return n;
}


int ShoesDataForType::mapSize() const noexcept { return data.size(); }

//Не очень простой метод, который вызывается другим не очень простым методом из StorageShoes. Результат - строку разбирают на данные 
void ShoesDataForType::cutFromString(string &s) {
	int i;
	string t;
	char c;
	pair<short, int> p;
	while (Reader::isDigit(s[0])) {
		i = 0;
		while (Reader::isDigit(s[i])) i++;
		t = s.substr(0, i);
		c = s[i];
		p.second = stoi(t);
		p.first = (short)(c - 'A') + 25;
		data.insert(p);
		s = s.substr(i + 1, s.length() - i - 1);
		if (s.empty()) break;
	}
}