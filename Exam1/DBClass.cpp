#include <iostream>
#include <openssl/conf.h> // �������, ��������� � ��������� ��������� OpenSSL
#include <openssl/conf.h>
#include <openssl/evp.h> // ���� ���������������� ������� https://wiki.openssl.org/index.php/EVP
#include <openssl/err.h> // ���� ���������� ������ OpenSSL � �� �����������
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
	unsigned char *crypted = new unsigned char[1000]; // ������������� ������
	unsigned char *plaintext = new unsigned char[1000]; // ������������� ������
	unsigned char *iv = (unsigned char *)"0123456789012345"; // �����������
	int plaintext_len = strlen((char *)plaintext); // ����� ������ ����� ���������
	int len = 0; // ����� ������
	int cr_len = 0; // ����� �����

	std::fstream in_crypted(filename, std::ios::binary | std::ios::in); // �������� �����
	if (in_crypted.is_open()) { // ��������� ����
		in_crypted.read((char*)crypted, 1000); // ��������� ����
		cr_len = in_crypted.gcount(); // �������� ��� �� ��������� ��������
		in_crypted.close(); // ��������� ����
	}
	else { // ���� ���� �� ��������
		std::cout << "�� ������� ������� ��� ��������� ����" << std::endl;
		return -1;
	}

	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); // �������� ��������� � ����������� ������

	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(),
		NULL,
		(unsigned char*)key,
		iv); // ������������� ������� AES, ������ � ��������

	EVP_DecryptUpdate(ctx, (unsigned char*)plaintext, &len, crypted, cr_len); // ����������

	plaintext_len = len;
	EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext + len, &len); // ��������� ���������

	plaintext_len += len;
	plaintext[plaintext_len] = '\0'; // ���������� ����� ������

	std::string s = (char*)plaintext;
	DBRecord r(s); // ������� ������ � ���� ������
	db.push_back(r); // �������� � ���� ������

	EVP_CIPHER_CTX_free(ctx); // ������������ ������

}

int DBClass::find(const char * secondname)
{
	for (int i = 0; i < db.size(); i++) { // ����� ���� ��������� 
		if (db[i].GetSecondName() == secondname) { // ���� ���, � �������� ��������� �������
			return i; // ���� ������� �� ��������� ������ ������
		}
	}

	return -1; // ���� �� ������� �� ���������� -1
}

int DBClass::add(const char * name, const char * second_name, const char * passport)
{
	bool correct = true;
	for (int i = 0; i < strlen(name); i++) {
		if (isalpha(name[i]) == 0) //isalpha - ���������� ��������� ��������, ���� ��� �������� �������� ������ 
			correct = false;
	}

	for (int i = 0; i < strlen(name); i++) {
		if (isalpha(second_name[i]) == 0) 
			correct = false;
	}

	if (strlen(passport) != 11)
		correct = false;


	//isdigit - ���������� ��������� ��������, ���� �������� ch �������� ������ �� 0 �� 9
	for (int i = 0; i < 4; i++) { // ��������� ������ ������ ������� (�������� �� ������)
		if (isdigit(passport[i]) == 0)
			correct = false;
	}

	for (int i = 5; i < 11; i++) { // ��������� ��������� ����� �������� (�������� �� ������)
		if (isdigit(passport[i]) == 0)
			correct = false;
	}
	DBRecord r(name, second_name, passport); // ������� ������ ��� ��
	db.push_back(r); // ��������� � ��

	if (correct = true) {
		return db.size(); // ���� ��� ������ �� ���������� ������ ������������ ��������
	}
	else {
		return -1; // ���� ��������� �� ������ �� ���������� -1
	}
}

void DBClass::printAll() {

	for (int i = 0; i < db.size(); i++) {
		db[i].print(); //����� ������� �������� ��
	}
}