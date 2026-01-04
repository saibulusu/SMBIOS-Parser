#include "Functions.h"

SMBIOSData::SMBIOSData(RawSMBIOSData* raw)
  : rawData(raw) {
  std::vector<const SMBIOSStruct*> structureTable;
  
  const uint8_t* ptr = rawData->SMBIOSTableData;
  const uint8_t* end = ptr + rawData->Length;
  
  const SMBIOSStruct* cur = (const SMBIOSStruct*)ptr;
  while ((char*)cur < (char*)end) {
    structureTable.push_back(cur);
    cur = getNextStruct(cur);
  }
  
  this->structureTable = structureTable;
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
  return structureTable;
}

