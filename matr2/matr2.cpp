// matrix.cpp 

#include "pch.h" 
#include <iostream>
#include <cstring>

class matrix
{
private:

	double matr[10][10] = { {0} };
	int rows;
	int columns;
public:
	matrix();
	~matrix();
	bool summMatrix(matrix matr2);
	bool multMatrix(matrix matr2);
	int getElem(int row, int col);
	int getRows() { return rows; }
	int getColumns() { return columns; }
	bool input();
	void transp();
	void print();
};
int main()
{
	matrix matrA, matrB;
	matrA.input();
	matrB.input();
	matrA.multMatrix(matrB);
	matrA.summMatrix(matrB);
	matrA.print();
	matrA.transp();
	matrA.print();
	return 0;
}
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
				matr[i][j] += matr2.getElem(i, j);
			}
		}
		return true;
	}
	else {
		return false;
	}
}
bool matrix::multMatrix(matrix matr2)
{
	std::cout << "multMatrix" << std::endl;
	double result[10][10];
	if (columns == matr2.getRows())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < matr2.getColumns(); j++)
			{
				int summ = 0;
				for (int p = 0; p < columns; p++)
				{
					summ += matr[i][p] * matr2.getElem(p, j);
				}
				result[i][j] = summ;
				std::cout << result[i][j] << '\t';
			}
			std::cout << '\n';
		}
		return true;
	}
	else return false;
}
int matrix::getElem(int row, int col)
{
	if (row<rows && col<columns && row>-1 && col > -1)
	{
		return matr[row][col];
	}
	else
	{
		std::cout << "ERROR\n";
		return -1;
	}
}
bool matrix::input()
{
	std::cout << "rows=";
	std::cin >> rows;
	if (rows < 1 || rows>10)
	{
		return false;
	}
	std::cout << "columns=";
	std::cin >> columns;
	if (columns < 1 || columns>10)
	{
		return false;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << "matr[" << i << "][" << j << "]=";
			std::cin >> matr[i][j];
		}
		std::cout << std::endl;
	}
	return true;
}
void matrix::transp()
{
	std::cout << "transpMatrix" << std::endl;
	double temporary;
	for (int i = 0; i < 10; i++)
	{
		for (int j = i; j < rows; j++)
		{
			temporary = matr[j][i];
			matr[j][i] = matr[i][j];
			matr[i][j] = temporary;

		}
	}
	int temp = columns;
	columns = rows;
	rows = temp;
}
void matrix::print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << matr[i][j] << '\t';
		}
		std::cout << '\n';
	}
}