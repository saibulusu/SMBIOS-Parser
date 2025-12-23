#include "Functions.h"

void SMBIOSParser::displayType0Structure(const SMBIOSStruct* curStruct) {
  std::vector<std::string> strings = getStrings(curStruct);
  std::cout << "SMBIOS Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;
  
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t Vendor = bytes[0x04];
  std::cout << "\tVendor: " << strings[Vendor] << std::endl;
  
  uint8_t BIOSVersion = bytes[0x05];
  std::cout << "\tBIOS Version: " << strings[BIOSVersion] << std::endl;
  
  uint8_t BIOSReleaseDate = bytes[0x08];
  std::cout << "\tBIOS release Date: " << strings[BIOSReleaseDate] << std::endl;
  
  uint8_t BIOSROMSize = bytes[0x09];
  std::cout << "\tBIOS Rom Size: " << 64 + 64 * (int)BIOSROMSize << "K" << std::endl;
}
