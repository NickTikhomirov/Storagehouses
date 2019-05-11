#include <iostream>
#include "Storage.h"

using std::endl;
using std::cout;



Storage::Storage(){
	capacity = 0;
}
Storage::~Storage(){}



//Блок сеттеров и геттеров
void Storage::setName(string a) {name = a;}
void Storage::setCity(string a) {city = a;}
void Storage::setCapacity(int a) {capacity = a;}
string Storage::getName()const noexcept {return name;}
string Storage::getCity()const noexcept {return city;}
int Storage::getCapacity()const noexcept {return capacity;}


//Классический вывод
void Storage::consOut()const noexcept {
	cout << "__Storehouse__" << endl;
	cout << "Name: " << getName() << endl;
	cout << "City: " << getCity() << endl;
	cout << "Capacity: " << getCapacity() << endl;
	cout << "Place left:" << endl;
	cout << "   Absolute: " << capacityLeft() << endl;
	cout << "   Relative: " << capacityLeftPerc()<<"%" << endl;
	cout << "Has ";
	if (!hasSmallSizes()) cout << "no ";
	cout << "small sizes" << endl;

}


//Однострочный вывод
void Storage::shortOut() const noexcept {
	cout << getName() << " - " << getCity() << " (" << getCapacity() << ")" << endl;
}


//У потомков это подробный вывод. У родительского класса это просто зеркало классического
void Storage::contOut()const noexcept {consOut();}


double Storage::capacityLeftPerc() const noexcept {
	return 100.0* capacityLeft() / getCapacity();
}


bool Storage::compare(Storage* arg, char style) const noexcept {
	if (style == '0') {
		return (getName() < arg->getName());
	}
	if (style == '1') {
		return (getCapacity() < arg->getCapacity());
	}
}
