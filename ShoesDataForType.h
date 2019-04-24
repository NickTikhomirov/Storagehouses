#pragma once
#include <unordered_map>
#include <string>
#include <ostream>


using std::unordered_map;
using std::pair;
using std::string;

//� ������ ������ ����� ���� ����� ������ �����. ������ ����� ������������� ��� ����� ��� ������ � unordered map-�� ������
class ShoesDataForType {
	unordered_map<short, int> data;
public:
	//���������� �������� - 2 �����
	void addPosition(short size, int amount);
	void addPosition(pair<short,int>);
	
	bool hasSmallSizes() const;			//�������� �� ����� �������. ���������� ��������� �� ������ ������ �����
	void contOut() const noexcept;		//����� ��������� ������
	int countAmount() const noexcept;	//�������, ������� ����� �� ��� ��������, ��� ����� ��� �������� ����� ������������� ������
	void rm();							//������
	string fileFill() const noexcept;   //�������� ������ � ������, ������� ������� ���� - � ��� � ���������� � ����
	int mapSize() const noexcept;       //������ ����������
	void cutFromString(string&);		//��������� ������ ������� � ���� ������ � ���������� ������ ����
};