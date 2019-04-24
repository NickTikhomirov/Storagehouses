#pragma once
#include <iostream>
using std::string;


//����� - ����������� �����
class Storage{
	//����� ��� ���� ����
	string name;
	string city;
	int capacity;

public:	
	Storage();
	virtual ~Storage();
	virtual void destroy()=0;

	//�������-�������
	void setName(string a);
	void setCity(string a);
	void setCapacity(int a);
	string getName()const noexcept;
	string getCity()const noexcept;
	int getCapacity()const noexcept;

	//�������� ������ - ������������ ��� ������ �� �����
	virtual void stringParser(string) = 0;

	//��������� ������ ������� �� ����� - �������, ���������� (�� ���� ����������) � ������� (� ���� �������)
	virtual void consOut()const noexcept;
	virtual void contOut()const noexcept;
	virtual void shortOut()const noexcept;

	//������ � ����
	virtual string filePut() const noexcept = 0;
	//�����, ������� ���������� ���������� ��� ���������� � ���������� ���������� �����
	virtual void addData() = 0;

	//"����������, ��������������� ���������"
	virtual int capacityLeft()const noexcept = 0;
	double capacityLeftPerc() const noexcept;
	virtual bool hasSmallSizes()const noexcept = 0;

	//���������� ���� ���������, ������������ ��� ����������. ����� �������� �� �������� ���������
	bool compare(Storage* arg, char style) const noexcept;
	
};