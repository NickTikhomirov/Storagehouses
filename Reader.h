#pragma once
#include <string>
#include "ClothesDataPiece.h"

using std::string;
using std::pair;


//Класс для чтения с консоли
class Reader
{
public:
	//Всякие проверки, которые даже, вроде есть в с++ и без моего вмешательства, но мне хочется свои
	static bool isDigit(char);
	static bool isLowerLetter(char);
	static bool isNotUpperLetter(char);
	static bool checkStringTxt(string); 	//Проверяет, чтобы строка заканчивалась на .txt


	static string readString();		//Чтение строки string с клавиатуры 
	static int readInt();			//Чтение целочисленного с клавиатуры
	static double readDouble();		//Чтение дробного с клавиатуры

	static string readCity();		//Чтение названия города
	static string readName(bool onlycaptals=true);		//Чтение названия склада
	static int readCapacity();		//Чтение вместительности склада
	static bool read_0_or_1();		//Чтение логического значения (0 или 1)
	static bool readDataForType_shoes(string, pair<short, int>&); //Чтение std::pair<short,int>
	static bool isCharFromSizeString(char); //Проверяет символ, чтобы он был 0....9 или -
	static void fixstring(string&); 	//дописывает к строке .txt, если надо
	
	static int readInteractionBase();  	//Чтение действия пользователя с базой данных
	static void helpBase();			//Справка по командам в базе данных
	static int readInteraction();		//Чтение действия пользователя в основном меню
	static void helpMain();			//Справка по командам в основном меню
	static bool correctSize(int, char);     //Проверка на правильность ввода размера обуви/одежды
};
