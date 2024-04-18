/*Conatains code for the TABLES defined across whole assembler*/
#include<iostream>
#include<map>
#include<string>

using namespace std;

/**
 * @brief Represents an opcode entry in the opcode table.
 */
struct struct_opcode{
    string opcode;   /**< The opcode string. */
    int format;      /**< The format of the opcode. */
    char exists;     /**< Flag indicating if the opcode exists. */

    /**
     * @brief Default constructor for struct_opcode.
     * Initializes the opcode, format, and exists members.
     */
    struct_opcode(){
      opcode="undefined";
      format=0;
      exists='n';
    }
};

/**
 * @struct struct_literal
 * @brief Represents a literal in the assembly code.
 * 
 * This struct stores the value, address, existence flag, and block number of a literal.
 * The value represents the literal's value, the address represents its memory address,
 * the existence flag indicates whether the literal exists or not, and the block number
 * represents the block number where the literal is defined.
 */
struct struct_literal{
  string value;       ///< The value of the literal.
  string address;     ///< The memory address of the literal.
  char exists;        ///< Flag indicating the existence of the literal.

  /**
   * @brief Default constructor for struct_literal.
   * 
   * Initializes the struct_literal object with default values.
   * The value is set to an empty string, the address is set to "?",
   * the block number is set to 0, and the existence flag is set to 'n'.
   */
  struct_literal(){
    value = "";
    address = "?";
    exists = 'n';
  }
};

/**
 * @struct struct_label
 * @brief Represents a label in the assembly program.
 * 
 * This struct contains information about a label, including its address, name, relative flag,
 * block number, and existence flag.
 */
struct struct_label{
     string address; /**< The address of the label. */
     string name; /**< The name of the label. */
     int relative; /**< The relative flag of the label. */
     char exists; /**< The existence flag of the label. */
     char isstart; /**< The flag indicating if the label is a start label. */

     /**
      * @brief Default constructor for struct_label.
      * 
      * Initializes the struct_label object with default values.
      */
     struct_label(){
       name="undefined";
       address="0";
       exists='n';
       relative = 0;
     }
};


/**
 * @struct struct_register
 * @brief Represents a register in the assembly language.
 * 
 * This struct contains information about a register, including its number and existence status.
 */
struct struct_register{
     char num; /**< The number of the register. */
     char exists; /**< The existence status of the register. */
     int value; /**< The value of the register. */
     int location; /**< The location of the register. */

     /**
      * @brief Default constructor for struct_register.
      * 
      * Initializes the register number to 'F' and the existence status to 'n'.
      */
     struct_register(){
       num = 'F';
       exists='n';
       value = 0;
       location = 0;
     }
};

typedef map<string,struct_label> SYMBOL_TABLE_TYPE;
typedef map<string,struct_opcode> OPCODE_TABLE_TYPE;
typedef map<string,struct_register> REG_TABLE_TYPE;
typedef map<string,struct_literal> LIT_TABLE_TYPE;

SYMBOL_TABLE_TYPE SYMTAB;
OPCODE_TABLE_TYPE OPTAB;
REG_TABLE_TYPE REGTAB;
LIT_TABLE_TYPE LITTAB;

void load_REGTAB(){
  REGTAB["A"].num='0';
  REGTAB["A"].exists='y';
  REGTAB["A"].value = 0;
  REGTAB["A"].location = 0;

  REGTAB["X"].num='1';
  REGTAB["X"].exists='y';
  REGTAB["X"].value = 0;
  REGTAB["X"].location = 0;

  REGTAB["L"].num='2';
  REGTAB["L"].exists='y';
  REGTAB["L"].value = 0;
  REGTAB["L"].location = 0;

  REGTAB["B"].num='3';
  REGTAB["B"].exists='y';
  REGTAB["B"].value = 0;
  REGTAB["B"].location = 0;

  REGTAB["S"].num='4';
  REGTAB["S"].exists='y';
  REGTAB["S"].value = 0;
  REGTAB["S"].location = 0;

  REGTAB["T"].num='5';
  REGTAB["T"].exists='y';
  REGTAB["T"].value = 0;
  REGTAB["T"].location = 0;

  REGTAB["F"].num='6';
  REGTAB["F"].exists='y';
  REGTAB["F"].value = 0;
  REGTAB["F"].location = 0;

  REGTAB["PC"].num='8';
  REGTAB["PC"].exists='y';
  REGTAB["PC"].value = 0;
  REGTAB["PC"].location = 0;

  REGTAB["SW"].num='9';
  REGTAB["SW"].exists='y';
  REGTAB["SW"].value = 0;
  REGTAB["SW"].location = 0;
}
void load_OPTAB(){
  OPTAB["ADD"].opcode="18";
  OPTAB["ADD"].format=3;
  OPTAB["ADD"].exists='y';

  OPTAB["ADDF"].opcode="58";
  OPTAB["ADDF"].format=3;
  OPTAB["ADDF"].exists='y';

  OPTAB["ADDR"].opcode="90";
  OPTAB["ADDR"].format=2;
  OPTAB["ADDR"].exists='y';

  OPTAB["AND"].opcode="40";
  OPTAB["AND"].format=3;
  OPTAB["AND"].exists='y';

  OPTAB["CLEAR"].opcode="B4";
  OPTAB["CLEAR"].format=2;
  OPTAB["CLEAR"].exists='y';

  OPTAB["COMP"].opcode="28";
  OPTAB["COMP"].format=3;
  OPTAB["COMP"].exists='y';

  OPTAB["COMPF"].opcode="88";
  OPTAB["COMPF"].format=3;
  OPTAB["COMPF"].exists='y';

  OPTAB["COMPR"].opcode="A0";
  OPTAB["COMPR"].format=2;
  OPTAB["COMPR"].exists='y';

  OPTAB["DIV"].opcode="24";
  OPTAB["DIV"].format=3;
  OPTAB["DIV"].exists='y';

  OPTAB["DIVF"].opcode="64";
  OPTAB["DIVF"].format=3;
  OPTAB["DIVF"].exists='y';

  OPTAB["DIVR"].opcode="9C";
  OPTAB["DIVR"].format=2;
  OPTAB["DIVR"].exists='y';

  OPTAB["FIX"].opcode="C4";
  OPTAB["FIX"].format=1;
  OPTAB["FIX"].exists='y';

  OPTAB["FLOAT"].opcode="C0";
  OPTAB["FLOAT"].format=1;
  OPTAB["FLOAT"].exists='y';

  OPTAB["HIO"].opcode="F4";
  OPTAB["HIO"].format=1;
  OPTAB["HIO"].exists='y';

  OPTAB["J"].opcode="3C";
  OPTAB["J"].format=3;
  OPTAB["J"].exists='y';

  OPTAB["JEQ"].opcode="30";
  OPTAB["JEQ"].format=3;
  OPTAB["JEQ"].exists='y';

  OPTAB["JGT"].opcode="34";
  OPTAB["JGT"].format=3;
  OPTAB["JGT"].exists='y';

  OPTAB["JLT"].opcode="38";
  OPTAB["JLT"].format=3;
  OPTAB["JLT"].exists='y';

  OPTAB["JSUB"].opcode="48";
  OPTAB["JSUB"].format=3;
  OPTAB["JSUB"].exists='y';

  OPTAB["LDA"].opcode="00";
  OPTAB["LDA"].format=3;
  OPTAB["LDA"].exists='y';

  OPTAB["LDB"].opcode="68";
  OPTAB["LDB"].format=3;
  OPTAB["LDB"].exists='y';

  OPTAB["LDCH"].opcode="50";
  OPTAB["LDCH"].format=3;
  OPTAB["LDCH"].exists='y';

  OPTAB["LDF"].opcode="70";
  OPTAB["LDF"].format=3;
  OPTAB["LDF"].exists='y';

  OPTAB["LDL"].opcode="08";
  OPTAB["LDL"].format=3;
  OPTAB["LDL"].exists='y';

  OPTAB["LDS"].opcode="6C";
  OPTAB["LDS"].format=3;
  OPTAB["LDS"].exists='y';

  OPTAB["LDT"].opcode="74";
  OPTAB["LDT"].format=3;
  OPTAB["LDT"].exists='y';

  OPTAB["LDX"].opcode="04";
  OPTAB["LDX"].format=3;
  OPTAB["LDX"].exists='y';

  OPTAB["LPS"].opcode="D0";
  OPTAB["LPS"].format=3;
  OPTAB["LPS"].exists='y';

  OPTAB["MUL"].opcode="20";
  OPTAB["MUL"].format=3;
  OPTAB["MUL"].exists='y';

  OPTAB["MULF"].opcode="60";
  OPTAB["MULF"].format=3;
  OPTAB["MULF"].exists='y';

  OPTAB["MULR"].opcode="98";
  OPTAB["MULR"].format=2;
  OPTAB["MULR"].exists='y';

  OPTAB["NORM"].opcode="C8";
  OPTAB["NORM"].format=1;
  OPTAB["NORM"].exists='y';

  OPTAB["OR"].opcode="44";
  OPTAB["OR"].format=3;
  OPTAB["OR"].exists='y';

  OPTAB["RD"].opcode="D8";
  OPTAB["RD"].format=3;
  OPTAB["RD"].exists='y';

  OPTAB["RMO"].opcode="AC";
  OPTAB["RMO"].format=2;
  OPTAB["RMO"].exists='y';

  OPTAB["RSUB"].opcode="4F";
  OPTAB["RSUB"].format=3;
  OPTAB["RSUB"].exists='y';

  OPTAB["SHIFTL"].opcode="A4";
  OPTAB["SHIFTL"].format=2;
  OPTAB["SHIFTL"].exists='y';

  OPTAB["SHIFTR"].opcode="A8";
  OPTAB["SHIFTR"].format=2;
  OPTAB["SHIFTR"].exists='y';

  OPTAB["SIO"].opcode="F0";
  OPTAB["SIO"].format=1;
  OPTAB["SIO"].exists='y';

  OPTAB["SSK"].opcode="EC";
  OPTAB["SSK"].format=3;
  OPTAB["SSK"].exists='y';

  OPTAB["STA"].opcode="0C";
  OPTAB["STA"].format=3;
  OPTAB["STA"].exists='y';

  OPTAB["STB"].opcode="78";
  OPTAB["STB"].format=3;
  OPTAB["STB"].exists='y';

  OPTAB["STCH"].opcode="54";
  OPTAB["STCH"].format=3;
  OPTAB["STCH"].exists='y';

  OPTAB["STF"].opcode="80";
  OPTAB["STF"].format=3;
  OPTAB["STF"].exists='y';

  OPTAB["STI"].opcode="D4";
  OPTAB["STI"].format=3;
  OPTAB["STI"].exists='y';

  OPTAB["STL"].opcode="14";
  OPTAB["STL"].format=3;
  OPTAB["STL"].exists='y';

  OPTAB["STS"].opcode="7C";
  OPTAB["STS"].format=3;
  OPTAB["STS"].exists='y';

  OPTAB["STSW"].opcode="E8";
  OPTAB["STSW"].format=3;
  OPTAB["STSW"].exists='y';

  OPTAB["STT"].opcode="84";
  OPTAB["STT"].format=3;
  OPTAB["STT"].exists='y';

  OPTAB["STX"].opcode="10";
  OPTAB["STX"].format=3;
  OPTAB["STX"].exists='y';

  OPTAB["SUB"].opcode="1C";
  OPTAB["SUB"].format=3;
  OPTAB["SUB"].exists='y';

  OPTAB["SUBF"].opcode="5C";
  OPTAB["SUBF"].format=3;
  OPTAB["SUBF"].exists='y';

  OPTAB["SUBR"].opcode="94";
  OPTAB["SUBR"].format=2;
  OPTAB["SUBR"].exists='y';

  OPTAB["SVC"].opcode="B0";
  OPTAB["SVC"].format=2;
  OPTAB["SVC"].exists='y';

  OPTAB["TD"].opcode="E0";
  OPTAB["TD"].format=3;
  OPTAB["TD"].exists='y';

  OPTAB["TIO"].opcode="F8";
  OPTAB["TIO"].format=1;
  OPTAB["TIO"].exists='y';

  OPTAB["TIX"].opcode="2C";
  OPTAB["TIX"].format=3;
  OPTAB["TIX"].exists='y';

  OPTAB["TIXR"].opcode="B8";
  OPTAB["TIXR"].format=2;
  OPTAB["TIXR"].exists='y';

  OPTAB["WD"].opcode="DC";
  OPTAB["WD"].format=3;
  OPTAB["WD"].exists='y';
}

void load_tables(){
  load_OPTAB();
  load_REGTAB();
}

