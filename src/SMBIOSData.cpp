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
  
  const SMBIOSStruct* cur = (const SMBIOSStruct*)ptr;
  while ((char*)cur < (char*)end) {
    structureTable.push_back(cur);
    cur = getNextStruct(cur);
  }

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
