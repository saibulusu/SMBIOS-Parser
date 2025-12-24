#include "SMBIOSParser.h"
#include "SMBIOSPlatform.h"
#include "SMBIOSData.h"
#include "Functions.h"
#include <iomanip>

SMBIOSParser::SMBIOSParser(SMBIOSData& d)
  : data(d) {}

void SMBIOSParser::displayVersion() {
  std::cout << "v2.0" << std::endl;
}

void SMBIOSParser::displayHexContents() {
}

void SMBIOSParser::displayAllStructures() {
  std::vector<const SMBIOSStruct*> structureTable = data.getStructureTable();
  for (long unsigned int i = 0; i < structureTable.size(); ++i) {
    displayStructure(i);
    if (i < structureTable.size() - 1) {
      //std::cout << std::endl;
    }
  }
}

void SMBIOSParser::displayStructureTable() {
  std::vector<const SMBIOSStruct*> structureTable = data.getStructureTable();
  std::cout << "ID\t" << "Type\t" << "Description" << std::endl;
  for (long unsigned int i = 0; i < structureTable.size(); ++i) {
    std::cout << i << "\t" << (int)structureTable[i]->Type << "\t";
    switch (structureTable[i]->Type) {
    case 0:
      std::cout << "BIOS" << std::endl;
      break;
    case 1:
      std::cout << "System" << std::endl;
      break;
    case 2:
      std::cout << "Baseboard" << std::endl;
      break;
    case 3:
      std::cout << "System Enclosure/Chassis" << std::endl;
      break;
    case 4:
      std::cout << "Processor" << std::endl;
      break;
    case 5:
      std::cout << "Memory Controller" << std::endl;
      break;
    case 6:
      std::cout << "Memory Module" << std::endl;
      break;
    case 7:
      std::cout << "Cache" << std::endl;
      break;
    case 8:
      std::cout << "Port Connector" << std::endl;
      break;
    case 9:
      std::cout << "System Slots" << std::endl;
      break;
    case 10:
      std::cout << "On Board Devices" << std::endl;
      break;
    case 11:
      std::cout << "OEM Strings" << std::endl;
      break;
    case 12:
      std::cout << "System Configuration Options" << std::endl;
      break;
    case 13:
      std::cout << "BIOS Language" << std::endl;
      break;
    case 14:
      std::cout << "Group Associations" << std::endl;
      break;
    case 15:
      std::cout << "System Event Log" << std::endl;
      break;
    case 16:
      std::cout << "Physical Memory Array" << std::endl;
      break;
    case 17:
      std::cout << "Memory Device" << std::endl;
      break;
    case 18:
      std::cout << "32-Bit Memory Error" << std::endl;
      break;
    case 19:
      std::cout << "Memory Array Mapped Address" << std::endl;
      break;
    case 20:
      std::cout << "Memory Device Mapped Address" << std::endl;
      break;
    case 21:
      std::cout << "Built-in Pointing Device" << std::endl;
      break;
    case 22:
      std::cout << "Portable Battery" << std::endl;
      break;
    case 23:
      std::cout << "System Reset" << std::endl;
      break;
    case 24:
      std::cout << "Hardware Security" << std::endl;
      break;
    case 25:
      std::cout << "System Power Controls" << std::endl;
      break;
    case 26:
      std::cout << "Voltage Probe" << std::endl;
      break;
    case 27:
      std::cout << "Cooling Device" << std::endl;
      break;
    case 28:
      std::cout << "Temperature Probe" << std::endl;
      break;
    case 29:
      std::cout << "Electrical Current Probe" << std::endl;
      break;
    case 30:
      std::cout << "Out of Band Remote Access" << std::endl;
      break;
    case 31:
      std::cout << "Boot Integrity Services Entry Point" << std::endl;
      break;
    case 32:
      std::cout << "System Boot" << std::endl;
      break;
    case 33:
      std::cout << "64-Bit Memory Error" << std::endl;
      break;
    case 34:
      std::cout << "Management Device" << std::endl;
      break;
    case 35:
      std::cout << "Management Device Component" << std::endl;
      break;
    case 36:
      std::cout << "Management Device Threshold Data" << std::endl;
      break;
    case 37:
      std::cout << "Memory Channel" << std::endl;
      break;
    case 38:
      std::cout << "IPMI Device Information" << std::endl;
      break;
    case 39:
      std::cout << "System Power Supply" << std::endl;
      break;
    case 40:
      std::cout << "Additional" << std::endl;
      break;
    case 41:
      std::cout << "Onboard Devices" << std::endl;
      break;
    case 42:
      std::cout << "Management Controller Host Interface" << std::endl;
      break;
    case 126:
      std::cout << "Inactive" << std::endl;
      break;
    case 127:
      std::cout << "End-of-Table" << std::endl;
      break;
    default:
      std::cout << "Vendor-Specific Structure" << std::endl;
      break;
    }
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
  std::vector<const SMBIOSStruct*> structureTable = data.getStructureTable();
  const SMBIOSStruct* curStruct = structureTable[handle];

  switch (curStruct->Handle) {
  case 0:
    displayBIOSInformation(curStruct);
    break;
  case 1:
    displaySystemInformation(curStruct);
    break;
  case 2:
    displayBaseboardInformation(curStruct);
    break;
  default:
    break;
  }
}
