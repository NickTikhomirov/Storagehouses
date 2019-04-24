#pragma once
#include <string>
#include "ClothesDataPiece.h"

using std::string;
using std::pair;


//����� ��� ������ � �������
class Reader
{
public:
	//������ ��������, ������� ����, ����� ���� � �++ � ��� ����� �������������, �� ��� ������� ����
	static bool isDigit(char);
	static bool isLowerLetter(char);
	static bool isNotUpperLetter(char);
	static bool checkStringTxt(string); //���������, ����� ������ ������������� �� .txt


	static string readString();		//������ ������ string � ���������� 
	static int readInt();			//������ �������������� � ����������
	static double readDouble();		//������ �������� � ����������

	static string readCity();		//������ �������� ������
	static string readName();		//������ �������� ������
	static int readCapacity();		//������ ��������������� ������
	static bool read_0_or_1();		//������ ����������� �������� (0 ��� 1)
	static bool readDataForType_shoes(string, pair<short, int>&); //������ std::pair<short,int>
	static bool isCharFromSizeString(char); //��������� ������, ����� �� ��� 0....9 ��� -
	static void fixstring(string&); //���������� � ������ .txt, ���� ����
};

