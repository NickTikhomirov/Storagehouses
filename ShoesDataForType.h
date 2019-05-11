#pragma once
#include <unordered_map>
#include <string>
#include <ostream>


using std::unordered_map;
using std::pair;
using std::string;

//В каждом складе обуви есть обувь разных марок. Каждой марке соответствует вот такой вот монстр с unordered map-ой внутри
class ShoesDataForType {
	unordered_map<short, int> data;
public:
	//Добавление элемента - 2 штуки
	void addPosition(short size, int amount);
	void addPosition(pair<short,int>);
	
	bool hasSmallSizes() const;		//Проверка на малые размеры. Вызывается проверкой из класса склада обуви
	void contOut() const noexcept;		//Вывод подробных данных
	int countAmount() const noexcept;	//Считаем, сколько места мы тут занимаем, это нужно для подсчёта общей загруженности склада
	void rm();				//Чистка
	string fileFill() const noexcept;   	//Собирает данные в строку, которую передаёт выше - а там её записывают в файл
	int mapSize() const noexcept;       	//Размер контейнера
	void cutFromString(string&);		//Разбирает строку обратно в кучу данных и складывает внутрь себя
};
