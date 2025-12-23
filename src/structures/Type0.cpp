#include "Functions.h"

void SMBIOSParser::displayType0Structure(const SMBIOSStruct* curStruct) {
  std::vector<std::string> strings = getStrings(curStruct);
  std::cout << "SMBIOS Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;
  
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t vendor = bytes[0x04];
  std::cout << "\tVendor: " << strings[vendor] << std::endl;
/*
  std::cout << "\tBIOS Version: " << strings[curStruct->BIOSVersion] << std::endl;
  std::cout << "\tBIOS release Date: " << strings[curStruct->BIOSReleaseDate] << std::endl;

  std::cout << "\tBIOS Rom Size: " << 64 + 64 * (int)curStruct->BIOSROMSize << "K" << std::endl;
*/
}
