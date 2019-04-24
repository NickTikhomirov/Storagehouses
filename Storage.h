#pragma once
#include <iostream>
using std::string;


//Склад - абстрактный класс
class Storage{
	//Общие для всех поля
	string name;
	string city;
	int capacity;

public:	
	Storage();
	virtual ~Storage();
	virtual void destroy()=0;

	//Сеттеры-геттеры
	void setName(string a);
	void setCity(string a);
	void setCapacity(int a);
	string getName()const noexcept;
	string getCity()const noexcept;
	int getCapacity()const noexcept;

	//Нарезает строку - используется при чтении из файла
	virtual void stringParser(string) = 0;

	//Несколько разных выводов на экран - обычный, развёрнутый (со всем содержимым) и краткий (в одну строчку)
	virtual void consOut()const noexcept;
	virtual void contOut()const noexcept;
	virtual void shortOut()const noexcept;

	//Запись в файл
	virtual string filePut() const noexcept = 0;
	//Метод, который наследники используют для заполнения с клавиатуры оставшихся полей
	virtual void addData() = 0;

	//"Функционал, предусмотренный вариантом"
	virtual int capacityLeft()const noexcept = 0;
	double capacityLeftPerc() const noexcept;
	virtual bool hasSmallSizes()const noexcept = 0;

	//Сравннение двух элементов, используется для сортировки. Стиль отвечает за критерий сравнения
	bool compare(Storage* arg, char style) const noexcept;
	
};