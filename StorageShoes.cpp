#include <iostream>
#include <fstream>
#include <ios>
#include <algorithm>
#include "StorageShoes.h"
#include "Reader.h"

using std::cout;
using std::endl;
using std::cin;
using std::pair;
using std::make_pair;

using std::to_string;
using std::stoi;

using std::ofstream;



//јналогично складу одежды, но немного иначе

void StorageShoes::destroy() {
	string t;
	setName(t);
	setCity(t);
	setCapacity(0);
	for (auto& d : contents) d.second.rm();
	Storage::~Storage();
}

StorageShoes::StorageShoes(){}
StorageShoes::~StorageShoes(){
	destroy();
}




void StorageShoes::consOut() const noexcept {
	Storage::consOut();
	cout << "Type: Shoes" << endl;
}



void StorageShoes::contOut() const noexcept {
	consOut();
	cout << "Contents:" << endl;
	for (const pair<string, ShoesDataForType>& p : contents) {
		cout << "  Name: " << p.first << endl << "  Statistics:" << endl;
		p.second.contOut();
	}
}



int StorageShoes::capacityLeft() const noexcept {
	int counter = 0;
	for (const pair<string, ShoesDataForType> &p : contents)
		counter += p.second.countAmount();
	return getCapacity() - counter;
}



bool StorageShoes::hasSmallSizes() const noexcept {
	if (contents.size() == 0) return false;
	for (const pair<string, ShoesDataForType>& p : contents) {
		if (p.second.hasSmallSizes())
			return true;
	}
	return false;
}


string StorageShoes::filePut() const noexcept{
	string n = getName();
	n[0] = std::tolower(n[0]);
	n += to_string(getCapacity());
	n += getCity();
	n += "|";
	for (auto& r : contents) {
		n+=r.first;
		n+=r.second.fileFill();
	}
	return n;
}



void StorageShoes::addData() {
	string t, t1;
	int c = capacityLeft();
	bool p = false;
	cout << "Hello, this is user-friendly interface for data adding" << endl;
	cout << "You may leave whenever you want, just type \"e\"." << endl;
	cout << "If you want to exit with saving your progress, type \"s\"." << endl;
	cout << "By the way, this means you can\'t name your shoes with one of these two letters without adding anything else, sorry" << endl;
	do {
		do {
			cout << "Give me type of shoes:";
			cin >> t;
			if (t == "e" || t == "s") return;
			if (contents.find(t) != contents.end()) cout << "This type already exists." << endl;
			else p = true;
		} while (!p);
		ShoesDataForType d;
		cout << "The storagehouse has " << c << " units of free space." << endl;
		cout << "Give me sizes and amounts (format: \"size-amount\"): " << endl;
		cout << "If you want to stop giving information for this type and add another type with information, type \"n\"." << endl;
		do {
			cin >> t1;
			if (t1 == "e") return;
			if (t1 == "s") break;
			pair<short, int> r;
			if (t1 != "s" && t1 != "n") {
				if (!Reader::readDataForType_shoes(t1, r)) cout << "Incorrect input!";  //«десь строка данных по марке обуви режетс€ методом из Reader
				else  if (c < r.second) cout << "Not enough place" << endl;
				else {
					d.addPosition(r);
					c -= r.second;
					cout << "Capacity left: " << c << endl;
				}
			}
		} while (t1 != "s" && t1!="n");
		if (d.mapSize() > 0) {
			contents.insert(make_pair(t, d));
			cout << "The information was saved in the sessionary version of the database. Do not forget to save the database before exiting" << endl;
		}
	else cout << "No information was given. No saving." << endl;
	} while (t1!="s");
}



void StorageShoes::stringParser(string p) {
	p[0] = toupper(p[0]);
	int aa[3];
	aa[0] = aa[1] = aa[2] = 0;
	int a = 0;
	for (int i = 1; i < p.length(); i++) {
		if (Reader::isDigit(p[i]) && a==0) {
			aa[a] = i;
			a++;
		} else if(!Reader::isDigit(p[i]) && a==1){
			aa[a] = i;
			a++;
		} else if(p[i]=='|' && a==2){
			aa[a] = i;
			if (i != p.length() - 1) {
				a = 0;
				break;
			}
		}
	}
	setName(p.substr(0, aa[0]));
	setCapacity(stoi(p.substr(aa[0], aa[1] - aa[0])));
	setCity(p.substr(aa[1], aa[2]-aa[1]));
	if (a == 0) {
		string p1;
		ShoesDataForType p2;
		p = p.substr(aa[2] + 1, p.length() - aa[2] - 1);
		while (!p.empty()) {
			a = 0;
			while (!Reader::isDigit(p[a])) a++;
			p1 = p.substr(0, a);
			p = p.substr(a, p.length() - a);
			p2.cutFromString(p);
			contents.insert(make_pair(p1,p2));
		}
	}
}