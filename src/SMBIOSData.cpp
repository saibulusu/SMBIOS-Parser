#include "SMBIOSData.h"
#include <iostream>

SMBIOSData::SMBIOSData(RawSMBIOSData* raw)
  : rawData(raw) {
}

SMBIOSData::~SMBIOSData() {
  if (rawData) {
    free(rawData);
  }
}

const RawSMBIOSData* SMBIOSData::raw() const {
  return rawData;
}

std::vector<const SMBIOSStruct*> SMBIOSData::getStructureTable() const {
  std::vector<const SMBIOSStruct*> structureTable;
  
  const uint8_t* ptr = rawData->SMBIOSTableData;
  const uint8_t* end = ptr + rawData->Length;
  
  const SMBIOSStruct* first = reinterpret_cast<const SMBIOSStruct*>(ptr);
  std::cout << "first type: " << (int)first->Type << std::endl;
  std::cout << "first length: " << (int)first->Length << std::endl;
  std::cout << "first handle: " << (int)first->Handle << std::endl;
  structureTable.push_back(first);

  const SMBIOSStruct* second = getNextStruct(first);
  std::cout << "second type: " << (int)second->Type << std::endl;
  std::cout << "second length: " << (int)second->Length << std::endl;
  std::cout << "second handle: " << (int)second->Handle << std::endl;
  structureTable.push_back(second);

/*
  while (ptr < end) {
    const SMBIOSStruct* cur = reinterpret_cast<const SMBIOSStruct*>(ptr);
    structureTable.push_back(cur);

    ptr += cur->Length;
  }
*/
  
  return structureTable;
}

const SMBIOSStruct* SMBIOSData::getNextStruct(const SMBIOSStruct* curStruct) const {
  char* strings_begin = (char*)curStruct + curStruct->Length;
  char* next_strings  = strings_begin + 1;

  // Walk until you find a double null (end of string-set)
  while (*strings_begin != NULL || *next_strings != NULL) {
    ++strings_begin;
    ++next_strings;
  }

  // The structure after the double null
  return (const SMBIOSStruct*)(next_strings + 1);
}
