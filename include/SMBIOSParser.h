#pragma once

#include <vector>
#include <memory>
#include <iostream>

class SMBIOSData;
class SMBIOSStructure;

class SMBIOSParser {
public:
  explicit SMBIOSParser(SMBIOSData& data);

  void parse();

  const std::vector<std::unique_ptr<SMBIOSStructure>>&
  structures() const;

  void displayVersion();
  void displayHexContents();
  void displayAllStructures();
  void displayStructureTable();
  void displayCommands();
  void displayStructure(int handle);

private:
  SMBIOSData& data;
  std::vector<std::unique_ptr<SMBIOSStructure>> parsedStructures;
};
