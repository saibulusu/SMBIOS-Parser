#pragma once

#include <vector>
#include <memory>

class SMBIOSData;
class SMBIOSStructure;

class SMBIOSParser {
public:
  explicit SMBIOSParser(SMBIOSData& data); // constructor

  void parse(); // read raw table & build structures

  const std::vector<std::unique_ptr<SMBIOSStructure>>&
  structures() const; // read-only view of parsed results

private:
  SMBIOSData& data; // raw data (wrapper via SMBIOSData)
  std::vector<std::unique_ptr<SMBIOSStructure>> parsedStructures; // list of structures
};
