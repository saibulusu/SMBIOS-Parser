#pragma once

#include <vector>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#pragma pack(push, 1)
struct RawSMBIOSData {
  uint8_t  Used20CallingMethod;   // often 0 on Linux
  uint8_t  SMBIOSMajorVersion;    // filled from entry point if desired
  uint8_t  SMBIOSMinorVersion;
  uint8_t  DmiRevision;
  uint32_t Length;                // length of SMBIOS structure table
  uint8_t  SMBIOSTableData[];     // raw table bytes
};
#pragma pack(pop)

struct SMBIOSStruct {
  uint8_t Type;
  uint8_t Length;
  uint16_t Handle;
};

struct SMBIOSStruct;

class SMBIOSData {
public:
  explicit SMBIOSData(RawSMBIOSData* raw); // constructor
  ~SMBIOSData(); // destructor

  std::vector<const SMBIOSStruct*> getStructureTable() const;

  const RawSMBIOSData* raw() const; // read-only access to firmware data

private:
  RawSMBIOSData* rawData; // raw data
  std::vector<const SMBIOSStruct*> structureTable; // table of pointers
};
