#pragma once
#include <iostream>
#include <string>
class DBRecord {
private:
	std::string plaintext; //������
	//������ �� ��
	std::string name;
	std::string surname;
	std::string passport;
public:
	//���������� ������������� � �����������
	DBRecord();

	//�����������, ������� ������� ������ � ������� �� ��
	DBRecord(std::string name, std::string surname, std::string passport);
	DBRecord(std::string c); //������ ������ �� ������
	~DBRecord();
	
	std::string GetSecondName(); // �������� ������� �� ������
	void print(); //������� ������ � �������
};