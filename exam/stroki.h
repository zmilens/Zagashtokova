#pragma once
#include <string.h>
#include <string>

#include <openssl/conf.h>
#include <openssl/evp.h> 
#include <openssl/err.h> 
#include <openssl/aes.h>

class MyString
{
public:
	// Конструкторы

	MyString(); // пустой, создающий строку нулевой длины
	MyString(char c[]); // копирующий из массива char
	MyString(const char* c); // копирующий содержимое из массива *char.
	MyString(std::string str); // копирующий из std∷sting
	MyString(const MyString& s); // копирующий из объекта аналогичного класса

	~MyString(); // Деструктор

	void clear(); // Метод clear(), сбрасывающий длину строки в 0
	void add(const char* c); // Метод add(), складывающий исходную строку со строкой символов *char
	void add(std::string str); // Метод add(), принимающий std::string
	void insert(const char* c, unsigned int index); // Метод insert(), вставляющий строку после опредленной позиции для char*
	void insert(std::string, unsigned int index); // Метод insert(), вставляющий строку после опредленной позиции для std::string
	void cut(unsigned int index, unsigned int count); // Метод cut(), удаляющий опредленное кол-во символов после определенной позиции 

	friend std::ostream& operator<< (std::ostream& so, const MyString& s); // Перезарузка метода для потокового вывода в консоль
	MyString operator+(MyString s); // Перезагрузка оператора сложения

	unsigned char* encrypt(unsigned char* password, unsigned char* iv, int* cr_len); // Зашифровать строку
	void decrypt(unsigned char* crypted, int cr_len, unsigned char* password, unsigned char *iv); // Расшифровать строку

	int find(const char* c); // Метод find(), осуществляющий поиск последовательности символов char*
	int find(std::string str); // Метод find(), осуществляющий поиск строки std::string

	void save(const char* name); // Метод save() для записи в файл
	void load(const char* name); // Метод load() для чтения из файла

private:
	char *plaintext; // Динамический массив символов
	unsigned int lenght; // Длина строки
};
