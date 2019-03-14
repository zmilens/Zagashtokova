#pragma once
#include "DBRecord.h"

#include <vector>

class DBClass
{
private:
	std::vector <DBRecord> db;
public:
	//��������� ����������� � ����������
	DBClass();
	~DBClass();

	//����� ����������� � �������� ������� �� �����
	//����� ��������� ���������� �� ����
	int load(const char * filename, const char * key);
	
	//��������� ������ � ��
	int add(const char * name, const char * second_name, const char * passport);

	//���� ������ �� �������
	int find(const char *secondname);

	//������� � ������� ������ �� ��
	void printAll();

};