#include <iostream>
#include <fstream>
#include "StorageClothes.h"
#include "ClothesDataPiece.h"
#include "Reader.h"

using std::cout;
using std::endl;
using std::cin;
using std::to_string;

using std::pair;
using std::make_pair;

using std::ofstream;


//Чистка полей - просто перестраховка
void StorageClothes::destroy() {
	string t;
	setName(t);
	setCity(t);
	setCapacity(0);
	for (auto& d : contents) d.second.rm();
	Storage::~Storage();
}


StorageClothes::~StorageClothes() {
	destroy();
}


//Выводы - 2 штуки
void StorageClothes::consOut() const noexcept {
	Storage::consOut();
	cout << "Type: Clothes" << endl;
}


void StorageClothes::contOut() const noexcept {
	consOut();
	cout << "Contents:" << endl;
	for (const pair<string, ClothesDataForType>& p : contents) {
		cout << "  Name: " << p.first << endl << "  Statistics:" << endl;
		p.second.contOut();
	}
}




int StorageClothes::capacityLeft() const noexcept {
	int counter = 0;
	for (const pair<string, ClothesDataForType>& p : contents)
		counter += p.second.countAmount();
	return getCapacity() - counter;
}


bool StorageClothes::hasSmallSizes() const noexcept{
	if (contents.size() == 0) return false;
	for (const pair<string, ClothesDataForType>& p : contents)
		if (p.second.hasSmallSizes()) return true;
	return false;
}


string StorageClothes::filePut()const noexcept {
	string n = getName();
	n += to_string(getCapacity());
	n += getCity();
	n += "|";
	for (auto& r : contents) {
		n+=r.first;
		n+=r.second.fileFill();
	}
	return n;
}


//Добавление информации по содержимому склада
void StorageClothes::addData(){
	string t,t1;
	int c = capacityLeft(); //Чтобы не пересчитывать кучу раз оставшееся место, сохраним его
	bool p = false;
	cout << "Hello, this is user-friendly interface for data adding" << endl;
	cout << "You may leave whenever you want, just type \"e\"." << endl;                 //В интерфейсе есть команды, позволяющие с ним взаимодействовать. На словах прогрессивно, на деле - убого
	cout << "If you want to exit with saving your progress, type \"s\"." << endl;
	cout << "By the way, this means you can\'t name your clothes with one of these two letters without adding anything else, sorry" << endl;
	do{			//В силу особенностей условия и огромной вложенности всяких контейнеров, мне приходится крутить много циклов. Выходит тоже убого
		do {
			cout << "Give me type of clothes:";
			cin >> t;
			if (t == "e" || t == "s") return;
			if (contents.find(t) != contents.end()) cout << "This type already exists." << endl;
			else p = true;
		} while (!p);
		ClothesDataForType d;
		cout << "The storagehouse has " << c << " units of free space." << endl;    //На нуле должно бы автоматически выходить, но пусть лучше пользователь сам до этого дойдёт. Должно же быть в программе что-то философское
		cout << "Give me sizes, heights and amounts (format: \"size-height-amount\"): " << endl;   //Не самый идеальный ввод, но хотя бы не столбец чисел - уже спасибо. Парсится строка в классе ClothesDataPiece. Для одежды аналогичный метод живёт в Reader
		cout << "If you want to stop giving information for this type and add another type with information, type \"n\"." << endl;
		do {
			cin >> t1;
			if (t1 == "e") return;
			if (t1 == "s") break;
			ClothesDataPiece r;
			if (t1 != "s" && t1 != "n") {
				if (!r.tryToFill(t1)) cout << "Incorrect input!";
				else if (c < r.getAmount()) cout << "Not enough place" << endl;
				else {
					d.addPosition(r);
					c -= r.getAmount();
					cout << "Capacity left: " << c << endl;
				}
			}
		} while (t1!="s" && t1 != "n");
		if (d.setSize() > 0) {
			contents.insert(make_pair(t,d));
			cout << "The information was saved in the sessionary version of the database. Do not forget to save the database before exiting" << endl;
		} else cout<<"No information was given. No saving."<<endl;
	} while (t1 != "s");
}


//Я сделал весьма специфичный ввод в файл, и обратно читать его с пол-пинка не выходит. Приходится использовать несколько вложенных методов с циклами
void StorageClothes::stringParser(string p) {
	int aa[3];
	aa[0] = aa[1] = aa[2] = 0;
	int a = 0;
	for (int i = 1; i < p.length(); i++) { //Считаем позиции, где надо будет обрезать
		if (Reader::isDigit(p[i]) && a == 0) {
			aa[a] = i;
			a++;
		}
		else if (!Reader::isDigit(p[i]) && a == 1) {
			aa[a] = i;
			a++;
		}
		else if (p[i] == '|' && a == 2) {
			aa[a] = i;
			if (i != p.length() - 1) {
				a = 0;
				break;
			}
		}
	}
	setName(p.substr(0, aa[0]));
	setCapacity(stoi(p.substr(aa[0], aa[1] - aa[0])));
	setCity(p.substr(aa[1], aa[2] - aa[1]));
	if (a == 0) {  //А теперь пошли вырезать содержимое склада из строки
		string p1;
		ClothesDataForType p2;
		p = p.substr(aa[2] + 1, p.length() - aa[2] - 1);
		while (!p.empty()) {
			a = 0;
			while (!Reader::isDigit(p[a])) a++;
			p1 = p.substr(0, a);
			p = p.substr(a, p.length() - a);
			p2.cutFromString(p);
			contents.insert(make_pair(p1, p2));
		}
	}
}