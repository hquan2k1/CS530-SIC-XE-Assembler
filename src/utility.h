/*
 * QUAN NGUYEN 
 * cssc4550
 * CS530, Spring 2024
 * Assignment #2
 * utility.cpp
*/

#ifndef UTILITY_H
#define UTILITY_H


#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<map>
#include<algorithm>
#include <string>
#include <vector>

using namespace std;

string intToStringHex(int x,int fill = 5);
string expandString(string data,int length,char fillChar,bool back);
string stringToAsciiHex(const string& str);
int stringHexToInt(string x);
string stringToHexString(const string& input);
bool checkWhiteSpace(char x);
bool checkCommentLine(string line);
bool if_all_num(string x);
void readFirstNonWhiteSpace(string line,int& index,bool& status,string& data,bool readTillEnd=false);
void readByteOperand(string line,int& index,bool& status,string& data);
void writeToFile(ofstream& file,string data,bool newline=true);
string getRealOpcode(string opcode);
char getFlagFormat(string data);


class EvaluateString{
public:
  int getResult();
  EvaluateString(string data);
private:
  string storedData;
  int index;
  char peek();
  char get();
  int term();
  int factor();
  int number();
};

#endif // UTILITY_H