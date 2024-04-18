/*
 * QUAN NGUYEN , IAN GOWER
 * cssc4550 , cssc4053
 * CS530, Spring 2024
 * Assignment #2
 * Pass2.cpp
*/

#include "Pass1.h"
#include "Pass2.h"

using namespace std;

Pass1 pass1;

int baseRegisterVal;

/**
 * @brief Reads a section of data from a given string.
 * 
 * This function reads a section of data from the given string starting from the specified index.
 * It continues reading until it encounters a tab character or reaches the end of the string.
 * The section of data is stored in a temporary buffer and returned as a string.
 * 
 * @param data The string from which to read the section of data.
 * @param ind The index from which to start reading the section of data.
 * @return The section of data read from the string.
 */
string Pass2:: readSection(string data, int& ind)
{
    string tempBuffer = "";

    while(ind<data.length() && data[ind] != '\t')
    {
        tempBuffer += data[ind];
        ind++;
    }
    ind++;

    if(tempBuffer==" ")
    {
        tempBuffer = "";
    }
    return tempBuffer;
}

/**
 * Reads a line from the input file and extracts the different fields.
 *
 * @param readFile The input file stream to read from.
 * @param isComment A boolean reference to store whether the line is a comment or not.
 * @param address A string reference to store the address field.
 * @param label A string reference to store the label field.
 * @param opcode A string reference to store the opcode field.
 * @param operand A string reference to store the operand field.
 * @param comment A string reference to store the comment field.
 * @return True if a line was successfully read, false otherwise.
 */
bool Pass2:: readIntFile(ifstream& readFile, bool& isComment, string& address, string& label, string& opcode, string& operand, string& comment)
{
    string line = "";
    string tempBuffer = "";
    int ind = 0;
    if(!getline(readFile, line))
    {
        return false;
    }
    if(line[ind]=='.')
    {
        isComment = true;
    }
    else
    {
        isComment = false;
    }
    if(isComment)
    {
        comment = line;
        return true;
    }

    address = readSection(line, ind);
    label = readSection(line,ind);
    opcode = readSection(line, ind);
    operand = readSection(line, ind);
    comment = readSection(line, ind);
    return true;
}

/**
 * Writes a line to the listing file.
 *
 * @param writeFile The output file stream to write to.
 * @param isComment A flag indicating if the line is a comment.
 * @param address The address of the line.
 * @param label The label of the line.
 * @param opcode The opcode of the line.
 * @param operand The operand of the line.
 * @param objCode The object code of the line.
 * @param comment The comment of the line.
 */
void Pass2:: writeListingLine(ofstream& writeFile, bool isComment, string& address, string& label, string& opcode, string& operand, string &objCode, string&comment)
{
    string writeData = "";
    string tempBuffer = "";
    if(isComment)
    {
        writeData+=comment;
    }
    else
    {
        int i = 0;
        if(address.length()==5)
        {
            writeData+= address.substr(1,4) + "    "+ label;
        }
        else
        {
            writeData+= address + "        ";
        }
        for( ; i<8-label.length();i++)
        {
            writeData+=' ';
        }
        if(opcode[0]!='+'&&opcode[0]!='=')
        {
            writeData+=' ';
            i = 1;
        }
        else
        {
            i = 0;
        }
        writeData+= opcode;
        for( ; i<9-opcode.length(); i++)
        {
            writeData+=' ';
        }
        if((operand[0]!='#'&&operand[0]!='@')&&operand[0]!='=')
        {
            writeData+=' ';
            i = 1;
        }
        else
        {
            i = 0;
        }
        writeData+= operand;
        for( ; i<26-operand.length(); i++)
        {
            writeData+=' ';
        }
        writeData+= objCode;
    }
    writeFile<<writeData<<endl;
    isComment = false;
    address = ""; 
    label = "";
    opcode = "";
    operand = "";
    objCode = "";
    comment = "";
}

/**
 * Searches for an opcode in the optab (opcode table).
 *
 * @param opcode The opcode to search for.
 * @return True if the opcode is found in the optab, false otherwise.
 */
bool Pass2:: searchOptab(string opcode)
{
    if(OPTAB[getRealOpcode(opcode)].exists=='y')
    {
        return true;
    }
    return false;
}

/**
 * Searches the symbol table for a given operand.
 *
 * @param operand The operand to search for in the symbol table.
 * @return True if the operand is found in the symbol table, false otherwise.
 */
bool Pass2:: searchSymTab(string operand)
{
    string tempBuffer = "";
    int i = 0;
    if(operand[i]=='#'||operand[i]=='@')
    {
        i=1;
    }
    while(i<operand.length()&&operand[i]!=',')
    {
        tempBuffer+=operand[i];
        i++;
    }
    if(SYMTAB[tempBuffer].exists=='y')
    {
        return true;
    }
    return false;
}

/**
 * Checks if a symbol is present in the operand.
 *
 * @param operand The operand to check.
 * @return True if the symbol is present in the operand, false otherwise.
 */
bool Pass2:: symbolInOperand(string operand)
{
    bool returnVal = false;
    int i = 0;
    if (operand.length()>0)
    {
        if(operand[0]=='#')
        {
            i = 1; 
            
        }
        while(i<operand.length())
        {
            if(!isdigit(operand[i]))
            {
                returnVal = true;
            }
            i++;
        }
        if(returnVal)
        {
            string tempBuffer = "";
            int ind = 0;
            while(ind<operand.length()&&operand[ind]!=',')
            {
                tempBuffer+=operand[ind];
                ind++;
            }
            returnVal = REGTAB[tempBuffer].exists == 'n';
        }
    }
    return returnVal;
}

/**
 * Retrieves the value associated with a given symbol.
 *
 * @param operand The symbol for which to fetch the value.
 * @return The value associated with the symbol, or an empty string if the symbol is not found.
 */
string Pass2:: fetchSymVal(string operand)
{
    string tempBuffer="";
    int i = 0;
    if(operand[0]=='@'||operand[0]=='#')
    {
        i=1;
    }

    while(i<operand.length()&&operand[i]!=',')
    {
        tempBuffer+=operand[i];
        i++;
    }
    return SYMTAB[tempBuffer].address;

}

/**
 * Assembles the object code for a given opcode, operand, and other parameters.
 *
 * @param opcode The opcode of the instruction.
 * @param operand The operand of the instruction.
 * @param opAd The operand address.
 * @param address The address of the instruction.
 * @param format The format of the instruction.
 * @return The assembled object code.
 */
string Pass2:: assembleObj(string opcode, string operand, int opAd, string address, int format)
{
    string returnVal = "";
    int opcd = 0x0;
    bool x = false;
    bool ex = false;
    if(operand[operand.length()-1]=='X')
    {
        x = true;
    }
    if(opcode[0]=='+')
    {
        ex = true;
    }
    opcd = stringHexToInt(OPTAB[getRealOpcode(opcode)].opcode);
    if(format==1)
    {
        returnVal+=intToStringHex(opcd).substr(3,2);
        return returnVal;
    }
    if(format==2)
    {
        returnVal+=intToStringHex(opcd).substr(3,2);
        string tempBuffer = "";
        int ind = 0;
        while(ind<operand.length()&&operand[ind]!=',')
        {
            tempBuffer+=operand[ind];
            ind++;
        }
        ind++;
        if(REGTAB[tempBuffer].exists=='y')
        {
            returnVal+=REGTAB[tempBuffer].num;
        }
        tempBuffer="";
        while(ind<operand.length()&&operand[ind]!=',')
        {
            tempBuffer+=operand[ind];
            ind++;
        }
        if(tempBuffer!="")
        {
            if(REGTAB[tempBuffer].exists=='y')
            {
                returnVal+=REGTAB[tempBuffer].num;
            }
        }
        else{
            returnVal+='0';
        }
        return returnVal;
    }
    if(operand[0]=='@')
    {
        opcd+=2;
    }
    else if(operand[0]=='#')
    {
        opcd+=1;
    }
    else
    {
        opcd+=3;
    }
    returnVal+= intToStringHex(opcd).substr(3,2);
    if(ex)
    {
        returnVal+='1';
        returnVal+=intToStringHex(opAd);
    }
    else if(operand[0]=='#'&&isdigit(operand[1]))
    {
        returnVal+=intToStringHex(opAd).substr(1,4);
    }
    else if(opAd==0)
    {
        returnVal+="0000";
    }
    else
    {
        int dist = opAd-stringHexToInt(address)-0x3;
        if((dist>2047||dist<-2048))
        {
            dist = opAd - baseRegisterVal;
            x ? returnVal+="C":returnVal+="4";
            returnVal+=intToStringHex(dist).substr(2,3);
        }
        else
        {
            x ? returnVal+="A":returnVal+="2";
            returnVal+=intToStringHex(dist).substr(2,3);
        }

    }
    return returnVal;

}



/**
 * Performs the second pass of the assembler.
 * This pass generates the object code and writes it to the output file.
 */
void Pass2::pass2()
{
    string fileName_noEXT = fileName.substr(0, fileName.length() - 4);
    //OPEN FILES
    string tempBuffer;
    pass1.intermediateFile.open(fileName_noEXT + ".i");//begin
    if(!pass1.intermediateFile)
    {
        cout << "Unable to open file: " << fileName_noEXT << ".st" << endl;
        exit(1);
    }
    pass1.ListingFile.open(fileName_noEXT + ".l");
    if(!pass1.ListingFile)
    {
        cout<<"Unable to open file: "<< fileName_noEXT <<".l"<<endl;
        exit(1);
    }

    pass1.errorFile.open(fileName_noEXT + ".e");
    if(!pass1.errorFile){
    cout<<"Unable to open file: "<<fileName_noEXT + ".e"<<endl;
    exit(1);
    }
    writeToFile(pass1.errorFile,"************PASS2************");  

    string address = "";
    string label = "";
    string opcode = "";
    string operand = "";
    string comment = "";
    bool isComment = false;
    string objCode = "";
    int opAd = 0;
    int format;

    getline(pass1.intermediateFile, tempBuffer);
    //LOGIC FROM BOOK
    readIntFile(pass1.intermediateFile, isComment, address, label, opcode, operand, comment);
    writeListingLine(pass1.ListingFile, isComment, address, label, opcode, operand, objCode, comment);
    readIntFile(pass1.intermediateFile, isComment, address, label, opcode, operand, comment);
    if(opcode == "START")
    {
        writeListingLine(pass1.ListingFile, isComment, address, label, opcode, operand, objCode, comment);
        readIntFile(pass1.intermediateFile, isComment, address, label, opcode, operand, comment);
    }
    while(opcode!="END"&&operand!="END")
    {
        if (isComment == false)
        {
            if (searchOptab(opcode))
            {
                if (symbolInOperand(operand))
                {
                    if (searchSymTab(operand))
                    {
                        //store Symbol value as operand address
                        opAd = stringHexToInt(fetchSymVal(operand));
                    } 
                    else if (LITTAB[operand.substr(1,operand.length()-1)].exists=='y')
                    {
                        opAd = stringHexToInt(LITTAB[operand.substr(1,operand.length()-1)].address);
                    }
                    else
                    {
                        //store 0 as operand address
                        opAd = 0;
                        //set error flag(undefined symbol)
                        writeToFile(pass1.errorFile, "Undefined Symbol at address: " + address);
                    }
                } 
                else
                {
                    if(operand[0]=='#')
                    {
                        opAd = stoi(operand.substr(1,operand.length()));
                    }
                    //store 0 as operand address
                    else
                    {
                        opAd = 0;
                    }                    
                }
                //assemble object code instruction
                format = OPTAB[getRealOpcode(opcode)].format;
                objCode = assembleObj(opcode, operand, opAd, address, format);
            }
            else if((opcode=="BYTE"||opcode=="WORD")||opcode=="BASE")
            {
                if(opcode=="BASE")
                {
                    baseRegisterVal = stringHexToInt(fetchSymVal(operand));
                }
                if(opcode=="BYTE"||opcode=="WORD")
                {
                    objCode="";
                    if(operand.length()>0)
                    {
                        if(operand[0]=='X')
                        {
                            for(int i = 2; i<operand.length()-1;i++)
                            {
                                objCode+=(operand[i]);
                            }
                        }
                        else
                        {
                            for(int i = 2; i<operand.length()-1;i++)
                            {
                                objCode+=intToStringHex((int)operand[i]).substr(3,2);
                            }
                        }
                    }
                }
            }
            else if(opcode[0]=='=')
            {
                objCode="";
                for(int i = 3; i<opcode.length()-1;i++)
                {
                    objCode+=intToStringHex((int)opcode[i]).substr(3,2);
                }
                
            }
        }
        writeListingLine(pass1.ListingFile, isComment, address, label, opcode, operand, objCode, comment);
        readIntFile(pass1.intermediateFile, isComment, address, label, opcode, operand, comment);
    }
    //LAST LINE
    address = "";
    writeListingLine(pass1.ListingFile, isComment, address, label, operand, comment, objCode, opcode);

    pass1.intermediateFile.close();
    pass1.ListingFile.close();
    pass1.errorFile.close();
};
