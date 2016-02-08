// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int GetNumber(char num, int radix, bool & wasError)
{
	int number = (int)(num);
	if (number > 47 && number < 58)
	{
		if (number - 48 < radix)
			return number - 48;
		else
		{
			wasError = true;
			return -1;
		}
	}
	else if (number > 64 && number < 91)
	{
		number = number - (int)('A') + 10;
		if (number < radix)
			return number;
		else
		{
			wasError = true;
			return -1;
		}
	}
	else
	{
		wasError = true;
		return -1;
	}
}

char GetSymbol(int num)
{
	
	if (num < 10)
	{
		return char(num + 48);
	}
	else
		return char(num - 10 + 65);
}

int StringToInt(const char str[], int radix, bool & wasError)
{
	int len = std::strlen(str);
	int number = 0;
	int i = 0;
	char symbol;
	while (str[i] && !wasError)
	{
		symbol = str[i];
		number += GetNumber(str[i], radix, wasError) * std::pow(radix, len - i - 1);
		i++;
	}
	if (wasError)
		return -1;
	return number;
}

std::string IntToString(int n, int radix)
{
	std::string number = "";
	while (n > 0)
	{
		number = GetSymbol(n % radix) + number;
		n = int(n / radix);
	}
	return number;
}

std::string transferNumber(int present, int future, char * value, bool & wasError)
{
	int number = StringToInt(value, present, wasError);
	if (!wasError)
	{
		return IntToString(number, future);
	}
	return "Error";
}

bool isNumber(char * num)
{
	int i = 0;
	while (num[i])
	{
		if (!(((int)(num[i]) > 64 && (int)(num[i]) < 91) || ((int)(num[i]) > 47 && (int)(num[i]) < 58) || (int)(num[i]) == 45))
			return 0;
		i++;
	}
	return 1;
}

bool isMinus(char * num, std::string & absNumber)
{
	std::string number(num);
	char * an;
	if (num[0] == '-')
	{
		number.erase(0, 1);
		num = &number[0u];
		absNumber = number;
		return 1;
	}
	absNumber = number;
	return 0;
}

int main(int argc, char * argv[])
{
	char * value = argv[3];
	std::string absNumber;
	std::string answer;
	bool isMinusNumber = false;
	bool wasError = false;
	if (argc < 4)
	{
		printf("Error! Not enough arguments.");
		return 0;
	}
	else if (argc > 4)
	{
		printf("Error! Too many arguments.");
		return 0;
	}
	else if (atoi(argv[1]) < 2 || atoi(argv[1]) > 36 || atoi(argv[2]) < 2 || atoi(argv[2]) > 36)
	{
		printf("Error! Wrong data.");
		return 0;
	}
	else if (!isNumber(argv[3]))
	{
		printf("Error! Wrong value.");
		return 0;
	}
	else
	{
		isMinusNumber = isMinus(std::ref(value), absNumber);
		value = &absNumber[0u];
		answer = transferNumber(atoi(argv[1]), atoi(argv[2]), value, wasError);
		if (wasError)
		{
			printf("Error! Wrong value!!");
			return 0;
		}
		if (isMinusNumber)
			printf("-%s", answer.c_str());
		else
			printf("%s", answer.c_str());
		
	}
    return 0;
}

