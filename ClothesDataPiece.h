#pragma once
#include <string>

using std::string;


//У одежды слишком много полей для записи в пару, а кортеж мне не очень понравился
class ClothesDataPiece
{
	
public:
	short size;
	short height;
	int amount;
	ClothesDataPiece();
	~ClothesDataPiece();

	void setSize(short);
	void setHeight(short);
	void setAmount(int);
	short getSize() const noexcept;
	short getHeight() const noexcept;
	int getAmount() const noexcept;
	
	bool tryToFill(string);							//Парсер для строки вида "размер-рост-количество"
	bool operator<(const ClothesDataPiece& a) const noexcept;
};

