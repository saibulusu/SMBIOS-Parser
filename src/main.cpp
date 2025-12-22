#include "SMBIOSPlatform.h"
#include "SMBIOSData.h"
#include "SMBIOSStructure.h"
#include "SMBIOSParser.h"
#include <string>
#include <iostream>

int main() {
  SMBIOSData* data = loadSMBIOSFromLinux();
  SMBIOSParser parser(*data);
  parser.parse();

  std::cout << "> ";
  std::string input;
  while (std::cin >> input) {
    if (!input.compare("quit")) {
      break;
    } else if (!input.compare("version")) {
      parser.displayVersion();
    } else if (!input.compare("hex")) {

    } else if (!input.compare("all")) {

    } else if (!input.compare("table")) {
      parser.displayStructureTable();
    } else if (!input.compare("cmds")) {
      parser.displayCommands();
    } else {
      
    }

    std::cout << "> ";
  }

  delete data;
  
  return 0;
}