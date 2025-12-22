#include "SMBIOSStructure.h"

std::string SMBIOSStructure::description() {
  return "SMBIOS structure of type" + header->Type;
}

std::string SMBIOSStructure::toString() {
  return "SMBIOS structure of type" + header->Type;
}
