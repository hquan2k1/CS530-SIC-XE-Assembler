#include "Pass1.h"

using namespace std;

/**
 * @brief Comparator function for sorting symbols in the symbol table.
 * 
 * This function compares two symbols based on their addresses. If one of the symbols
 * has the 'isstart' flag set to 'y', it is considered smaller and will be placed before
 * the other symbol. If both symbols have the 'isstart' flag set to 'n', they are compared
 * based on their addresses in hexadecimal format.
 * 
 * @param a The first symbol to compare.
 * @param b The second symbol to compare.
 * @return true if a should be placed before b in the sorted symbol table, false otherwise.
 */
bool symtabComparator(const std::pair<std::string, struct_label>& a, const std::pair<std::string, struct_label>& b) {
  if (a.second.isstart == 'y') return true;
  if (b.second.isstart == 'y') return false;
  return stringHexToInt(a.second.address) < stringHexToInt(b.second.address);
}

int main(int argc, char* argv[]) {
  
  for (int i = 1; i < argc; i++) {
    Pass1 pass1;
    pass1.fileName = argv[i];
    string fileName_noEXT = pass1.fileName.substr(0, pass1.fileName.length() - 4);

    if (pass1.printtab.is_open()) pass1.printtab.close();

    clear_tables();
    load_tables();

    cout << "\nPerforming PASS1" << endl;
    cout << "Writing intermediate file to " << fileName_noEXT << ".i" << endl;
    cout << "Writing error file to " << fileName_noEXT << ".e" << endl;
    pass1.pass1();

    cout << "Writing SYMBOL TABLE" << endl;
    pass1.printtab.open(fileName_noEXT + ".st");
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

    pass1.writestring = "";
    cout << "Writing LITERAL TABLE" << endl;
  
    writeToFile(pass1.printtab, "\nLiteral Table\nName\tOperand\tAddress\tLength\n--------------------------------------");

    for (auto const& it: LITTAB) {
      // Remove the C and surrounding quotes from the literal value
      string literalValue = it.second.value.substr(2, it.second.value.length() - 4);
      string asciiHexValue = stringToAsciiHex(literalValue);
      string writestring = literalValue + "\t" + asciiHexValue + "\t" + it.second.address + "\t" + to_string(literalValue.length()) + "\n";
      writeToFile(pass1.printtab, writestring);
    }

    pass1.printtab.close();
  }

  return 0;
}
