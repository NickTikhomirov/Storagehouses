#pragma once
#include <vector>
#include "Storage.h"
#include <vector>

using std::string;
using std::vector;


//База данных
class DataBase{
	string name;
	void uniteSort(DataBase& tt1, DataBase& tt2, char style);  //Вспомогательный метод для соритровки
	int countActive() const noexcept;						   //Уточняет размер вектора
	void extractByRule(char, DataBase&) const noexcept;		   //Для формирования новых баз данных
	bool getNameAndCity(string,string) const noexcept;		   //Проверяет, не ввел ли пользователь сочетание имя-город, которое уже есть
public:
	vector<Storage*> data;
	void addItem(Storage*);		//Зачем-то добавляю элемент в public-поле через метод

	//Работа с именем базы данных. В основном функционал перенёс в Reader
	void setName(string);
	string getName() const noexcept;
	bool checkName() const noexcept;
	void fixName();

	void changeBaseInterface(); //Меню работы с базой данных
	
	void readFromFile();		//Чтение из файла
	void consOut() const noexcept; //Вывод на экран содержимого
	void save();				//Запись в файл

	void sort_this(char style);			//Сортировка по принципу
	void getElementFromUser();			//Добавление нового элемента в контейнер с клавиатуры

	bool deletePosition(string,string);	//Удаление с сохранением порядка остальных элементов
};

