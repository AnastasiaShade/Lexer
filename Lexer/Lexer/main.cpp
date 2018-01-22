#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Lexer.h"
using namespace std;

void CheckArgsCount(int argc);
void CheckFile(ifstream &input, string fileName);
void Print(vector<string> &tokens, vector<string> &tokenTypes);

int main(int argc, char * argv[])
{
	try
	{
		CheckArgsCount(argc);
		ifstream input("GetNetAddress.java");
		//ifstream input("input.txt");
		CheckFile(input, argv[1]);
		string str;
		CLexer lexer;
		
		while (getline(input, str))
		{
			lexer.FindTokens(str);
			Print(lexer.GetTokens(), lexer.GetTokenTypes());
		}
		cout << "Token type is \"" << EOF_TOKEN << "\"" << endl;
		cout << "Token value is \"" << "" << "\"" << endl;
		cout << "-----------------------------------------------------------------" << endl;

	}
	catch (exception & err)
	{
		cout << err.what() << endl;
	}

    return 0;
}

void CheckArgsCount(int argc)
{
	if (argc < 2)
	{
		throw logic_error("Invalid arguments count\nUsage: Lexer.exe <input file>\n");
	}
}

void CheckFile(ifstream &input, string fileName)
{
	if (!input.is_open())
	{
		throw ios_base::failure("Failed to open file for reading\n");
	}
}

void Print(vector<string> & tokens, vector<string> & tokenTypes)
{
	for (size_t it = 0; it < tokens.size(); ++it)
	{
		cout << "Token type is \"" << tokenTypes[it] << "\"" << endl;
		cout << "Token value is \"" << tokens[it] << "\"" << endl;
		cout << "-----------------------------------------------------------------" << endl;
	}
}