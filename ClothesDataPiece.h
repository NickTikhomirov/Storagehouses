#pragma once
#include <string>

using std::string;


//” одежды слишком много полей дл€ записи в пару, а кортеж мне не очень понравилс€
class ClothesDataPiece
{
	static bool isCharAllowed(char);
	short size;
	short height;
	int amount;
public:
	ClothesDataPiece();
	~ClothesDataPiece();

	void setSize(short);
	void setHeight(short);
	void setAmount(int);
	short getSize() const noexcept;
	short getHeight() const noexcept;
	int getAmount() const noexcept;
	
	bool tryToFill(string);							//ѕарсер дл€ строки вида "размер-рост-количество"
	bool operator<(const ClothesDataPiece&) const;  //—равнение перегрузил. ѕросили дл€ какого-то контейнера, уже не помню точно
};

