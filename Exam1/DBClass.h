#pragma once
#include "DBRecord.h"

#include <vector>

class DBClass
{
private:
	std::vector <DBRecord> db;
public:
	//объявляем конструктор и деструктор
	DBClass();
	~DBClass();

	//метод расшифровки и загрузки записей из файла
	//также проверяет существует ли файл
	int load(const char * filename, const char * key);
	
	//добавляет запись в БД
	int add(const char * name, const char * second_name, const char * passport);

	//ищёт запись по фамилии
	int find(const char *secondname);

	//выводит в консоль данные из БД
	void printAll();

};