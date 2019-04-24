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
	static bool checkStringTxt(string); //Проверяет, чтобы строка заканчивалась на .txt


	static string readString();		//Чтение строки string с клавиатуры 
	static int readInt();			//Чтение целочисленного с клавиатуры
	static double readDouble();		//Чтение дробного с клавиатуры

	static string readCity();		//Чтение названия города
	static string readName();		//Чтение названия склада
	static int readCapacity();		//Чтение вместительности склада
	static bool read_0_or_1();		//Чтение логического значения (0 или 1)
	static bool readDataForType_shoes(string, pair<short, int>&); //Чтение std::pair<short,int>
	static bool isCharFromSizeString(char); //Проверяет символ, чтобы он был 0....9 или -
	static void fixstring(string&); //дописывает к строке .txt, если надо
};

