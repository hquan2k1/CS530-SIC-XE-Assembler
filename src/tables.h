#ifndef TABLES_H
#define TABLES_H

#include<iostream>
#include<map>
#include<string>
#include "utility.h"

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


typedef map<string,struct_label> SYMBOL_TABLE_TYPE;
typedef map<string,struct_opcode> OPCODE_TABLE_TYPE;
typedef map<string,struct_register> REG_TABLE_TYPE;
typedef map<string,struct_literal> LIT_TABLE_TYPE;

extern SYMBOL_TABLE_TYPE SYMTAB;
extern OPCODE_TABLE_TYPE OPTAB;
extern REG_TABLE_TYPE REGTAB;
extern LIT_TABLE_TYPE LITTAB;

void load_REGTAB();
void load_OPTAB();
void load_tables();
void clear_tables();


#endif // TABLES_H