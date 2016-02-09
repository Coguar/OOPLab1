// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <fstream>
#include <string>
#include <io.h>
#include <algorithm>

using namespace std;

const int MATRIX_SIZE = 3;
typedef vector<vector<float>> matrix;

float GetMinor(matrix & arr, int i, int j)
{
	int arrSize = int(arr.size() - 1);
	vector<float> minor;
	for (int mi = 0; mi <= arrSize; mi++)
	{
		for (int mj = 0; mj <= arrSize; mj++)
		{
			if (mi != i && mj != j)
			{
				minor.push_back(arr[mi][mj]);
			}
		}
	}
	return minor[0] * minor[3] - minor[1] * minor[2];
}

matrix GetMinorMatrix(matrix & arr)
{
	int arrSize = int(arr.size() - 1);
	matrix minorArr = arr;
	for (int i = 0; i <= arrSize; i++)
	{
		for (int j = 0; j <= arrSize; j++)
		{
			minorArr[i][j] = GetMinor(arr, i, j) * float(pow(-1, i + j));
		}
	}
	return minorArr;
}

float GetDeterminant(matrix & arr)
{
	int arrSize = int(arr.size() - 1);
	int j;
	int j1;
	float determinant = 0;
	float number;
	float number1;
	for (int k = 0; k <= arrSize; k++)
	{
		j = k;
		j1 = k;
		number = 1;
		number1 = 1;
		for (int i = 0; i <= arrSize; i++)
		{
			number *= arr[i][j];
			number1 *= arr[i][j1];
			j++;
			j1--;
			if (j > arrSize)
				j = 0;
			if (j1 < 0)
				j1 = arrSize;

		}
		determinant += number - number1;
	}
	return determinant;
}

bool isInvertable(matrix & arr)
{
	if (GetDeterminant(arr) != 0)
		return 1;
	return 0;
}

void showInvertMatrix(matrix & arr, float determinant)
{
	int arrSize = int(arr.size() - 1);
	for (int i = 0; i <= arrSize; i++)
	{
		for (int j = 0; j <= arrSize; j++)
		{
			printf("%6.3f  ", (float(arr[j][i]) / determinant));
		}
		printf("\n");
	}
}

matrix GetMatrixFromFile(char * inputFile)
{
	ifstream matrixFile(inputFile);
	matrix arr(3);
	float number;
	int arrSize = 3;

	for (int i = 0; i < arrSize; i++)
		for (int j = 0; j < arrSize; j++)
		{
			number = 0;
			matrixFile >> number;
			arr[i].push_back(number);
		}
	matrixFile.close();
	return arr;
}

bool isCorrectFile(char * inputFile)
{
	string line;
	ifstream matrixFile(inputFile);
	int lineCount = 0;
	while (getline(matrixFile, line))
	{
		lineCount++;	
		for (int i = 0; i < int(line.length()); i++)
		{
			if (!((int)line[i] >= 48 && (int)line[i] <= 57 || line[i] == '-' || line[i] == ' ' || line[i] == '.'))
			{
				matrixFile.close();
				return 0;
			}
		}
	}
	matrixFile.close();
	if (lineCount != MATRIX_SIZE)
		return 0;
	return 1;
}

int main(int argc, char * argv[])
{
	matrix arr;
	if (argc < 2)
	{
		printf("Error! Not enough arguments.");
		return 0;
	}
	else if (argc > 2)
	{
		printf("Error! Too many arguments.");
		return 0;
	}
	else if (_access(argv[1], 0) == -1)
	{
		printf("Error! File %s not found.", argv[1]);
		return 0;
	}
	else if (!isCorrectFile(argv[1]))
	{
		printf("Error! Wrong file.");
		return 0;
	}
	else
	{
		arr = GetMatrixFromFile(argv[1]);
		if (isInvertable(arr))
			showInvertMatrix(GetMinorMatrix(arr), GetDeterminant(arr));
		else
		{
			printf("Matrix can not be inverted.");
			return 0;
		}
	}
    return 0;
}

