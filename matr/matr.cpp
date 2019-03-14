// matr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

class Matrix
{
private:
	int columns, rows;
	double *matr = new double[rows*columns];
public:
	bool summMatrix(Matrix matr1);
	bool multMatrix(Matrix matr1);
	int getRows() { return rows; }
	int getColumns() { return columns; }
	int getElem(int row, int column);
	bool input();
	void print();
	void transp();
	Matrix();
	~Matrix();
};
Matrix::Matrix() {}
Matrix::~Matrix() {}
//delete[] * matr;
int main()
{
	Matrix matrA, matrB;
	matrA.input();
	matrB.input();
	matrA.summMatrix(matrB);
	matrA.multMatrix(matrB);
	matrA.print();
	matrA.transp();
	matrA.print();
	return 0;
}
bool Matrix::summMatrix(Matrix matr1)
{
	std::cout << "summMatrix" << std::endl;
	if (rows == matr1.getRows() && columns == matr1.getColumns())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				matr[i*columns + j] += matr1.getElem(i, j);
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
int Matrix:: getElem(int row, int column)
{
	if (row<rows && column < columns && rows >-1 && columns>-1)
	{
		return matr[rows*columns + column];
	}
	else
	{
		std::cout << "error\n";
		return -1;
	}
}
bool Matrix:: multMatrix(Matrix matr1)
{
	std::cout << "multMatrix" << std::endl;
	if (columns == matr1.getRows())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < matr1.getColumns(); j++)
			{
				int summ = 0;
				for (int p = 0; p < columns; p++)
				{
					summ += matr[i*columns + p] * matr1.getElem(p, j);
				}
				matr[i*matr1.getColumns() + j] = summ;
				std::cout << matr[i*matr1.getColumns() + j] << ' ';
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
};
bool Matrix:: input() 
{
	std::cout << "rows=";
	std::cin >> rows;
	std::cout << "columns=";
	std::cin >> columns;
	for (int i=0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << "matr[" << i << "][" << j << "]=";
			std::cin >> matr[i*columns+j];
		}
		std::cout <<std:: endl;
	}
	return true;
};
void Matrix::print() 
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cin >> matr[i*columns + j];
		}
		std::cout << std::endl;
	}
};
void Matrix:: transp() 
{
	int temp;
	std::cout << "transpMatrix" << std::endl;
	for (int i = 0; i < columns; i++)
	{
		for (int j = i; j < rows; j++)
		{
			temp = matr[j*columns + i];
			matr[j*columns + i] = matr[i*rows + j];
			matr[i*rows + j] = temp;
		}
	}
};

