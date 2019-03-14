#include <iostream>
#include <string>
#include "DBRecord.h"


DBRecord::DBRecord() {

}

DBRecord::DBRecord(std::string name, std::string surname, std::string passport) {
	
	plaintext = new char[256]; //иницилизируем динамический массив
	
	//обозначим первый символ концом строки, значит она пустая
	plaintext[0] = '\0'; 
	 
	//this - указатель на адрес объекта класса, который указывает в какие элементы объекта надо внести данные
	this->name = name; //копирует имя
	this->surname = surname; //копирует фамилию
	this->passport = passport; //копирует паспорт
}

DBRecord::DBRecord(std::string c) {

	plaintext = c;
}

void DBRecord:: print() {
	
	std::cout << plaintext << std::endl; //вывод строки
	std::cout << name << std::endl;
	std::cout << surname << std::endl;
	std::cout << passport << std::endl;
}

std::string DBRecord::GetSecondName() {
	return surname;
}

DBRecord::~DBRecord() {

}
