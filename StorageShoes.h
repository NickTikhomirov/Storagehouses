#pragma once
#include <unordered_map>
#include "ShoesDataForType.h"
#include "Storage.h"
#include <string>

using std::unordered_map;
using std::pair;
using std::string;

//����� �����
class StorageShoes: public Storage{
	unordered_map<string, ShoesDataForType> contents;
public:
	StorageShoes();
	~StorageShoes();
	//������� �����. ��������, ���������� ��������, �� �� ������� �� ���, ��� �������
	void destroy();
	
	//������, �������������� �� ������
	void consOut() const noexcept;
	void contOut() const noexcept;

	//���������� �� ������
	int capacityLeft() const noexcept;
	bool hasSmallSizes() const noexcept;
	string filePut() const noexcept;
	void addData();
	void stringParser(string);
};

