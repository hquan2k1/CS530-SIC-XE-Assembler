/*Code for pass1*/
#include "utility.cpp" /*conatins all important headers*/
#include "tables.cpp"
#include "Pass1.h"


using namespace std;

ifstream intermediateFile;
ofstream errorFile,objectFile,ListingFile;
ofstream printtab;
string writestring;

/**
 * Handles the LTORG directive in Pass 1 of the assembly process.
 * Assigns addresses to literals in the LITTAB and updates the LOCCTR accordingly.
 * 
 * @param litPrefix The prefix string to be updated with the assigned addresses of literals.
 * @param LOCCTR The current value of the LOCCTR (Location Counter).
 * @param prevLOCCTR The previous value of the LOCCTR.
 */

void Pass1::handle_LTORG(string& litPrefix,int& LOCCTR, int& prevLOCCTR){
  string litAddress,litValue;
  litPrefix = "";
  for(auto const& it: LITTAB){
    litAddress = it.second.address;
    litValue = it.second.value;
    if(litAddress!="?"){
    }
    else {
      LITTAB[it.first].address = intToStringHex(LOCCTR);
      litPrefix += intToStringHex(LOCCTR) + "\t" + "*" + "\t" + "="+ litValue + "\t" + " " + "\t" + " ";

      if(litValue[0]=='X'){
        LOCCTR += (litValue.length() - 3)/2;
        prevLOCCTR += (litValue.length() - 3)/2;
      }
      else if(litValue[0]=='C'){
        LOCCTR += litValue.length() - 3;
        prevLOCCTR += litValue.length() - 3;
      }
    }
  }
}

/**
 * Evaluates an expression and determines the value of the operand.
 * 
 * @param expression The expression to be evaluated.
 * @param relative A boolean reference indicating if the operand is relative or not.
 * @param tempOperand A string reference to store the evaluated operand value.
 * @param lineNumber The line number of the expression in the source code.
 * @param errorFile An ofstream reference to the error file for writing error messages.
 * @param error_flag A boolean reference indicating if an error occurred during evaluation.
 */
void Pass1::evaluateExpression(string expression, bool& relative,string& tempOperand, ofstream& errorFile,bool& error_flag){
  string singleOperand="?",singleOperator="?",valueString="",valueTemp="",writeData="";
  // lastOperator is 1 if the last operator is multiplication or division, 0 for addition and subtraction
  // lastOperand is 1 if the last operand is a relative address, 0 is absolute
  // pairCount is 0 if relative expression, 1 if absolute expression
  int lastOperand=0,lastOperator=0,pairCount=0;
  char lastByte = ' ';
  bool Illegal = false;

  for(int i=0;i<expression.length();){
    // Concatenate characters to singleOperand until an operator is found or the end of the expression is reached
    singleOperand = "";
    lastByte = expression[i];
    while((lastByte != '+' && lastByte != '-' && lastByte != '/' && lastByte !=  '*') && i<expression.length()){
      singleOperand += lastByte;
      lastByte = expression[++i];
    }

    
    if(SYMTAB[singleOperand].exists=='y'){
      lastOperand = SYMTAB[singleOperand].relative;
      valueTemp = to_string(stringHexToInt(SYMTAB[singleOperand].address));
    } else if((singleOperand != "" || singleOperand !="?" ) && if_all_num(singleOperand)){
      lastOperand = 0;
      valueTemp = singleOperand;
    } else {
      writeData = "Can't find symbol. Found " + singleOperand;
      writeToFile(errorFile,writeData);
      Illegal = true;
      break;
    }

    // Relative addressing used in multiplication and division is illegal
    // Multiplication and division requires absolute addressing
    if(lastOperand * lastOperator == 1){
      writeData = "Illegal expression, relative address can't divide";
      writeToFile(errorFile,writeData);
      error_flag = true;
      Illegal = true;
      break;
    } else if((singleOperator=="-" || singleOperator=="+" || singleOperator=="?") && lastOperand == 1){
      // Relative addressing can still use addition and subtraction
      if(singleOperator=="-"){
        pairCount--;
      }
      else{
        pairCount++;
      }
    }

    valueString += valueTemp;

    singleOperator= "";
    while(i<expression.length()&&(lastByte=='+'||lastByte=='-'||lastByte=='/'||lastByte=='*')){
      singleOperator += lastByte;
      lastByte = expression[++i];
    }

    if(singleOperator.length()>1){
      writeData = "Illegal operator in expression. Found "+singleOperator;
      writeToFile(errorFile,writeData);
      error_flag = true;
      Illegal = true;
      break;
    }

    if(singleOperator=="*" || singleOperator == "/"){
      lastOperator = 1;
    } else{
      lastOperator = 0;
    }

    valueString += singleOperator;
  }

  if(!Illegal){
    if(pairCount==1){
      /*relative*/
      relative = 1;
      EvaluateString tempOBJ(valueString);
      tempOperand = intToStringHex(tempOBJ.getResult());
    } else if(pairCount==0){
      /*absolute*/
      relative = 0;
      EvaluateString tempOBJ(valueString);
      tempOperand = intToStringHex(tempOBJ.getResult());
    } else{
      writeData = "Illegal expression of addressing";
      writeToFile(errorFile,writeData);
      error_flag = true;
      tempOperand = "00000";
      relative = 0;
    }
  }
  else {
    tempOperand = "00000";
    error_flag = true;
    relative = 0;
  }
}

/**
 * This function performs the first pass of the assembly process.
 * It initializes the source file, intermediate file, and error file.
 * It opens the source file and validates the input.
 * It opens the intermediate file and validates the input.
 * It writes the header to the intermediate file.
 * It opens the error file and validates the input.
 * It writes the pass1 header to the error file.
 * It parses the first line of the source file, storing the label and opcode.
 * If the opcode is "START", it parses the operand and comment, sets the start address and LOCCTR, and writes the line to the intermediate file.
 * It then reads the next line and parses the label and opcode.
 * It enters a loop until the opcode is "END".
 * Within the loop, it checks if the line is a comment line.
 * If it is not a comment line, it checks if a label exists and appends it to the symbol table.
 * It searches for the appropriate opcode and assembler directives and increments the LOCCTR accordingly.
 * It handles special cases for certain opcodes.
 * It handles the "BASE" directive.
 * It handles the "LTORG" directive.
 * It handles the "ORG" directive.
 * It handles the "EQU" directive.
 * If the opcode is invalid, it writes an error message to the error file.
 * It then reads the next line and parses the label and opcode.
 * Once the opcode is "END", it checks if a label exists and appends it to the symbol table.
 * It resets the LOCCTR and prevLOCCTR.
 * 
 * @param fileName The name of the source file to be processed.
 * @param SYMTAB The symbol table to store the symbols and their addresses.
 * @param OPTAB The opcode table to store the opcodes and their formats.
 * @param LITTAB The literal table to store the literals and their addresses.
 * @param startAddress The starting address of the program.
 * @param LOCCTR The current value of the LOCCTR (Location Counter).
 * @param error_flag A flag indicating if an error occurred during the assembly process.
 * @param program_length The length of the program.
 * @param firstExecutable_Sec The name of the first executable section.
 * @param index The index of the current line being processed.
 * @param label The label of the current line being processed.
 * @param opcode The opcode of the current line being processed.
 * @param operand The operand of the current line being processed.
 * @param comment The comment of the current line being processed.
 * @param tempOperand A temporary operand used for calculations.
 * @param saveLOCCTR A temporary variable to store the LOCCTR value.
 * @param prevLOCCTR The previous value of the LOCCTR.
 * @param fileLine The current line being processed.
 * @param writeData The data to be written to the intermediate file.
 * 
 */
void Pass1::pass1() {
  // Initialize the source file, intermediate file, and error file
  ifstream sourceFile;
  ofstream intermediateFile, errorFile;

  // Open the source file and validate input
  sourceFile.open(fileName);
  if (!sourceFile) {
    cout << "Unable to open file: " << fileName << endl;
    exit(1);
  }

  // Open intermediate file and validate input
  intermediateFile.open("intermediate_" + fileName);
  if (!intermediateFile) {
    cout << "Unable to open file: intermediate_" << fileName << endl;
    exit(1);
  }

  writeToFile(intermediateFile, "Address\tLabel\tOPCODE\tOPERAND\tComment");

  // Open error file and validate input
  errorFile.open("error_" + fileName);
  if (!errorFile) {
    cout << "Unable to open file: error_" << fileName << endl;
    exit(1);
  }

  writeToFile(errorFile, "----------PASS1----------");

  string fileLine;
  string writeData, writeDataSuffix = "", writeDataPrefix = "";
  int index = 0;

  bool statusCode;
  string label, opcode, operand, comment;
  string tempOperand;

  int saveLOCCTR, prevLOCCTR;
  prevLOCCTR = 0;

  getline(sourceFile, fileLine);

  while (checkCommentLine(fileLine)) {
    writeData = fileLine;
    writeToFile(intermediateFile, writeData);
    getline(sourceFile, fileLine);
    index = 0;
  }

  // Parse the first line of the source file, storing label and opcode
  readFirstNonWhiteSpace(fileLine, index, statusCode, label);
  readFirstNonWhiteSpace(fileLine, index, statusCode, opcode);

  if (opcode == "START") {
    SYMTAB[label].name = label;
    SYMTAB[label].address = intToStringHex(0);
    SYMTAB[label].exists = 'y';
    SYMTAB[label].isstart = 'y';
    readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
    readFirstNonWhiteSpace(fileLine, index, statusCode, comment, true);

    startAddress = stringHexToInt(operand);
    LOCCTR = startAddress;
    writeData = intToStringHex(LOCCTR - prevLOCCTR) + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment;
    writeToFile(intermediateFile, writeData); // Write file to intermediate file

    getline(sourceFile, fileLine); // Read next line

    index = 0;
    readFirstNonWhiteSpace(fileLine, index, statusCode, label); // Parse label
    readFirstNonWhiteSpace(fileLine, index, statusCode, opcode); // Parse OPCODE
  } else {
    startAddress = 0;
    LOCCTR = 0;
  }

  while (opcode != "END") 
  {
    while (opcode != "END") 
    {
      if (!checkCommentLine(fileLine)) {
        // Check if label exists and append to SYMTAB
        if (label != "") {
          if (SYMTAB[label].exists == 'n') {
            SYMTAB[label].name = label;
            SYMTAB[label].address = intToStringHex(LOCCTR);
            SYMTAB[label].relative = 1;
            SYMTAB[label].exists = 'y';
          } else {
            writeData = "Duplicate symbol for '" + label + "'. Previously defined at " + SYMTAB[label].address;
            writeToFile(errorFile, writeData);
            error_flag = true;
          }
        }
        
        // Search for appropriate OPCODE and ASSEMBLER DIRECTIVES 
        // and increment LOCCTR according to format
        if (OPTAB[getRealOpcode(opcode)].exists == 'y') {
          if (OPTAB[getRealOpcode(opcode)].format == 3) {
            LOCCTR += 3;
            prevLOCCTR += 3;
            if (getFlagFormat(opcode) == '+') {
              LOCCTR += 1;
              prevLOCCTR += 1;
            }
            if (getRealOpcode(opcode) == "RSUB") {
              operand = " ";
            } else {
              readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
              if (operand[operand.length() - 1] == ',') {
                readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
                operand += tempOperand;
              }
            }

            if (getFlagFormat(operand) == '=') {
              tempOperand = operand.substr(1, operand.length() - 1);
              if (tempOperand == "*") {
                tempOperand = "X'" + intToStringHex(LOCCTR - prevLOCCTR, 6) + "'";
              }
              if (LITTAB[tempOperand].exists == 'n') {
                LITTAB[tempOperand].value = tempOperand;
                LITTAB[tempOperand].exists = 'y';
                LITTAB[tempOperand].address = "?";
              }
            }
          } else if (OPTAB[getRealOpcode(opcode)].format == 1) {
            operand = " ";
            LOCCTR += OPTAB[getRealOpcode(opcode)].format;
            prevLOCCTR += OPTAB[getRealOpcode(opcode)].format;
          } else {
            LOCCTR += OPTAB[getRealOpcode(opcode)].format;
            prevLOCCTR += OPTAB[getRealOpcode(opcode)].format;
            readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
            if (operand[operand.length() - 1] == ',') {
              readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
              operand += tempOperand;
            }
          }
        } else if (opcode == "WORD") {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          LOCCTR += 3;
          prevLOCCTR += 3;
        } else if (opcode == "RESW") {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          LOCCTR += 3 * stoi(operand);
          prevLOCCTR += 3 * stoi(operand);
        } else if (opcode == "RESB") {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          LOCCTR += stoi(operand);
          prevLOCCTR += stoi(operand);
        } else if (opcode == "BYTE") {
          readByteOperand(fileLine, index, statusCode, operand);
          if (operand[0] == 'X') {
            LOCCTR += (operand.length() - 3) / 2;
            prevLOCCTR += (operand.length() - 3) / 2;
          } else if (operand[0] == 'C') {
            LOCCTR += operand.length() - 3;
            prevLOCCTR += operand.length() - 3;
          }
        } else if (opcode == "BASE") {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
        } else if (opcode == "LTORG") {
          operand = " ";
          handle_LTORG(writeDataSuffix,LOCCTR, prevLOCCTR);
        } else if (opcode == "ORG") {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);

          char lastByte = operand[operand.length() - 1];
          while (lastByte == '+' || lastByte == '-' || lastByte == '/' || lastByte == '*') {
            readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
            operand += tempOperand;
            lastByte = operand[operand.length() - 1];
          }

          int tempVariable;
          tempVariable = saveLOCCTR;
          saveLOCCTR = LOCCTR;
          LOCCTR = tempVariable;

          if (SYMTAB[operand].exists == 'y') {
            LOCCTR = stringHexToInt(SYMTAB[operand].address);
          } else {
            bool relative;
            // set error_flag to false
            error_flag = false;
            evaluateExpression(operand, relative, tempOperand, errorFile, error_flag);
            if (!error_flag) {
              LOCCTR = stringHexToInt(tempOperand);
            }
            error_flag = false; // reset error_flag
          }
        } else if (opcode == "EQU") {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          tempOperand = "";
          bool relative;

          if (operand == "*") {
            tempOperand = intToStringHex(LOCCTR - prevLOCCTR, 6);
            relative = 1;
          } else if (if_all_num(operand)) {
            tempOperand = intToStringHex(stoi(operand), 6);
            relative = 0;
          } else {
            char lastByte = operand[operand.length() - 1];

            while (lastByte == '+' || lastByte == '-' || lastByte == '/' || lastByte == '*') {
              readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
              operand += tempOperand;
              lastByte = operand[operand.length() - 1];
            }

            // Code for reading whole operand
            evaluateExpression(operand, relative, tempOperand, errorFile, error_flag);
          }

          SYMTAB[label].name = label;
          SYMTAB[label].address = tempOperand;
          SYMTAB[label].relative = relative;
          prevLOCCTR = LOCCTR - stringHexToInt(tempOperand);
        } else {
        readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
        writeData = "Invalid OPCODE. Found " + opcode + " at address " + intToStringHex(LOCCTR);
        writeToFile(errorFile, writeData);
        error_flag = true;
        }
      
        readFirstNonWhiteSpace(fileLine,index,statusCode,comment,true);

        if(opcode=="EQU" && SYMTAB[label].relative == 0){
          writeData = intToStringHex(LOCCTR-prevLOCCTR) + "\t" + " " + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment;
        } else {
          writeData = intToStringHex(LOCCTR-prevLOCCTR) + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment;
        }
      } else {
        writeData = intToStringHex(LOCCTR-prevLOCCTR) + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment;
      }
      
      writeToFile(intermediateFile,writeData);

      getline(sourceFile,fileLine); //Read next line
      index = 0;
      prevLOCCTR = 0;
      readFirstNonWhiteSpace(fileLine,index,statusCode,label); //Parse label
      readFirstNonWhiteSpace(fileLine,index,statusCode,opcode);//Parse OPCODE
    }

    if(opcode!="END")
    {
      if(SYMTAB[label].exists=='n')
      {
        SYMTAB[label].name = label;
        SYMTAB[label].address = intToStringHex(LOCCTR);
        SYMTAB[label].relative = 1;
        SYMTAB[label].exists = 'y';
      }
      
      LOCCTR=prevLOCCTR=0;

  	  writeToFile(intermediateFile, writeDataPrefix + "\t" + intToStringHex(LOCCTR-prevLOCCTR) + "\t" + "\t" + label + "\t" + opcode);

      getline(sourceFile,fileLine); //Read next line


      readFirstNonWhiteSpace(fileLine,index,statusCode,label); //Parse label
      readFirstNonWhiteSpace(fileLine,index,statusCode,opcode);//Parse OPCODE  
    }
  }

  if (opcode == "END") {
    firstExecutable_Sec = SYMTAB[label].address;
    SYMTAB[firstExecutable_Sec].name = label;
    SYMTAB[firstExecutable_Sec].address = firstExecutable_Sec;
  }

  readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
  readFirstNonWhiteSpace(fileLine, index, statusCode, comment, true);

  handle_LTORG(writeDataSuffix, LOCCTR, prevLOCCTR);

  writeData = intToStringHex(LOCCTR - prevLOCCTR) + "\t" + " " + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment + writeDataSuffix;
  writeToFile(intermediateFile, writeData);

  program_length = LOCCTR - startAddress - 1;

  sourceFile.close();
  intermediateFile.close();
  errorFile.close();

  // Remove SYMTAB entries that don't exists
  for (auto it = SYMTAB.begin(); it != SYMTAB.end(); ) {
      if (it->second.exists == 'n') {
          it = SYMTAB.erase(it);
      } else {
          ++it;
      }
  }
}

bool symtabComparator(const pair<string, struct_label>& a, const pair<string, struct_label>& b) {
  if (a.second.isstart == 'y') return true;
  if (b.second.isstart == 'y') return false;
  return stringHexToInt(a.second.address) < stringHexToInt(b.second.address);
}



int main(int argc, char* argv[]){
  Pass1 pass1;
  pass1.fileName = argv[1];
  load_tables();
  cout<<"\nPerforming PASS1"<<endl;
  cout<<"Writing intermediate file to 'intermediate_"<<pass1.fileName<<"'"<<endl;
  cout<<"Writing error file to 'error_"<<pass1.fileName<<"'"<<endl;
  pass1.pass1();
  cout << "Writing SYMBOL TABLE" << endl;
  printtab.open("tables_" + pass1.fileName);
  writeToFile(printtab, "CSECT Symbol  Value   Length  Flags:\n--------------------------------------");

  vector<pair<string, struct_label>> symtabVec(SYMTAB.begin(), SYMTAB.end());
  sort(symtabVec.begin(), symtabVec.end(), symtabComparator);

  for (const auto& it : symtabVec) {
    string fourthColumn = it.second.isstart == 'y' ? intToStringHex(pass1.program_length) : "";
    string writestring = (it.second.isstart == 'y' ? it.first : "") + "\t" +
                              (it.second.isstart != 'y' ? it.first : "") + "\t" + it.second.address
                               + "\t" + fourthColumn + "\t" + "R";
    writeToFile(printtab, writestring);
  }

  writestring="" ;
  cout<<"Writing LITERAL TABLE"<<endl;
  
  writeToFile(printtab, "\nLiteral Table\nName\tOperand\tAddress\tLength\n--------------------------------------");

  for (auto const& it: LITTAB) {
    // Remove the C and surrounding quotes from the literal value
    string literalValue = it.second.value.substr(2, it.second.value.length() - 4);
    string asciiHexValue = stringToAsciiHex(literalValue);
    string writestring = literalValue + "\t" + asciiHexValue + "\t" + it.second.address + "\t" + to_string(literalValue.length()) + "\n";
    writeToFile(printtab, writestring);
  }

  return 0;
}