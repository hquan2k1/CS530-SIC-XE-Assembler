//Pass2.cpp
#include "Pass2.h"
#include "utility.cpp"
#include "tables.cpp"
#include <fstream>
#include <sstream>

using namespace std;

ifstream intermediateFile;
ofstream ListingFile

string writestring

string readSection(string data, int& ind)
{
    string tempBuffer = "";

    while(ind<data.length() && data[ind] != '\t')
    {
        tempBuffer += data[ind];
        ind++;
    }
    ind++;
    return tempBuffer
}

bool readIntFile(ifstream& readFile, bool& isComment, string& address, string& label, string& opcode, string& operand, string& comment)
{
    string line = "";
    string tempBuffer = "";
    int ind = 0;
    if(!getline(readFile, line))
    {
        return false;
    }
    if(fileLine[ind]=='.')
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

    address = readSection(line, ind));
    label = readSection(line,ind);
    opcode = readSection(line, ind);
    operand = readSection(lind, ind);
    comment = readSection(line, ind);
    return true;
}

void writeListingLine(ofStream writeFile, bool isComment, string& address, string& label, string& opcode, string& operand, string &objCode, string& comment)
{
    string writeData = "";
    string tempBuffer = "";
    if(isComment)
    {
        writeData+=comment;
    }
    else
    {
        writeData+= address + '\t' + label + '\t' + opcode + '\t' + operand + '\t' + comment;
    }
    writeFile<<writeData<<endl;
    isComment = false;
    address = "";
    label = "";
    opcode = "";
    operand = "";
    objcode = "";
    comment = "";
}

bool searchOptab(string opcode)
{
    if(OPTAB[getRealOpcode(opcode)].exists=='y')
    {
        return true;
    }
    return false;
}

bool searchSymTab(string operand)
{
    string tempBuffer = "";
    int i = 0;
    while(i<operand.length()&&operand[i]!=",")
    {
        tempBuffer+=operand[i];
    }
    if(SYMTAB[tempBuffer].exists=='y')
    {
        return true;
    }
    return false;
}

bool symbolInOperand(string operand)
{
    if (operand.length()>0)
    {
        return (operand[0]!='#');
    }
    return false;
}

int fetchSymVal(string operand)
{

}

string assembleObj(string opcode, int opAd, )
{

}



Pass2()
{
    //OPEN FILES
    string tempBuffer;
    intermediateFile.open("intermediate_"+fileName);//begin
    if(!intermediateFile)
    {
        cout<<"Unable to open file: intermediate_"<<fileName<<endl;
        exit(1);
    }
    ListingFile.open("listing_"+fileName);
    if(!ListingFile)
    {
        cout<<"Unable to open file: listing_"<<fileName<<endl;
    }

    string address = "";
    string label = "";
    string opcode = "";
    string operand = "";
    string comment = "";
    bool isComment = false;
    string objCode = "";
    int opAd = 0;

    getLine(intermediateFile, tempBuffer);
    //LOGIC FROM BOOK
    readIntFile(intermediateFile, isComment, adress, label, opcode, operand, comment);
    if(opcode == "START")
    {
        writeListingLine(listingFile, isComment, address, label, opcode, operand, comment, objcode);
        readIntFile(intermediateFile, isComment, adress, label, opcode, operand, comment);
    }
    while(opcode!="END")
    {
        if (isComment == false)
        {
            if (searchOptab(opcode))
            {
                if (symbolInOperand(operand))
                {
                    if (searchSymtab(operand))
                    {
                        //store Symbol value as operand address
                        opAd = fetchSymVal(operand);
                    } else
                    {
                        //store 0 as operand address
                        opAd = 0;
                        //set error flag(undefined symbol)
                    }
                } else
                {
                    //store 0 as operand address
                    opAd = 0;
                    //assemble object code instruction
                    objCode = assembleObj(opAd);
                }
            }
            else if(opcode=="BYTE"||opcode=="WORD")
            {
                //convert constant to object code
                ? = assembleObj();
            }
        }
        writeListingLine(listingFile, isComment, address, label, opcode, operand, comment, objcode);
        readIntFile(intermediateFile, isComment, adress, label, opcode, operand, comment);
    }
    //LAST LINE
    writeListingLine();
};

