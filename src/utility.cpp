/*
 * QUAN NGUYEN, IAN GOWER
 * cssc4550, cssc4053
 * CS530, Spring 2024
 * Assignment #2
 * utility.cpp
*/

#include "utility.h"


/**
 * Converts an integer to a hexadecimal string representation.
 * 
 * @param x The integer to be converted.
 * @param fill The number of characters to fill in the resulting string. Default is 5.
 * @return The hexadecimal string representation of the integer.
 */
string intToStringHex(int x,int fill){
  stringstream s;
  s << setfill('0') << setw(fill) << hex << x;
  string temp = s.str();
  temp = temp.substr(temp.length()-fill,fill);
  transform(temp.begin(), temp.end(),temp.begin(),::toupper);
  return temp;
}

/**
 * @brief Expands a string to a specified length by adding a fill character.
 * 
 * @param data The input string to be expanded.
 * @param length The desired length of the expanded string.
 * @param fillChar The character used to fill the expanded string.
 * @param back Flag indicating whether the fill characters should be added at the back of the string (default is false).
 * @return The expanded string.
 */
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

/**
 * Converts a string to its hexadecimal representation.
 *
 * @param input The input string to convert.
 * @return The hexadecimal representation of the input string.
 */
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

/**
 * Checks if a character is a white space character.
 * 
 * @param x The character to be checked.
 * @return true if the character is a white space character, false otherwise.
 */
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
void readFirstNonWhiteSpace(string line,int& index,bool& status,string& data,bool readTillEnd){
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

/**
 * Reads a byte operand from the given line of code.
 * 
 * @param line The line of code to read from.
 * @param index The current index in the line of code.
 * @param status The status indicating if the operation was successful.
 * @param data The byte operand read from the line of code.
 */
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
void writeToFile(ofstream& file,string data,bool newline){
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

/**
 * @brief Constructs a new EvaluateString object.
 * 
 * This constructor initializes the `EvaluateString` object with the provided `data`.
 * It sets the `storedData` member variable to the given `data` and initializes the `index` to 0.
 * 
 * @param data The string data to be stored in the `EvaluateString` object.
 */
EvaluateString::EvaluateString(string data){
  storedData = data;
  index=0;
}

/**
 * Returns the result of evaluating the string expression.
 * 
 * @return The result of the evaluated expression.
 */
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

/**
 * Evaluates and returns the result of a term in the expression.
 * A term consists of one or more factors multiplied or divided together.
 * 
 * @return The result of the evaluated term.
 */
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

/**
 * Evaluates a factor in the expression.
 * A factor can be a number, an expression enclosed in parentheses, or a negative factor.
 * 
 * @return The evaluated value of the factor.
 */
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

/**
 * Returns the numeric value of the current character in the input stream.
 * This function reads characters from the input stream until a non-digit character is encountered.
 * It converts the read characters into an integer value and returns it.
 *
 * @return The numeric value of the current character in the input stream.
 */
int EvaluateString::number(){
  int result = get() - '0';
  while(peek() >= '0' && peek() <= '9'){
    result = 10*result + get()-'0';
  }
  return result;
}

/**
 * Retrieves the next character from the stored data and increments the index.
 * 
 * @return The next character from the stored data.
 */
char EvaluateString::get(){
  return storedData[index++];
}

/**
 * Returns the character at the current index in the storedData array.
 * This function does not modify the storedData array or the index.
 *
 * @return The character at the current index.
 */
char EvaluateString::peek(){
  return storedData[index];
}




