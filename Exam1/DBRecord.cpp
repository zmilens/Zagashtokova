#include <iostream>
#include <string>
#include "DBRecord.h"


DBRecord::DBRecord() {

}

DBRecord::DBRecord(std::string name, std::string surname, std::string passport) {
	
	plaintext = new char[256]; //������������� ������������ ������
	
	//��������� ������ ������ ������ ������, ������ ��� ������
	plaintext[0] = '\0'; 
	 
	//this - ��������� �� ����� ������� ������, ������� ��������� � ����� �������� ������� ���� ������ ������
	this->name = name; //�������� ���
	this->surname = surname; //�������� �������
	this->passport = passport; //�������� �������
}

DBRecord::DBRecord(std::string c) {

	plaintext = c;
}

void DBRecord:: print() {
	
	std::cout << plaintext << std::endl; //����� ������
	std::cout << name << std::endl;
	std::cout << surname << std::endl;
	std::cout << passport << std::endl;
}

std::string DBRecord::GetSecondName() {
	return surname;
}

DBRecord::~DBRecord() {

}
