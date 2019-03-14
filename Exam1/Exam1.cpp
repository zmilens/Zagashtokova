#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <openssl/conf.h> // функции, структуры и константы настройки OpenSSL
#include <openssl/conf.h>
#include <openssl/evp.h> // сами криптогрфические функции https://wiki.openssl.org/index.php/EVP
#include <openssl/err.h> // коды внутренних ошибок OpenSSL и их расшифровка
#include <openssl/aes.h>
#include <fstream>
#include <string>
#include "DBClass.h"

//#include "DBClass.cpp"
using namespace std;
void bruteforce(const char* filename, char pass_to_find[5]) {
	unsigned char *cryptedtext = new unsigned char[10000]; //зашифрованная строка
	unsigned char *plaintext = new unsigned char[10000]; //расшифрованная строка
	unsigned char *iv = (unsigned char *)"0123456789012345"; //инициализирующий вектор, рандомайзер

	int plaintext_len = 0; //длина строки после обработки
	int crypted_len = 0; //длина шифра

	std::fstream in_crypted(filename, std::ios::binary | std::ios::in); //файловый поток
	if (!in_crypted.is_open()) {
		std::cerr << "не удалось открыть файл" << std::endl; //cerr - сообщение об ошибке
		return;
	}
	in_crypted.read((char*)cryptedtext, 1000); //считываем шифр
	crypted_len = in_crypted.gcount(); //gcount - определяет кол-во считанных символов
	in_crypted.close(); //закрываем файл

	int len = 0; //длина строки
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); // Создание структуры с настройками метода

	char* password = new char[256]; //шифр 

	for (int a= 0; a < 10; a++) {
		for (int b = 0; b < 10; b++) {
			for (int c = 0; c < 10; c++) {
				for (int d = 0; d < 10; d++) {
					
					//здесь происходит смена цифр на символы
					pass_to_find[0] = a + '0'; 
					pass_to_find[1] = b + '0';
					pass_to_find[2] = c + '0';
					pass_to_find[3] = d+ '0';
					pass_to_find[4] = '\0'; //обозначаем конец строки

					sprintf(password, "0000000000000000000000000000%s", pass_to_find); //формируем пароль

					//расшифровка
					EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)password, iv); // Инициализация методом AES, ключом и вектором
					EVP_DecryptUpdate(ctx, plaintext, &len, cryptedtext, crypted_len); //дешифровка
					plaintext_len = len; // длина до обработки
					EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext + len, &len); // Финальная обработка необходима, если последний блок заполнен данными не полностью

					plaintext_len += len; // длина после
					plaintext[plaintext_len] = '\0'; // конец строки
		
					if (plaintext[0]=='{' && plaintext[1]=='\r' && plaintext[2]=='\n') {
						std::cout << "Ключ: " << password<< std::endl;
						EVP_CIPHER_CTX_free(ctx); // Освобождение памяти
						return; // завершить выполнение функции
					}
				}
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char pass[5] = "0000"; //пароль
	bruteforce("33_encrypted", pass);
	char* password = new char[256];
	sprintf(password, "0000000000000000000000000000%s", pass); // sprintf - производит вывод в массив

	DBClass db1; //создаём пустую БД
	
	db1.load("33_encrypted", password);
	db1.add("Harry", "Star", "1234 567890");
	
	std:: cout<< db1.find("0123456789");
	db1.printAll();
	


	system("pause");

}