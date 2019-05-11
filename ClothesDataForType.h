#pragma once
#include <set>
#include <string>
#include <ostream>
#include "ClothesDataPiece.h"

using std::ostream;
using std::multiset;
using std::string;


//Аналогично ShoesDataForType, только для одежды - даже методы такие же
class ClothesDataForType {
	multiset<ClothesDataPiece> data;
public:
	void contOut() const noexcept;
	void addPosition(ClothesDataPiece);
	bool hasSmallSizes() const;
	int countAmount() const noexcept;
	void rm();
	string fileFill() const noexcept;
	int setSize() const noexcept;	//Не "установить размер", а "получить размер сета"
	void cutFromString(string& );
};
