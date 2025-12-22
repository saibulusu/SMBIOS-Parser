#pragma once

#include "SMBIOSData.h"

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

SMBIOSData* loadSMBIOSFromLinux();
