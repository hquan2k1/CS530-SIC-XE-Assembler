// Pass1.h
#ifndef PASS1_H
#define PASS1_H

#include <string>
#include <unordered_map>

using namespace std;

class Pass1 {
public:
    string fileName;
    int startAddress;
    int LOCCTR;
    bool error_flag=false;
    int program_length;
    string firstExecutable_Sec;
    void pass1();
private:
    void handle_LTORG(string & litPrefix, int & LOCCTR, int & previousLOCCTR);
    void evaluateExpression(string expression, bool& relative,string& tempOperand, ofstream& errorFile,bool& error_flag);
    bool symtabComparator(const pair<string, struct_label>& a, const pair<string, struct_label>& b);
};

#endif // PASS1_H
