#pragma once

#include "SMBIOSData.h"
#include "SMBIOSPlatform.h"
#include <vector>
#include <memory>
#include <iostream>

class SMBIOSData;

class SMBIOSParser {
public:
  explicit SMBIOSParser(SMBIOSData& data);

  void displayVersion();
  void displayHexContents();
  void displayAllStructures();
  void displayStructureTable();
  void displayCommands();
  void displayStructure(int handle);

private:
  SMBIOSData& data;
  void displayType0Structure(const SMBIOSStruct* curStruct);
  void displayType1Structure(const SMBIOSStruct* curStruct);
  void displayType2Structure(const SMBIOSStruct* curStruct);
  void displayType3Structure(const SMBIOSStruct* curStruct);
  void displayType4Structure(const SMBIOSStruct* curStruct);
  void displayTypeOtherStructure(const SMBIOSStruct* curStruct);
};
