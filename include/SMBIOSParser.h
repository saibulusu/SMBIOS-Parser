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
};
