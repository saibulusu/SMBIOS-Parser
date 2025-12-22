#include "SMBIOSData.h"

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





/*
std::vector<SMBIOSStructure> SMBIOSData::getStructureTable() {
  std::vector<SMBIOSStructure*> structure_table;
  SMBIOSStruct* curStruct = (SMBIOSStructure*)this->SMBIOSTableData;
  while ((char*)curStruct < (char*)rawData + rawData->Length) {
    structureTable.push_back(curStruct);
    curStruct = getNextStruct(curStruct);
  }
  return structure_table;
}
*/
