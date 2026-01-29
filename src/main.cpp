#include "SMBIOSPlatform.h"
#include "SMBIOSData.h"
#include "SMBIOSParser.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
  SMBIOSData* data = loadSMBIOS();
  SMBIOSParser parser(*data);

  if (argc == 1) {
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
        try {
          int index = std::stoi(input);
          if (index < 0 || index >= parser.getStructuresCount()){
            std::cout << "ERROR: Out of bounds" << std::endl;
          }
          else {
            parser.displayStructure(index);
          }
        }
        catch (std::exception& e) {
          std::cout << "ERROR: Invalid command" << std::endl;
        }      
      }

      std::cout << "> ";
    }
  } else if (argc == 2) {
    std::string input = argv[1];
    if (!input.compare("version")) {
      parser.displayVersion();
    } else if (!input.compare("hex")) {
      parser.displayHexContents();
    } else if (!input.compare("all")) {
      parser.displayAllStructures();
    } else if (!input.compare("table")) {
      parser.displayStructureTable();
    } else {
      std::cout << "ERROR: Invalid argument" << std::endl;
    }
  } else {
    std::cout << "ERROR: Invalid number of arguments" << std::endl;
  }

  delete data;
  
  return 0;
}