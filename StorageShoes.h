#pragma once
#include <unordered_map>
#include "ShoesDataForType.h"
#include "Storage.h"
#include <string>

using std::unordered_map;
using std::pair;
using std::string;

//Склад обуви
class StorageShoes: public Storage{
	unordered_map<string, ShoesDataForType> contents;
public:
	StorageShoes();
	~StorageShoes();
	//Очистка полей. Возможно, избыточное действие, но не убирать же его, раз написал
	void destroy();
	
	//Выводы, унаследованные от склада
	void consOut() const noexcept;
	void contOut() const noexcept;

	//Наследство от склада
	int capacityLeft() const noexcept;
	bool hasSmallSizes() const noexcept;
	string filePut() const noexcept;
	void addData();
	void stringParser(string);
};

