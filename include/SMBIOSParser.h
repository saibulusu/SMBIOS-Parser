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
  void displayBIOSInformation(const SMBIOSStruct* curStruct);
  void displaySystemInformation(const SMBIOSStruct* curStruct);
  void displayBaseboardInformation(const SMBIOSStruct* curStruct);

  void displayVendorSpecificInformation(const SMBIOSStruct* curStruct);
};
