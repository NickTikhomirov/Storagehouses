#pragma once
#include <string>

using std::string;


//� ������ ������� ����� ����� ��� ������ � ����, � ������ ��� �� ����� ����������
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
	
	bool tryToFill(string);							//������ ��� ������ ���� "������-����-����������"
	bool operator<(const ClothesDataPiece&) const;  //��������� ����������. ������� ��� ������-�� ����������, ��� �� ����� �����
};

