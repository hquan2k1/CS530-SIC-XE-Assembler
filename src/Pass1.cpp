// Pass1.cpp
#include "Pass1.h"
#include <fstream>
#include <sstream>
#include <iostream>

Pass1::Pass1() : LOCCTR(0) {}

void Pass1::process(std::string inputFile) {
    std::ifstream sourceFile(inputFile);
    std::string line;
    if (sourceFile.is_open()) {
        while (getline(sourceFile, line)) {
            processLine(line);
        }
        sourceFile.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

void Pass1::processLine(const std::string& line) {
    if (!isComment(line)) {
        std::istringstream iss(line);
        std::string label, opcode, operand;
        iss >> label >> opcode >> operand;

        if (!label.empty()) {
            if (SYMTAB.find(label) != SYMTAB.end()) {
                handleError("Duplicate symbol");
            } else {
                SYMTAB[label] = LOCCTR;
            }
        }

        if (opcode == "START") {
            handleStartDirective(operand);
        } else if (opcode == "END") {
            handleEndDirective();
        } else {
            // Process other opcodes and update LOCCTR
        }
    }
    writeIntermediateFile(line);
}

void Pass1::writeIntermediateFile(const std::string& line) {
    // Write the processed line to the intermediate file
}

bool Pass1::isComment(const std::string& line) {
    // Determine if the line is a comment
    return false; // Placeholder
}

void Pass1::handleStartDirective(const std::string& operand) {
    // Handle START directive
}

void Pass1::handleEndDirective() {
    // Handle END directive
}

void Pass1::handleError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}
