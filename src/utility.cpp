/*This file contains function helpfull for functioningof other files
Function declared here rarelly changes
This file also contains important files to #include*/
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<map>
#include<algorithm>
#include <string>
#include <vector>
#include <tables.cpp>
using namespace std;

string getString(char c){
  string s(1,c) ;
  return s ;
}

/**
 * Converts an integer to a hexadecimal string representation.
 * 
 * @param x The integer to be converted.
 * @param fill The number of characters to fill in the resulting string. Default is 5.
 * @return The hexadecimal string representation of the integer.
 */
string intToStringHex(int x,int fill = 5){
  stringstream s;
  s << setfill('0') << setw(fill) << hex << x;
  string temp = s.str();
  temp = temp.substr(temp.length()-fill,fill);
  transform(temp.begin(), temp.end(),temp.begin(),::toupper);
  return temp;
}

string expandString(string data,int length,char fillChar,bool back=false){
  if(back){
    if(length<=data.length()){
      return data.substr(0,length);
    }
    else{
      for(int i = length-data.length();i>0;i--){
        data += fillChar;
      }
    }
  }
  else{
    if(length<=data.length()){
      return data.substr(data.length()-length,length);
    }
    else{
      for(int i = length-data.length();i>0;i--){
        data = fillChar + data;
      }
    }
  }
  return data;
}

/**
 * Converts a string to its ASCII hexadecimal representation.
 * 
 * @param str The input string to be converted.
 * @return The ASCII hexadecimal representation of the input string.
 */
string stringToAsciiHex(const string& str) {
  stringstream hexStream;
  for (char c : str) {
    hexStream << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(c);
  }
  return hexStream.str();
}

/**
 * Converts a hexadecimal string to an integer.
 * 
 * @param x The hexadecimal string to convert.
 * @return The integer representation of the hexadecimal string.
 */
int stringHexToInt(string x){
  return stoul(x,nullptr,16);
}

string stringToHexString(const string& input){
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

bool checkWhiteSpace(char x){
  if(x==' ' || x=='\t'){
    return true;
  }
  return false;
}

/**
 * Checks if a given line is a comment line.
 * A comment line starts with a period (.) or an asterisk (*).
 * 
 * @param line The line to be checked.
 * @return True if the line is a comment line, false otherwise.
 */
bool checkCommentLine(string line){
  if(line[0]=='.' || line[0]=='*'){
    return true;
  }
  return false;
}

/**
 * Checks if a given string consists of only numeric characters.
 * 
 * @param x The string to be checked.
 * @return True if the string consists of only numeric characters, false otherwise.
 */
bool if_all_num(string x){
  bool all_num = true;
  int i = 0;
  while(all_num && (i<x.length())){
    all_num &= isdigit(x[i++]);
  }
  return all_num;
}

/**
 * Reads the first non-whitespace character from a given line starting from a specified index.
 * 
 * @param line The input line to read from.
 * @param index The starting index to begin reading from.
 * @param status A boolean flag indicating the status of the read operation.
 * @param data The string variable to store the read data.
 * @param readTillEnd Optional parameter to specify whether to read till the end of the line.
 *                   Default value is false.
 */
void readFirstNonWhiteSpace(string line,int& index,bool& status,string& data,bool readTillEnd=false){
  data = "";
  status = true;

  if(readTillEnd){
    data = line.substr(index,line.length() - index);
    if(data==""){
      status = false;
    }
    return;
  }

  // If no whitespace then append line to data
  while(index<line.length() && !checkWhiteSpace(line[index])){ 
    data += line[index];
    index++;
  }

  // If data is empty, set status to false
  if(data == " "){
    status = false;
  }

  // Increase index to pass all whitespace
  while(index<line.length() && checkWhiteSpace(line[index])){ 
    index++;
  }
}

void readByteOperand(string line,int& index,bool& status,string& data){
  data = "";
  status = true;
  if(line[index]=='C'){
    data += line[index++];
    char identifier = line[index++];
    data += identifier;
    while(index<line.length() && line[index]!=identifier){//Copy all data until next identifier regardless of whitespace
      data += line[index];
      index++;
    }
    data += identifier;
    index++;//Shift to next of identifier
  }
  else{
    while(index<line.length()&&!checkWhiteSpace(line[index])){//In no whitespace then data
      data += line[index];
      index++;
    }
  }

  if(data==""){
    status = false;
  }

  while(index<line.length()&&checkWhiteSpace(line[index])){//Increase index to pass all whitespace
    index++;
  }
}

/**
 * Writes the given data to the specified file.
 *
 * @param file The output file stream to write to.
 * @param data The data to be written to the file.
 * @param newline Flag indicating whether to append a newline character after the data. Default is true.
 */
void writeToFile(ofstream& file,string data,bool newline=true){
  if(newline){
    file<<data<<endl;
  }else{
    file<<data;
  }
}

/**
 * @brief This function takes an opcode as input and returns the real opcode by removing any prefix characters.
 * 
 * @param opcode The opcode to process.
 * @return The real opcode without any prefix characters.
 */
string getRealOpcode(string opcode){
  if(opcode[0] == '+' || opcode[0] == '@'){
    return opcode.substr(1,opcode.length() - 1);
  }
  return opcode;
}

/**
 * Returns the flag format character based on the given data.
 *
 * @param data The input string.
 * @return The flag format character ('#', '+', '@', '=', or ' ').
 */
char getFlagFormat(string data){
  if(data[0] == '#' || data[0] == '+' || data[0] == '@' || data[0] == '='){
    return data[0];
  }
  return ' ';
}

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

EvaluateString::EvaluateString(string data){
  storedData = data;
  index=0;
}

int EvaluateString::getResult(){
  int result = term();
  while(peek()=='+' || peek() == '-'){
    if(get() == '+'){
      result += term();
    }else{
      result -= term();
    }
  }
  return result;
}

int EvaluateString::term(){
  int result = factor();
  while(peek() == '*' || peek() == '/'){
    if(get()=='*'){
      result *= factor();
    }
    else{
      result /= factor();
    }
  }
  return result;
}

int EvaluateString::factor(){
  if(peek() >= '0' && peek() <= '9'){
    return number();
  }
  else if(peek() == '('){
    get();
    int result = getResult();
    get();
    return result;
  }
  else if(peek()=='-'){
    get();
    return -factor();
  }
  return 0;
}

int EvaluateString::number(){
  int result = get() - '0';
  while(peek() >= '0' && peek() <= '9'){
    result = 10*result + get()-'0';
  }
  return result;
}

char EvaluateString::get(){
  return storedData[index++];
}

char EvaluateString::peek(){
  return storedData[index];
}

/**
 * Comparator function for sorting entries in the symbol table.
 * The function compares two pairs of strings and struct_label objects.
 * It first checks if the 'isstart' flag of the first struct_label is set to 'y'.
 * If it is, the first pair is considered smaller and is placed before the second pair.
 * If the 'isstart' flag of the second struct_label is set to 'y', the second pair is considered smaller.
 * If neither 'isstart' flag is set to 'y', the function compares the addresses of the struct_labels.
 * The addresses are converted from hexadecimal strings to integers and compared.
 * If the address of the first struct_label is smaller, the first pair is considered smaller.
 * If the address of the second struct_label is smaller, the second pair is considered smaller.
 * If the addresses are equal, the pairs are considered equal.
 * 
 * @param a The first pair of string and struct_label to compare.
 * @param b The second pair of string and struct_label to compare.
 * @return True if the first pair is smaller, false otherwise.
 */
bool symtabComparator(const pair<string, struct_label>& a, const pair<string, struct_label>& b) {
  if (a.second.isstart == 'y') return true;
  if (b.second.isstart == 'y') return false;
  return stringHexToInt(a.second.address) < stringHexToInt(b.second.address);
}


