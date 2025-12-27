#include "SMBIOSParser.h"
#include "SMBIOSPlatform.h"
#include "SMBIOSData.h"
#include "Functions.h"

SMBIOSParser::SMBIOSParser(SMBIOSData& d)
  : data(d) {}

  void SMBIOSParser::displayVersion() {
    std::cout << "v2.0" << std::endl;
  }

void SMBIOSParser::displayHexContents() {
  for (uint32_t i = 0; i < data.raw()->Length; ++i) {
    std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)data.raw()->SMBIOSTableData[i] << " ";
    if (i % 32 == 31) {
      std::cout << std::endl;
    }
  }
  std::cout << std::dec << std::endl;
}

void SMBIOSParser::displayAllStructures() {
  std::vector<const SMBIOSStruct*> structureTable = data.getStructureTable();
  for (long unsigned int i = 0; i < structureTable.size(); ++i) {
    displayStructure(i);
  }
}

void SMBIOSParser::displayStructureTable() {
  std::vector<const SMBIOSStruct*> structureTable = data.getStructureTable();
  std::cout << "Handle\t" << "Type\t" << "Description" << std::endl;
  for (long unsigned int i = 0; i < structureTable.size(); ++i) {
    std::cout << i << "\t" << (int)structureTable[i]->Type << "\t";
    std::cout << getTypeName(structureTable[i]->Type) << std::endl;
  }
}

void SMBIOSParser::displayCommands() {
  std::cout << "cmds: Display available commands" << std::endl;
  std::cout << "all: Display all structures" << std::endl;
  std::cout << "table: Display structure table" << std::endl;
  std::cout << "hex: Display the SMBIOS table bytes in hex" << std::endl;
  std::cout << "<id>: Display the structure with the given ID" << std::endl;
  std::cout << "quit: Exit the program" << std::endl;
}

void SMBIOSParser::displayStructure(int handle) {
  auto structureTable = data.getStructureTable();
  const SMBIOSStruct* curStruct = structureTable[handle];

  if (curStruct->Type == 0) displayBIOSInformation(curStruct);
  else if (curStruct->Type == 1) displaySystemInformation(curStruct);
  else if (curStruct->Type == 2) displayBaseboardInformation(curStruct);
  else if (curStruct->Type == 3) displayChassisInformation(curStruct);
  else if (curStruct->Type == 4) displayProcessorInformation(curStruct);
  else if (curStruct->Type == 5) displayMemoryControllerInformation(curStruct);
  else if (curStruct->Type == 6) displayMemoryModuleInformation(curStruct);
  else if (curStruct->Type == 7) displayCacheInformation(curStruct);
  else if (curStruct->Type == 8) displayPortConnectorInformation(curStruct);
}

int SMBIOSParser::getStructuresCount() {
  return data.getStructureTable().size();
}
