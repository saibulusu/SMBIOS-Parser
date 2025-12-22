#include "SMBIOSParser.h"
#include "SMBIOSData.h"
#include "SMBIOSStructure.h"
#include <iomanip>

SMBIOSParser::SMBIOSParser(SMBIOSData& d)
  : data(d) {}

void SMBIOSParser::parse() {
  parsedStructures.clear();
  auto table = data.getStructureTable();
  if (!table.empty()) {
    parsedStructures.push_back(
      std::make_unique<SMBIOSStructure>(table[0])
    );
  }
}

const std::vector<std::unique_ptr<SMBIOSStructure>>&
SMBIOSParser::structures() const {
  return parsedStructures;
}

void SMBIOSParser::displayVersion() {
  std::cout << "v2.0" << std::endl;
}

void SMBIOSParser::displayHexContents() {
}

void SMBIOSParser::displayCommands() {
  std::cout << "cmds: Display available commands" << std::endl;
  std::cout << "all: Display all structures" << std::endl;
  std::cout << "table: Display structure table" << std::endl;
  std::cout << "hex: Display the SMBIOS table bytes in hex" << std::endl;
  std::cout << "<id>: Display the structure with the given ID" << std::endl;
  std::cout << "quit: Exit the program" << std::endl;
}
