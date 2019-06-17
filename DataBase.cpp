#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "DataBase.h"
#include "StorageClothes.h"
#include "StorageShoes.h"
#include "Reader.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

using std::ifstream;
using std::ofstream;


using std::experimental::filesystem::path;
using std::experimental::filesystem::exists;



bool DataBase::getNameAndCity(string n, string c) const noexcept{
	for (const auto& a : data) {
		if(a!=0)
			if (a->getName() == n)
				if (a->getCity() == c) {
					cout << "This storagehouse already exists! Type different name and city." << endl;
					return false;
				}
	}
	return true;
}






void DataBase::extractByRule(char c, DataBase &a) const noexcept{
	switch (c) {
		case '%': {
			double perc;
			cout << "Give me minimal percent rate of used capacity." << endl;
			perc = Reader::readDouble();
			for (const auto p : data)
				if(p!=0)
					if (p->capacityLeftPerc() < 100 - perc)
						a.addItem(p);
			break;
		}
		case 'n':{
			cout << "Give me storagehouse name:" << endl;
			string n1 = Reader::readName();
			for (const auto p : data)
				if (p != 0)
					if (p->getName() == n1)
						a.addItem(p);
			break;
		}
		case 'c': {
			cout << "Give me city name:" << endl;
			string n1 = Reader::readCity();
			for (const auto p : data)
				if (p != 0)
					if (p->getCity() == n1)
						a.addItem(p);
			break;
		}
	}
}



void DataBase::addItem(Storage *a) {
	int c = countActive();
	if (c == data.size()) data.resize(c + 3);
	data[c] = a;
}


int DataBase::countActive() const noexcept {
	int r = data.size();
	while (r != 0) {
		if (data[r - 1] != 0) break;
		else r -= 1;
	}
	return r;
}

string DataBase::getName() const noexcept{
	return name;
}

void DataBase::setName(string a){
	name = a;
}

bool DataBase::checkName() const noexcept{
	return Reader::checkStringTxt(name);
}


void DataBase::fixName(){
	if (!checkName()) setName(getName()+".txt");
}




void DataBase::sort_this(char style) {
	if (data.size() > 1) {
		DataBase t1, t2;
		t1.data.resize(data.size() / 2);
		t2.data.resize(data.size() / 2 + data.size() % 2);
		for (int i = 0; i < t1.data.size(); i++)
			t1.data[i] = data[i];
		for (int i = t1.data.size(); i < data.size(); i++)
			t2.data[i - t1.data.size()] = data[i];
		t1.sort_this(style);
		t2.sort_this(style);
		uniteSort(t1, t2, style);
	}
}



void DataBase::uniteSort(DataBase& tt1, DataBase& tt2, char style) {
	int i1 = 0;
	int i2 = 0;
	int i = 0;
	while (i1 > -1 || i2 > -1) {
		if (i2 > -1) {
			if (tt1.data[i1]->compare(tt2.data[i2], style)) {
				data[i] = tt1.data[i1];
				i1++;
			}
			else {
				data[i] = tt2.data[i2];
				i2++;
			}
			if (i1 == tt1.data.size()) {
				i1 = i2;
				tt1 = tt2;
				i2 = -1;
			}
			else if (i2 == tt2.data.size()) i2 = -1;
		}
		else {
			data[i] = tt1.data[i1];
			i1++;
			if (i1 == tt1.data.size()) i1 = -1;
		}
		i++;

	}
}

void DataBase::getElementFromUser(){
	string n, c;
	bool t;
	int cap;
	cout<<"Adding new storagehouse in process"<<endl;
	cout<<"Types: 0 = Shoes, 1 = Clothes" << endl;
	cout << "  Type:";       
	t = Reader::read_0_or_1();
	do {
		cout << "  Name:";	
		n=Reader::readName();
		cout << "  City:"; 
		c=Reader::readCity();
	} while (!getNameAndCity(n, c));
	cout<<"  Capacity:";   
	cap = Reader::readCapacity();
	Storage* f=0;
	if(!t){
		StorageShoes* k;
		k = new StorageShoes;
		k->setName(n);
		k->setCity(c);
		k->setCapacity(cap);
		cout << "Now let\'s add some data!" << endl;
		k->addData();
		f = k;
	}
	else {
		StorageClothes* k;
		k = new StorageClothes;
		k->setName(n);
		k->setCity(c);
		k->setCapacity(cap);
		cout << "Now let\'s add some data!" << endl;
		k->addData();
		f = k;
	}
	addItem(f);
}


void DataBase::changeBaseInterface() {
	short p=1;
	do {
		try {
			cout << "Base manager active!" << endl;
			p = Reader::readInteractionBase();
			switch (p) {
			case 1: {
				consOut();
				break;
			}
			case 2: {
				DataBase newBase;
				extractByRule('n', newBase);
				if (newBase.data.empty()) cout << "No storagehouses with this name" << endl;
				else {
					cout << "Results:" << endl;
					for (auto& p1 : newBase.data)
						if (p1 != 0) {
							cout << " >";
							p1->shortOut();
						}
					DataBase secondBase;
					newBase.extractByRule('c', secondBase);
					if (secondBase.data.empty()) cout << "No storagehouses with this city" << endl;
					else {
						cout << "Result:" << endl;
						for (auto& p1 : secondBase.data)
							if (p1 != 0) {
								cout << " >";
								p1->contOut();
							}
					}
				}
				break;
			}
			case 3: {
				getElementFromUser();
				break;
			}
			case 4: {
				string aa, bb;
				cout << "Give me a name of storagehouse you want to delete" << endl;
				aa = Reader::readName();
				cout << "Give me a homecity of storagehouse you want to delete" << endl;
				bb = Reader::readCity();
				if (!deletePosition(aa, bb)) cout << "Good news, there is no storagehouse with these parameters in the database. No deletion required." << endl;
				else cout << "Succesfully deleted!" << endl;
				break;
			}
			case 5: {
				data.resize(countActive());
				sort_this('0');
				cout << "Done sorting by name. Do not forget to save results into database file." << endl;
				break;
			}
			case 6: {
				data.resize(countActive());
				sort_this('1');
				cout << "Done sorting by capacity. Do not forget to save results into database file." << endl;
				break;
			}
			case 7: {
				save();
				cout << "Done saving. Do not forget to... not to delete the .txt file of database." << endl;
				break;
			}
			case 8: {
				string nn, nnn;
				bool l = true;
				cout << "We are going to create a new database. Choose a name" << endl;
				do {
					cin >> nn;
					Reader::fixstring(nn);
					path k(name);
					nnn = k.parent_path().string() + '\\' + nn;
					if (exists(nnn)) cout << "This database already exists!" << endl;
					else l = false;
				} while (l);
				cout << "Do you want to extract by capacity (0) or by city(1)?" << endl;
				bool e_rule = Reader::read_0_or_1();
				DataBase d;
				if (e_rule) extractByRule('c', d);
				else extractByRule('%', d);
				d.setName(nnn);
				cout << "Searching done. Interacting with new database." << endl;
				d.changeBaseInterface();
			}
			}
		}
		catch (int) {
			cout << "You have returned to main page of base manager." << endl;
		}
	} while (p != 0);

}


void DataBase::consOut() const noexcept {
	for (auto& p : data) 
		if (p != 0){
			cout << "====================" << endl;
			p->consOut();
		}

	cout << "====================" << endl;
}

void DataBase::readFromFile() {
	ifstream f(name);
	int a;
	string p;
	f >> a;
	data.resize(a);
	f.ignore();
	for (int i = 0; i < a; i++) {
		getline(f, p);
		if (islower(p[0])) {
			data[i] = new StorageShoes;
			data[i]->stringParser(p);
		} else {
			data[i] = new StorageClothes;
			data[i]->stringParser(p);
		}
	}
	f.close();
}


void DataBase::save(){
	ofstream a(name,std::ios::out);
	a << countActive() << endl;
	for (auto& r : data) {
		if(r!=0)
			a<<r->filePut()<<endl; 
	}
	a.close();
}


bool DataBase::deletePosition(string n, string c) {
	bool sdvig = false;
	for (int i = 0; i < data.size(); i++) {
		if (sdvig == true)
			data[i - 1] = data[i];
		if (data[i] == 0) break;
		if (data[i]->getName() == n && data[i]->getCity() == c) {
			sdvig = true;
			data[i]->destroy();
			delete data[i];
		}
	}
	if (sdvig) data[data.size() - 1] = 0;
	return sdvig;
}
