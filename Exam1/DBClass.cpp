#include <iostream>
#include <openssl/conf.h> // функции, структуры и константы настройки OpenSSL
#include <openssl/conf.h>
#include <openssl/evp.h> // сами криптогрфические функции https://wiki.openssl.org/index.php/EVP
#include <openssl/err.h> // коды внутренних ошибок OpenSSL и их расшифровка
#include <openssl/aes.h>
#include <string>
#include <vector>
#include <fstream>
#include "DBClass.h"
#include <ctype.h>



DBClass::DBClass() {

}

DBClass::~DBClass() {

}

int DBClass::load(const char * filename, const char * key)
{
	unsigned char *crypted = new unsigned char[1000]; // зашифрованная строка
	unsigned char *plaintext = new unsigned char[1000]; // дешифрованная строка
	unsigned char *iv = (unsigned char *)"0123456789012345"; // рандомайзер
	int plaintext_len = strlen((char *)plaintext); // длина строки после обработки
	int len = 0; // Длина строки
	int cr_len = 0; // Длина шифра

	std::fstream in_crypted(filename, std::ios::binary | std::ios::in); // файловый поток
	if (in_crypted.is_open()) { // открываем файл
		in_crypted.read((char*)crypted, 1000); // считываем шифр
		cr_len = in_crypted.gcount(); // получаем кол во считанных символов
		in_crypted.close(); // закрываем файл
	}
	else { // если файл не открылся
		std::cout << "Не удалось открыть или прочитать файл" << std::endl;
		return -1;
	}

	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); // Создание структуры с настройками метода

	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(),
		NULL,
		(unsigned char*)key,
		iv); // Инициализация методом AES, ключом и вектором

	EVP_DecryptUpdate(ctx, (unsigned char*)plaintext, &len, crypted, cr_len); // Дешифровка

	plaintext_len = len;
	EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext + len, &len); // Финальная обработка

	plaintext_len += len;
	plaintext[plaintext_len] = '\0'; // Обозначаем конец строки

	std::string s = (char*)plaintext;
	DBRecord r(s); // создаем запись в базу данных
	db.push_back(r); // помещаем в базу данных

	EVP_CIPHER_CTX_free(ctx); // Освобождение памяти

}

int DBClass::find(const char * secondname)
{
	for (int i = 0; i < db.size(); i++) { // среди всех элементов 
		if (db[i].GetSecondName() == secondname) { // ищем тот, у которого совпадают фамилии
			return i; // если найдено то возврщаем индекс записи
		}
	}

	return -1; // если не найдена то возвращаем -1
}

int DBClass::add(const char * name, const char * second_name, const char * passport)
{
	bool correct = true;
	for (int i = 0; i < strlen(name); i++) {
		if (isalpha(name[i]) == 0) //isalpha - возвращает ненулевое значение, если его аргумент является буквой 
			correct = false;
	}

	for (int i = 0; i < strlen(name); i++) {
		if (isalpha(second_name[i]) == 0) 
			correct = false;
	}

	if (strlen(passport) != 11)
		correct = false;


	//isdigit - возвращает ненулевое значение, если аргумент ch является цифрой от 0 до 9
	for (int i = 0; i < 4; i++) { // проверяем первые четыре символа (являются ли цифрой)
		if (isdigit(passport[i]) == 0)
			correct = false;
	}

	for (int i = 5; i < 11; i++) { // проверяем последние шесть символов (являются ли цифрой)
		if (isdigit(passport[i]) == 0)
			correct = false;
	}
	DBRecord r(name, second_name, passport); // создаем запись для БД
	db.push_back(r); // добавляем в БД

	if (correct = true) {
		return db.size(); // если все хорошо то возвращаем индекс добавленного элемента
	}
	else {
		return -1; // если валидация не прошла то возвращаем -1
	}
}

void DBClass::printAll() {

	for (int i = 0; i < db.size(); i++) {
		db[i].print(); //вывод каждого элемента БД
	}
}