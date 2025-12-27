#include "Functions.h"

// Type 2 - Baseboard
void displayBaseboardInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t Manufacturer;
  uint8_t Product;
  uint8_t Version;
  uint8_t SerialNumber;
  uint8_t AssetTag;
  uint8_t FeatureFlags;
  uint8_t LocationInChassis;
  uint16_t ChassisHandle;
  uint8_t BoardType;
  uint8_t NumberOfContainedObjectHandles;

  std::memcpy(&Manufacturer, bytes + 0x04, sizeof(Manufacturer));
  std::memcpy(&Product, bytes + 0x05, sizeof(Product));
  std::memcpy(&Version, bytes + 0x06, sizeof(Version));
  std::memcpy(&SerialNumber, bytes + 0x07, sizeof(SerialNumber));
  std::memcpy(&AssetTag, bytes + 0x08, sizeof(AssetTag));
  std::memcpy(&FeatureFlags, bytes + 0x09, sizeof(FeatureFlags));
  std::memcpy(&LocationInChassis, bytes + 0x0A, sizeof(LocationInChassis));
  std::memcpy(&ChassisHandle, bytes + 0x0B, sizeof(ChassisHandle));
  std::memcpy(&BoardType, bytes + 0x0D, sizeof(BoardType));
  std::memcpy(&NumberOfContainedObjectHandles, bytes + 0x0E, sizeof(NumberOfContainedObjectHandles));

  std::cout << "\tManufacturer: " << strings[Manufacturer] << std::endl;
  std::cout << "\tProduct: " << strings[Product] << std::endl;
  std::cout << "\tVersion: " << strings[Version] << std::endl;
  std::cout << "\tSerial Number: " << strings[SerialNumber] << std::endl;
  std::cout << "\tAsset Tag: " << strings[AssetTag] << std::endl;

  displayFeatureFlags(FeatureFlags);

  std::cout << "\tLocation in Chassis: " << strings[LocationInChassis] << std::endl;
  std::cout << "\tChassis Handle: " << (int)ChassisHandle << std::endl;
  std::cout << "\tBaseboard Type: " << getBaseBoardType(BoardType) << std::endl;

  if (NumberOfContainedObjectHandles > 0) {
    std::cout << "\tContained Object Handles:" << std::endl;
    for (int i = 0; i < NumberOfContainedObjectHandles; ++i) {
      uint8_t ContainedObjectHandle = bytes[0x0F + i];
      std::cout << "\t\t" << (int)ContainedObjectHandle << std::endl;
    }
  } else {
    std::cout << "\tNo Contained Objects" << std::endl;
  }
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
