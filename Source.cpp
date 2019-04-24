#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <experimental/filesystem>
#include <fstream>
#include <cstdio>

#include "Storage.h"
#include "StorageShoes.h"
#include "StorageClothes.h"
#include "DataBase.h"
#include "Reader.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;

using std::map;
using std::vector;
using std::set;

using std::tuple;
using std::pair;

using std::ofstream;
using std::ifstream;
using std::remove;



using std::experimental::filesystem::path;
using std::experimental::filesystem::directory_entry;

using std::experimental::filesystem::exists;
using std::experimental::filesystem::create_directory;
using std::experimental::filesystem::directory_iterator;
using std::experimental::filesystem::current_path;


//������� � �������������. ���������� - ���� ������.
void textInteraction(){
	cout << "What do you want to do?"<<endl;
	cout << "0. Exit" << endl;
	cout << "1. Get bases list" << endl;
	cout << "2. Add new base" << endl;
	cout << "3. Interact with existing base"<< endl;
	cout << "4. Delete existing base" << endl;

}



//����� ������ ���. ������ ����������� - ������ ����������� filesystem library.
void list_bases(path ourDirectory){
	bool f = false;
	for (auto& p : directory_iterator(ourDirectory))
		if (Reader::checkStringTxt(p.path().string())) {
			cout << p.path().filename() << endl;
			f = true;
		}
	if (!f) cout << "<No bases found>" << endl;
}




int main() {
	short userInput=1;
	DataBase DB;
	path ourDirectory = current_path();
	ourDirectory += "\\server";                                //���� ������ ����� �� ������: "������� ����������/server". ����� ������ ������ ���, ����� ������������� ����. 
	if (!exists(ourDirectory)) create_directory(ourDirectory); //��������������� �������� ����� ����������, ���� � ���

	//�������� ����� ���������. � ���� ����� ������������ ����� ��������� �� ����� � ������.
	while (userInput!=0) {
		textInteraction();
		userInput = Reader::readInt();     //������ ������������� ����� ������ �������� � ������� Reader. ���, �� ����, ������������ cin
		switch (userInput) {
			case 0:{break;}	 //����� �� ���������
			case 1:{	//����� ������ ��� ������
				cout << "List of bases:" << endl;
				list_bases(ourDirectory);
				break;
			}
			case 2:{	 //� ����� �� ������������ ��� ���������� �������� - ��� �������� ����� ���� ������. ������, ����� ������� �����
				string n1;
				cout<<"Give me base's name:";
				cin>>n1;
				Reader::fixstring(n1);    //��� ������� ���������� .txt � ������
				ofstream pe(ourDirectory.string()+'\\'+n1);
				pe << "0";
				pe.close();
				break;
			}
			case 3: {	//������ ���� ������ �� ����� � ��������� �� ������� ���� - ���������� ������ � ������ ������
				string n1;
				cout << "Give me base's name:";
				cin >> n1;
				Reader::fixstring(n1);
				if (exists(*(new path(ourDirectory.string() + '\\' + n1)))) {
					DB.setName(ourDirectory.string() + '\\' + n1);
					DB.readFromFile();
					DB.changeBaseInterface();			//����������, ��� ������� � ������� ����
				} else cout << "No such database"<<endl;
				break;
			}
			case 4: {	//�������� ���� ������
				string n1;
				cout << "Give me base's name:";
				cin >> n1;
				if (!Reader::checkStringTxt(n1)) n1 += ".txt";
				n1 = ourDirectory.string() + '\\' + n1;
				if (exists(*(new path(n1)))) {
					remove(n1.c_str());
					cout << "Deletion success!" << endl;
				}
				else cout << "No such database" << endl;
				break;
			}
			default: {cout << "Unidentified input. Kaput." << endl; }
		}
		cout << endl;
	}
}
