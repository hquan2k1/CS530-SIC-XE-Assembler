// Pass1.h
#ifndef PASS1_H
#define PASS1_H

#include <string>
#include <unordered_map>

class Pass1 {
public:
    Pass1();
    void process(std::string inputFile);

private:
    int LOCCTR;
    std::unordered_map<std::string, int> SYMTAB;
    void processLine(const std::string& line);
    void writeIntermediateFile(const std::string& line);
    bool isComment(const std::string& line);
    void handleStartDirective(const std::string& operand);
    void handleEndDirective();
    void handleError(const std::string& message);
};

#endif // PASS1_H
