#pragma once
#include <set>
#include <string>
#include <ostream>
#include "ClothesDataPiece.h"

using std::ostream;
using std::set;
using std::string;


//јналогично ShoesDataForType, только дл€ одежды - даже методы такие же
class ClothesDataForType {
	set<ClothesDataPiece> data;
public:
	void contOut() const noexcept;
	void addPosition(ClothesDataPiece);
	bool hasSmallSizes() const;
	int countAmount() const noexcept;
	void rm();
	string fileFill() const noexcept;
	int setSize() const noexcept;	//Ќе "установить размер", а "получить размер сета"
	void cutFromString(string& );
};
