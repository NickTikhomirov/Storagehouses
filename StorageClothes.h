#pragma once
#include <unordered_map>
#include "Storage.h"
#include "ClothesDataForType.h"

using std::unordered_map;


//Склад одежды
class StorageClothes:public Storage{
	unordered_map<string, ClothesDataForType> contents;
public:
	~StorageClothes();
	void destroy();             //Описания всего этого есть в складе и складе обуви. Склад одежды просто реализует эти методы по-своему

	void consOut() const noexcept;
	void contOut() const noexcept;

	int capacityLeft() const noexcept;
	bool hasSmallSizes() const noexcept;
	string filePut()const noexcept;
	void addData();
	void stringParser(string);
};

