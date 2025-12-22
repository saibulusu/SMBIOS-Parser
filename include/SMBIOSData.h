#pragma once

#include <vector>
#include <cstdint>
#include <cstdlib>

struct RawSMBIOSData;
struct SMBIOSStruct;

class SMBIOSData {
public:
  explicit SMBIOSData(RawSMBIOSData* raw); // constructor
  ~SMBIOSData(); // destructor

  std::vector<const SMBIOSStruct*> getStructureTable() const;

  const RawSMBIOSData* raw() const; // read-only access to firmware data

private:
  RawSMBIOSData* rawData; // raw data
};
