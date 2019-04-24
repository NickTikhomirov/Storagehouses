#include "ClothesDataPiece.h"
#include <string>

using std::string;
using std::stoi;


//Всё описано в заголовочном файле

bool ClothesDataPiece::operator<(const ClothesDataPiece& a) const {
	return size < a.getSize();
}

ClothesDataPiece::ClothesDataPiece()
{
	size = 0;
	height = 0;
	amount = 0;
}


ClothesDataPiece::~ClothesDataPiece()
{
}

void ClothesDataPiece::setAmount(int a) { amount = a; }
void ClothesDataPiece::setHeight(short a) { height = a; }
void ClothesDataPiece::setSize(short a) { size = a; }
short ClothesDataPiece::getSize() const noexcept { return size; }
short ClothesDataPiece::getHeight() const noexcept { return height; }
int ClothesDataPiece::getAmount() const noexcept { return amount; }




bool ClothesDataPiece::isCharAllowed(char r) {
	if (r >= '0' && r <= '9') return true;
	if (r == '-') return true;
	return false;
}


bool ClothesDataPiece::tryToFill(string s) {
	short p1 = 0;
	short p2 = 0;
	short counter = 0;

	if (s.length() < 5) return false;
	for (int i = 0; i < s.length(); i++) {
		if (!isCharAllowed(s[i])) return false;
		if (s[i] == '-') {
			if (i == 0 || i == s.length() - 1) return false;
			if (s[i - 1] == '-') return false;
			counter++;
			if (p1 == 0) p1 = i;
			else p2 = i;
		}
	}
	if (counter != 2) return false;
	
	counter = 0;
	string a[3];
	for (int i = 0; i < s.length(); i++)
		if (i == p1 || i == p2) counter++;
		else a[counter] += s[i];

	counter = (short)stoi(a[0]);
	if (counter < 25) return false;
	size = counter;
	counter = (short)stoi(a[1]);
	if (counter < 30) return false;
	height = counter;
	amount = stoi(a[2]);
	return true;
}