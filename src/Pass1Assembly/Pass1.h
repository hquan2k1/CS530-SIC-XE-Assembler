// Pass1.h
#ifndef PASS1_H
#define PASS1_H

#include <string>
#include <unordered_map>

using namespace std;

class Pass1 {
public:
    string fileName;
    bool error_flag=false;
    int program_length;
    string firstExecutable_Sec;
    void pass1();
private:
    void handle_LTORG(string& litPrefix, int& lineNumberDelta,int lineNumber,int& LOCCTR, int& lastDeltaLOCCTR);
    void evaluateExpression(string expression, bool& relative,string& tempOperand,int lineNumber, ofstream& errorFile,bool& error_flag);

};

#endif // PASS1_H
