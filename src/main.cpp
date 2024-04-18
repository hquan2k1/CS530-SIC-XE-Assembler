#include "utility.cpp" 
#include "tables.cpp"
#include "Pass1.h"

using namespace std;

int main(int argc, char* argv[]){
  Pass1 pass1;
  pass1.fileName = argv[1];
  load_tables();
  cout<<"\nPerforming PASS1"<<endl;
  cout<<"Writing intermediate file to 'intermediate_"<<pass1.fileName<<"'"<<endl;
  cout<<"Writing error file to 'error_"<<pass1.fileName<<"'"<<endl;
  pass1.pass1();
  cout << "Writing SYMBOL TABLE" << endl;
  pass1.printtab.open("tables_" + pass1.fileName);
  writeToFile(pass1.printtab, "CSECT Symbol  Value   Length  Flags:\n--------------------------------------");

  vector<pair<string, struct_label>> symtabVec(SYMTAB.begin(), SYMTAB.end());
  sort(symtabVec.begin(), symtabVec.end(), symtabComparator);

  for (const auto& it : symtabVec) {
    string fourthColumn = it.second.isstart == 'y' ? intToStringHex(pass1.program_length) : "";
    string writestring = (it.second.isstart == 'y' ? it.first : "") + "\t" +
                              (it.second.isstart != 'y' ? it.first : "") + "\t" + it.second.address
                               + "\t" + fourthColumn + "\t" + "R";
    writeToFile(pass1.printtab, writestring);
  }

  pass1.writestring="" ;
  cout<<"Writing LITERAL TABLE"<<endl;
  
  writeToFile(pass1.printtab, "\nLiteral Table\nName\tOperand\tAddress\tLength\n--------------------------------------");

  for (auto const& it: LITTAB) {
    // Remove the C and surrounding quotes from the literal value
    string literalValue = it.second.value.substr(2, it.second.value.length() - 4);
    string asciiHexValue = stringToAsciiHex(literalValue);
    string writestring = literalValue + "\t" + asciiHexValue + "\t" + it.second.address + "\t" + to_string(literalValue.length()) + "\n";
    writeToFile(pass1.printtab, writestring);
  }

  return 0;
}