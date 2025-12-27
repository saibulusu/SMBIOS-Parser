#include "Functions.h"

std::vector<std::string> getStrings(const SMBIOSStruct* curStruct) {
  std::vector<std::string> strings;
  std::string res = "";
  strings.push_back(res);
  char* curChar = (char*)curStruct + curStruct->Length;
  const SMBIOSStruct* next_struct = getNextStruct(curStruct);

  while (curChar < (char*)next_struct) {
    res.push_back(*curChar);
    if (*curChar == '\0') {
      strings.push_back(res);
      res = "";
    }
    ++curChar;
  }
  return strings;
}

const SMBIOSStruct* getNextStruct(const SMBIOSStruct* curStruct) {
  char* strings_begin = (char*)curStruct + curStruct->Length;
  char* next_strings  = strings_begin + 1;

  // Walk until you find a double null (end of string-set)
  while (*strings_begin != '\0' || *next_strings != '\0') {
    ++strings_begin;
    ++next_strings;
  }

  // The structure after the double null
  return (const SMBIOSStruct*)(next_strings + 1);
}

int getBit(uint8_t bytes[], int bitNum, int numBytes) {
  int whichBit = numBytes - 1 - bitNum / 8;
  bitNum %= 8;
  return getBit(bytes[whichBit], bitNum);
}

int getBit(uint8_t byte, int bitNum) {
  return (byte >> bitNum) % 2;
}

int getBit(uint16_t word, int bitNum) {
  return (word >> bitNum) % 2;
}

int getBits(uint8_t byte, int startBit, int endBit) {
  return (byte >> endBit) % (1 << (startBit - endBit));
}

int getBits(uint16_t word, int startBit, int endBit) {
  return (word >> endBit) % (1 << (startBit - endBit));
}

std::string getTypeName(uint8_t type) {
  switch (type) {
    case 0: return "BIOS";
    case 1: return "System";
    case 2: return "Baseboard";
    case 3: return "System Enclosure/Chassis";
    case 4: return "Processor";
    case 5: return "Memory Controller";
    case 6: return "Memory Module";
    case 7: return "Cache";
    case 8: return "Port Connector";
    case 9: return "System Slots";
    case 10: return "On Board Devices";
    case 11: return "OEM Strings";
    case 12: return "System Configuration Options";
    case 13: return "BIOS Language";
    case 14: return "Group Associations";
    case 15: return "System Event Log";
    case 16: return "Physical Memory Array";
    case 17: return "Memory Device";
    case 18: return "32-Bit Memory Error";
    case 19: return "Memory Array Mapped Address";
    case 20: return "Memory Device Mapped Address";
    case 21: return "Built-in Pointing Device";
    case 22: return "Portable Battery";
    case 23: return "System Reset";
    case 24: return "Hardware Security";
    case 25: return "System Power Controls";
    case 26: return "Voltage Probe";
    case 27: return "Cooling Device";
    case 28: return "Temperature Probe";
    case 29: return "Electrical Current Probe";
    case 30: return "Out of Band Remote Access";
    case 31: return "Boot Integrity Services Entry Point";
    case 32: return "System Boot";
    case 33: return "64-Bit Memory Error";
    case 34: return "Management Device";
    case 35: return "Management Device Component";
    case 36: return "Management Device Threshold Data";
    case 37: return "Memory Channel";
    case 38: return "IPMI Device Information";
    case 39: return "System Power Supply";
    case 40: return "Additional";
    case 41: return "Onboard Devices";
    case 42: return "Management Controller Host Interface";
    case 126: return "Inactive";
    case 127: return "End-of-Table";
    default: return "Vendor-Specific Structure";
  }
}
