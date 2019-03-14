#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <openssl/conf.h> // �������, ��������� � ��������� ��������� OpenSSL
#include <openssl/conf.h>
#include <openssl/evp.h> // ���� ���������������� ������� https://wiki.openssl.org/index.php/EVP
#include <openssl/err.h> // ���� ���������� ������ OpenSSL � �� �����������
#include <openssl/aes.h>
#include <fstream>
#include <string>
#include "DBClass.h"

//#include "DBClass.cpp"
using namespace std;
void bruteforce(const char* filename, char pass_to_find[5]) {
	unsigned char *cryptedtext = new unsigned char[10000]; //������������� ������
	unsigned char *plaintext = new unsigned char[10000]; //�������������� ������
	unsigned char *iv = (unsigned char *)"0123456789012345"; //���������������� ������, �����������

	int plaintext_len = 0; //����� ������ ����� ���������
	int crypted_len = 0; //����� �����

	std::fstream in_crypted(filename, std::ios::binary | std::ios::in); //�������� �����
	if (!in_crypted.is_open()) {
		std::cerr << "�� ������� ������� ����" << std::endl; //cerr - ��������� �� ������
		return;
	}
	in_crypted.read((char*)cryptedtext, 1000); //��������� ����
	crypted_len = in_crypted.gcount(); //gcount - ���������� ���-�� ��������� ��������
	in_crypted.close(); //��������� ����

	int len = 0; //����� ������
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); // �������� ��������� � ����������� ������

	char* password = new char[256]; //���� 

	for (int a= 0; a < 10; a++) {
		for (int b = 0; b < 10; b++) {
			for (int c = 0; c < 10; c++) {
				for (int d = 0; d < 10; d++) {
					
					//����� ���������� ����� ���� �� �������
					pass_to_find[0] = a + '0'; 
					pass_to_find[1] = b + '0';
					pass_to_find[2] = c + '0';
					pass_to_find[3] = d+ '0';
					pass_to_find[4] = '\0'; //���������� ����� ������

					sprintf(password, "0000000000000000000000000000%s", pass_to_find); //��������� ������

					//�����������
					EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)password, iv); // ������������� ������� AES, ������ � ��������
					EVP_DecryptUpdate(ctx, plaintext, &len, cryptedtext, crypted_len); //����������
					plaintext_len = len; // ����� �� ���������
					EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext + len, &len); // ��������� ��������� ����������, ���� ��������� ���� �������� ������� �� ���������

					plaintext_len += len; // ����� �����
					plaintext[plaintext_len] = '\0'; // ����� ������
		
					if (plaintext[0]=='{' && plaintext[1]=='\r' && plaintext[2]=='\n') {
						std::cout << "����: " << password<< std::endl;
						EVP_CIPHER_CTX_free(ctx); // ������������ ������
						return; // ��������� ���������� �������
					}
				}
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char pass[5] = "0000"; //������
	bruteforce("33_encrypted", pass);
	char* password = new char[256];
	sprintf(password, "0000000000000000000000000000%s", pass); // sprintf - ���������� ����� � ������

	DBClass db1; //������ ������ ��
	
	db1.load("33_encrypted", password);
	db1.add("Harry", "Star", "1234 567890");
	
	std:: cout<< db1.find("0123456789");
	db1.printAll();
	


	system("pause");

}