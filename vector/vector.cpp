// vector.cpp
#include "pch.h"
#include <iostream>
class matrix
{
protected:
	int columns;
	int rows;
	double * matr = new double[rows*columns];
	double * matr1 = new double[rows*columns];
public:
	bool summMatrix(matrix matr2);
	bool multMatrix(matrix matr2);
	int getElem(int row, int col);
	int getRows() { return rows; }
	int getColumns() { return columns; }
	bool input();
	void transp();
	void print();
	matrix();
	~matrix();
};
class vector : public matrix
{
public:
	vector() { rows = 1; }
	~vector();
	bool multvector(matrix v2);
};
int main()
{
	vector v1;
	vector v2;
	matrix matrA, matrB;
//	matrA.input();
//	matrB.input();
//	matrA.multMatrix(matrB);
//	matrA.summMatrix(matrB);
//	matrA.print();
//	matrA.transp();
//	matrA.print();
	v1.input();
	matrA.input();
	//	v2.input();
	v1.multvector(matrA);
	v1.summMatrix(v2);
	v1.transp();
	v1.print();
	return 0;
}

vector::~vector() {}
matrix::matrix() {}
matrix::~matrix() {}
bool matrix::summMatrix(matrix matr2)
{
	std::cout << "summMatrix" << std::endl;
	if (rows == matr2.getRows() && columns == matr2.getColumns())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				matr[i*columns + j] += matr2.getElem(i, j);
			}
		}
		return true;
	}
	else
	{
		std::cout << "columns and rows aren't equal" << std::endl;
		return false;
	}
}
bool matrix::multMatrix(matrix matr2)
{
	std::cout << "multMatrix" << std::endl;
	if (columns == matr2.getRows())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < matr2.getColumns(); j++)
			{
				int summ = 0;
				for (int p = 0; p < columns; p++)
				{
					summ += matr[i*columns + p] * matr2.getElem(p, j);
				}
				matr1[i*matr2.getColumns() + j] = summ;
				std::cout << matr1[i*matr2.getColumns() + j] << ' ';

			}
			std::cout << std::endl;
		}
		return true;
	}
	else
	{
		std::cout << "columns1!=rows2";
		return false;
	}
}
int matrix::getElem(int row, int col)
{
	if (row<rows && col<columns && row>-1 && col > -1)
	{
		return matr[row*columns + col];
	}
	else
	{
		std::cout << "ERROR\n";
		return -1;
	}
}
bool matrix::input()
{
	if (rows != 1) {
		std::cout << "rows=";
		std::cin >> rows;
	}
	std::cout << "columns=";
	std::cin >> columns;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << "matr[" << i << "][" << j << "]=";
			std::cin >> matr[i*columns + j];
		}
		std::cout << std::endl;
	}
	return true;
}
void matrix::transp()
{
	double temporary;
	std::cout << "transpMatrix" << std::endl;
	for (int i = 0; i < columns; i++)
	{
		for (int j = i; j < rows; j++)
		{
			temporary = matr[j*columns + i];
			matr[j*columns + i] = matr[i*rows + j];
			matr[i*rows + j] = temporary;
		}
	}
}
void matrix::print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << matr[i*columns + j] << '\t';
		}
		std::cout << '\n';
	}
}
bool vector::multvector(matrix v2)
{
	if (columns != v2.getColumns()) {
		std::cout << "error";
	}
	else
	{
		int scal = 0;
		if (columns == v2.getColumns())
		{
			for (int i = 0; i < columns; i++)
			{
				scal += matr[i] * v2.getElem(0, i);
			}
			std::cout << scal;

			return true;
		}

		else { return false; }
	}
}