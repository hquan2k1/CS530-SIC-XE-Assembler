/*
 * QUAN NGUYEN 
 * cssc4550
 * CS530, Spring 2024
 * Assignment #2
 * utility.cpp
*/

#include "Pass1.h"
#include "Pass2.h"

using namespace std;

Pass1 pass1;

int baseRegisterVal;

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

bool Pass2:: searchOptab(string opcode)
{
    if(OPTAB[getRealOpcode(opcode)].exists=='y')
    {
        return true;
    }
    return false;
}

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
    }
    return returnVal;
}

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

string Pass2:: assembleObj(string opcode, string operand, int opAd, string address)
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
    pass1.ListingFile.open("listing_"+fileName);
    if(!pass1.ListingFile)
    {
        cout<<"Unable to open file: listing_"<<fileName<<endl;
    }

    pass1.errorFile.open("error_"+fileName);
    if(!pass1.errorFile){
    cout<<"Unable to open file: error_"<<fileName<<endl;
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
    bool literal = false;

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
    while(opcode!="END")
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
                        cout<<operand.substr(1,operand.length()-1)<<endl;
                        if(opcode[0]=='=')
                        {
                            objCode = LITTAB[opcode.substr(1,opcode.length()-1)].value;
                            literal = true;
                        }
                        else
                        {
                            //store 0 as operand address
                            opAd = 0;
                            cout<<opcode<<endl;
                            //set error flag(undefined symbol)
                            writeToFile(pass1.errorFile, "Undefined Symbol at address: " + address);
                        }
                    }
                } 
                else
                {
                    //store 0 as operand address
                    opAd = 0;
                }
                //assemble object code instruction
                
                if(!literal)
                {
                    objCode = assembleObj(opcode, operand, opAd, address);
                }
            }
            else if((opcode=="BYTE"||opcode=="WORD")||opcode=="BASE")
            {
                if(opcode=="BASE")
                {
                    baseRegisterVal = stringHexToInt(fetchSymVal(operand));
                }
            }
        }
        writeListingLine(pass1.ListingFile, isComment, address, label, opcode, operand, objCode, comment);
        readIntFile(pass1.intermediateFile, isComment, address, label, opcode, operand, comment);
        literal = false;
    }
    //LAST LINE
    address = "";
    writeListingLine(pass1.ListingFile, isComment, address, label, opcode, operand, objCode, comment);

    pass1.intermediateFile.close();
    pass1.ListingFile.close();
    pass1.errorFile.close();
};
