#pragma once
#include <iostream>
#include <string>
class DBRecord {
private:
	std::string plaintext; //строка
	//данные из БД
	std::string name;
	std::string surname;
	std::string passport;
public:
	//объявление конструкторов и деструктора
	DBRecord();

	//конструктор, который создаст запись с данными из БД
	DBRecord(std::string name, std::string surname, std::string passport);
	DBRecord(std::string c); //создаёт запись из строки
	~DBRecord();
	
	std::string GetSecondName(); // получает фамилию из записи
	void print(); //выводит запись в консоль
};