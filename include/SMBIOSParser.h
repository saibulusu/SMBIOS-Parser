#pragma once

#include "SMBIOSData.h"
#include "SMBIOSPlatform.h"
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

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

  int getStructuresCount();

private:
  SMBIOSData& data;
  
  void displayBIOSInformation(const SMBIOSStruct* curStruct); // type 0
  void displaySystemInformation(const SMBIOSStruct* curStruct); // type 1
  void displayBaseboardInformation(const SMBIOSStruct* curStruct); // type 2
  void displayChassisInformation(const SMBIOSStruct* curStruct); // type 3
  void displayProcessorInformation(const SMBIOSStruct* curStruct); // type 4
  void displayMemoryControllerInformation(const SMBIOSStruct* curStruct); // type 5
  void displayMemoryModuleInformation(const SMBIOSStruct* curStruct); // type 6

  void displayVendorSpecificInformation(const SMBIOSStruct* curStruct);
};
