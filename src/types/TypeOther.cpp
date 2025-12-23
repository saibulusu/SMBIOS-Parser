#include "Functions.h"

void SMBIOSParser::displayTypeOtherStructure(const SMBIOSStruct* curStruct) {
  std::cout << "Vendor-Specific SMBIOS structure (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tCannot display more information" << std::endl;
}
