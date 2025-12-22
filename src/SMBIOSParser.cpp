#include "SMBIOSParser.h"
#include "SMBIOSData.h"
#include "SMBIOSStructure.h"

SMBIOSParser::SMBIOSParser(SMBIOSData& d)
  : data(d) {}

void SMBIOSParser::parse() {
  parsedStructures.clear();
/*
  auto table = data.getStructureTable();
  if (!table.empty()) {
    // wrap first structure in SMBIOSStructure
    parsedStructures.push_back(
      std::make_unique<SMBIOSStructure>(table[0])
    );
  }
*/
}

const std::vector<std::unique_ptr<SMBIOSStructure>>&
SMBIOSParser::structures() const {
  return parsedStructures;
}
