#include "SMBIOSData.h"

void displayCommands() {
  std::cout << "cmds: Display available commands" << std::endl;
  std::cout << "all: Display all structures" << std::endl;
  std::cout << "table: Display structure table" << std::endl;
  std::cout << "hex: Display the SMBIOS table bytes in hex" << std::endl;
  std::cout << "<id>: Display the structure with the given ID" << std::endl;
  std::cout << "quit: Exit the program" << std::endl;
}

int main() {
  SMBIOSData smbiosData = SMBIOSData::fromLinux();
  std::cout << "SMBIOS table length: " << smbiosData.getLength() << std::endl;

  //rawData.displayCommands();
  std::cout << "> ";
  std::string input;
  while (std::cin >> input) {
    if (input.compare("quit") == 0) {
      break;
    }
    else if (input.compare("hex") == 0) {
      //displayHexContents(rawData);
    }
    else if (input.compare("all") == 0) {
      //displayAllStructures(rawData);
    }
    else if (input.compare("table") == 0) {
      // displayStructureTable(rawData);
    }
    else if (input.compare("cmds") == 0) {
      //displayCommands();
    }
    else {
      try {
        int index = std::stoi(input);
        /*
        if (index < 0 || index >= getStructureTable(rawData).size()) {
          std::cout << "ERROR: Out of bounds" << std::endl;
        }
        else {
          //rawData.displayStructure(rawData, index);
        }
        */
      }
      catch (std::exception& e) {
        std::cout << "ERROR: Invalid command" << std::endl;
      }
    }
    
    std::cout << "> ";
  }

  return 0;
}