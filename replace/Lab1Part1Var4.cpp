// Lab1Part1Var4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <io.h>
#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <sys/stat.h>

const int64_t MAX_SIZE = 8589934592 * 2;

bool isNormalSize(char  * inputFile) 
{
	struct stat fi;
	stat(inputFile, &fi);
	return int(fi.st_size) < MAX_SIZE;
}

void RewriteWithoutReplace(char * outputFile, char  * inputFile) 
{
	std::string line;
	std::ifstream input(inputFile);
	std::ofstream output(outputFile);
	while (std::getline(input, line)) 
	{
		output << line << std::endl;
	}
	input.close();
	output.close();
}

void RewriteAndReplace(char * outputFile, char  * inputFile, char * word, char * wordToReplace)
{
	std::string line;
	std::ifstream input(inputFile);
	std::ofstream output(outputFile);

	int pos = 0;
	
	std::string findWord(word);
	std::string newWord(wordToReplace);

	while (std::getline(input, line))
	{
		while ((pos = line.find(findWord)) != std::string::npos) 
		{
			output << line.substr(0, pos) << newWord;
			line.erase(0, pos + findWord.length());
		}
		output << line;
	}
	input.close();
	output.close();
}

bool CheckFileOnCorrect(char * outputFile, char  * inputFile)
{
	std::string oFile(outputFile);
	std::string iFile(inputFile);
	if (iFile.substr(iFile.length() - 4, iFile.length()) != ".txt") 
	{
		printf("Error! File %s not correct.", inputFile);
		return 0;
	}
	else if (oFile.substr(oFile.length() - 4, oFile.length()) != ".txt")
	{
		printf("Error! File %s not correct.", outputFile);
		return 0;
	}
	else
	{
		return 1;
	}
}

int main(int argc, char * argv[])
{

	if (argc < 4)
	{
		printf("Error! Not enough arguments.");
		return 0;
	}
	else if (argc > 5)
	{
		printf("Error! Too many arguments.");
		return 0;
	}
	else if (_access(argv[1], 0) == -1) 
	{
		printf("Error! File %s not found.", argv[1]);
		return 0;
	}
	else if(!CheckFileOnCorrect(argv[2], argv[1]))
	{
		return 0;
	}
	else {
		if (isNormalSize(argv[1]))
		{
			if (argc == 5) {
				RewriteAndReplace(argv[2], argv[1], argv[3], argv[4]);
			}
			else {
				RewriteWithoutReplace(argv[2], argv[1]);
			}
		}
		else
		{
			printf("Error! File too big.");
			return 0;
		}
	}
    return 0;
}

