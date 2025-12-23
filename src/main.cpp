#include "SMBIOSPlatform.h"
#include "SMBIOSData.h"
#include "SMBIOSParser.h"
#include <string>
#include <iostream>

int main() {
  SMBIOSData* data = loadSMBIOSFromLinux();
  SMBIOSParser parser(*data);

  std::cout << "> ";
  std::string input;
  while (std::cin >> input) {
    if (!input.compare("quit")) {
      break;
    } else if (!input.compare("version")) {
      parser.displayVersion();
    } else if (!input.compare("hex")) {
      parser.displayHexContents();
    } else if (!input.compare("all")) {
      parser.displayAllStructures();
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