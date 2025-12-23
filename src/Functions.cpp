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
