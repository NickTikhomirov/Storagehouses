#pragma once
#include <unordered_map>
#include "Storage.h"
#include "ClothesDataForType.h"

using std::unordered_map;


//����� ������
class StorageClothes:public Storage{
	unordered_map<string, ClothesDataForType> contents;
public:
	~StorageClothes();
	void destroy();             //�������� ����� ����� ���� � ������ � ������ �����. ����� ������ ������ ��������� ��� ������ ��-������

	void consOut() const noexcept;
	void contOut() const noexcept;

	int capacityLeft() const noexcept;
	bool hasSmallSizes() const noexcept;
	string filePut()const noexcept;
	void addData();
	void stringParser(string);
};

