#pragma once
#include <vector>
#include "Storage.h"
#include <vector>

using std::string;
using std::vector;


//���� ������
class DataBase{
	string name;
	void uniteSort(DataBase& tt1, DataBase& tt2, char style);  //��������������� ����� ��� ����������
	int countActive() const noexcept;						   //�������� ������ �������
	void extractByRule(char, DataBase&) const noexcept;		   //��� ������������ ����� ��� ������
	bool getNameAndCity(string,string) const noexcept;		   //���������, �� ���� �� ������������ ��������� ���-�����, ������� ��� ����
public:
	vector<Storage*> data;
	void addItem(Storage*);		//�����-�� �������� ������� � public-���� ����� �����

	//������ � ������ ���� ������. � �������� ���������� ������ � Reader
	void setName(string);
	string getName() const noexcept;
	bool checkName() const noexcept;
	void fixName();

	void changeBaseInterface(); //���� ������ � ����� ������
	
	void readFromFile();		//������ �� �����
	void consOut() const noexcept; //����� �� ����� �����������
	void save();				//������ � ����

	void sort_this(char style);			//���������� �� ��������
	void getElementFromUser();			//���������� ������ �������� � ��������� � ����������

	bool deletePosition(string,string);	//�������� � ����������� ������� ��������� ���������
};

