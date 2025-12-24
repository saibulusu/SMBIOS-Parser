#include "Functions.h"

// Type 2 - Baseboard
void SMBIOSParser::displayBaseboardInformation(const SMBIOSStruct* curStruct) {
  std::cout << "Baseboard Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;
  
  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t Manufacturer = bytes[0x04];
  uint8_t Product = bytes[0x05];
  uint8_t Version = bytes[0x06];
  uint8_t SerialNumber = bytes[0x07];
  uint8_t AssetTag = bytes[0x08];
  uint8_t FeatureFlags = bytes[0x09];
  uint8_t LocationInChassis = bytes[0x0A];
  uint16_t ChassisHandle;
  uint8_t BoardType = bytes[0x0D];

  std::memcpy(&ChassisHandle, bytes + 0x0B, sizeof(uint16_t));

  std::cout << "\tManufacturer: " << strings[Manufacturer] << std::endl;
  std::cout << "\tProduct: " << strings[Product] << std::endl;
  std::cout << "\tVersion: " << strings[Version] << std::endl;
  std::cout << "\tSerial Number: " << strings[SerialNumber] << std::endl;
  std::cout << "\tAsset Tag: " << strings[AssetTag] << std::endl;

  displayFeatureFlags(FeatureFlags);

  std::cout << "\tLocation in Chassis: " << strings[LocationInChassis] << std::endl;
  std::cout << "\tChassis Handle: " << (int)ChassisHandle << std::endl;
  std::cout << "\tBaseboard Type: " << getBaseBoardType(BoardType) << std::endl;
}

void displayFeatureFlags(uint8_t FeatureFlags) {
  std::cout << "\tFeatures: " << std::endl;
  if (getBit(FeatureFlags, 4)) {
    std::cout << "\t\tThe board is hot swappable" << std::endl;
  }
  if (getBit(FeatureFlags, 3)) {
    std::cout << "\t\tThe board is replaceable" << std::endl;
  }
  if (getBit(FeatureFlags, 2)) {
    std::cout << "\t\tThe board is removable" << std::endl;
  }
  if (getBit(FeatureFlags, 1)) {
    std::cout << "\t\tThe board requires at least one daughter board" << std::endl;
  }
  if (getBit(FeatureFlags, 0)) {
    std::cout << "\t\tThe board is a hosting board" << std::endl;
  }
}

std::string getBaseBoardType(uint8_t BoardType) {
  switch (BoardType) {
  case 1:
    return "Unknown";
  case 2:
    return "Other";
  case 3:
    return "Server Blade";
  case 4:
    return "Connectivity Switch";
  case 5:
    return "System Management Module";
  case 6:
    return "Processor Module";
  case 7:
    return "I/O Module";
  case 8:
    return "Memory Module";
  case 9:
    return "Daughter Board";
  case 10:
    return "Motherboard";
  case 11:
    return "Processor/Memory Module";
  case 12:
    return "Processor/IO Module";
  case 13:
    return "Interconnect Board";
  default:
    return "Other";
  }
}
