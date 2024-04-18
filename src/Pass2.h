/*
 * QUAN NGUYEN 
 * cssc4550
 * CS530, Spring 2024
 * Assignment #2
 * utility.cpp
*/

#ifndef SICXEASSEMBLER_PASS2_H
#define SICXEASSEMBLER_PASS2_H

#include <string>

using namespace std;

class Pass2 {
public:
    string fileName;
    void pass2();

private:
    string readSection(string data, int& ind);
    bool readIntFile(ifstream& readFile, bool& isComment, string& address, string& label, string& opcode, string& operand, string& comment);
    void writeListingLine(ofstream& writeFile, bool isComment, string& address, string& label, string& opcode, string& operand, string &objCode, string&comment);
    bool searchOptab(string opcode);
    bool searchSymTab(string operand);
    bool symbolInOperand(string operand);
    string fetchSymVal(string operand);
    string assembleObj(string opcode, string operand, int opAd, string address);

};



#endif //SICXEASSEMBLER_PASS2_H
