#include "Functions.h"

// Type 7 - Cache
void displayCacheInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t SocketDesignation;
  uint16_t CacheConfiguration;
  uint16_t MaximumCacheSize;
  uint16_t InstalledSize;
  uint16_t SupportedSRAMType;
  uint16_t CurrentSRAMType;

  std::memcpy(&SocketDesignation, bytes + 0x04, sizeof(SocketDesignation));
  std::memcpy(&CacheConfiguration, bytes + 0x05, sizeof(CacheConfiguration));
  std::memcpy(&MaximumCacheSize, bytes + 0x07, sizeof(MaximumCacheSize));
  std::memcpy(&InstalledSize, bytes + 0x09, sizeof(InstalledSize));
  std::memcpy(&SupportedSRAMType, bytes + 0x0B, sizeof(SupportedSRAMType));
  std::memcpy(&CurrentSRAMType, bytes + 0x0D, sizeof(CurrentSRAMType));

  displayCacheConfiguration(CacheConfiguration);
  std::cout << "\tMaximum ";
  displayCacheSize(MaximumCacheSize);
  std::cout << "\tInstalled ";
  displayCacheSize(InstalledSize);
  displaySRAMType(CurrentSRAMType);

  std::cout << "\tSocket Designation: " << strings[SocketDesignation] << std::endl;

  if (curStruct->Length < 0x13) return;

  uint8_t CacheSpeed;
  uint8_t ErrorCorrectionType;
  uint8_t SystemCacheType;
  uint8_t Associativity;

  std::memcpy(&CacheSpeed, bytes + 0x0F, sizeof(CacheSpeed));
  std::memcpy(&ErrorCorrectionType, bytes + 0x10, sizeof(ErrorCorrectionType));
  std::memcpy(&SystemCacheType, bytes + 0x11, sizeof(SystemCacheType));
  std::memcpy(&Associativity, bytes + 0x12, sizeof(ErrorCorrectionType));

  if (CacheSpeed != 0) std::cout << "\tCache Module Speed: " << (int)CacheSpeed << " ns" << std::endl;
  else std::cout << "\tCache Module Speed unknown" << std::endl;

  std::cout << "\tError Correction Type: " << getErrorCorrectionTypeField(ErrorCorrectionType) << std::endl;
  std::cout << "\tSystem Cache Type: " << getSystemCacheTypeField(SystemCacheType) << std::endl;
  std::cout << "\tAssociativity: " << getAssociativity(Associativity) << std::endl;
}

std::string getErrorCorrectionTypeField(uint8_t ErrorCorrectionType) {
  switch (ErrorCorrectionType) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "None";
    case 4: return "Parity";
    case 5: return "Single-bit ECC";
    case 6: return "Multi-bit ECC";
    default: return "Other";
  }
}

std::string getSystemCacheTypeField(uint8_t SystemCacheType) {
  switch (SystemCacheType) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "Instruction";
    case 4: return "Data";
    case 5: return "Unified";
    default: return "Other";
  }
}

std::string getAssociativity(uint8_t Associativity) {
  switch (Associativity) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "Direct Mapped";
    case 4: return "2-Way Set-Associative";
    case 5: return "4-Way Set-Associative";
    case 6: return "Fully Associative";
    case 7: return "8-Way Set-Associative";
    case 8: return "16-Way Set-Associative";
    case 9: return "12-Way Set-Associative";
    case 10: return "24-Way Set-Associative";
    case 11: return "32-Way Set-Associative";
    case 12: return "48-Way Set-Associative";
    case 13: return "64-Way Set-Associative";
    case 14: return "20-Way Set-Associative";
    default: return "Other";
  }
}

void displayCacheConfiguration(uint16_t CacheConfiguration) {
  int operationalMode = getBits(CacheConfiguration, 9, 8);
  std::cout << "\tCache Configuration:" << std::endl;
  switch (operationalMode) {
    case 0:
      std::cout << "\t\tWrite Through" << std::endl;
      break;
    case 1:
      std::cout << "\t\tWrite Back" << std::endl;
      break;
  }

  int enabledDisabled = getBit(CacheConfiguration, 7);
  switch (enabledDisabled) {
    case 0:
      std::cout << "\t\tDisabled at boot time" << std::endl;
      break;
    case 1:
      std::cout << "\t\tEnabled at boot time" << std::endl;
      break;
  }

  int location = getBits(CacheConfiguration, 6, 5);
  switch (location) {
    case 0:
      std::cout << "\t\tInternal to the CPU Module" << std::endl;
      break;
    case 1:
      std::cout << "\t\tExternal to the CPU Module" << std::endl;
      break;
    default:
      std::cout << "\t\tLocation unknown" << std::endl;
      break;
  }

  int socketed = getBit(CacheConfiguration, 3);
  switch (socketed) {
    case 0:
      std::cout << "\t\tSocketed" << std::endl;
      break;
    case 1:
      std::cout << "\t\tNot Socketed" << std::endl;
      break;
  }

  int level = getBits(CacheConfiguration, 2, 0);
  std::cout << "\t\tLevel: " << level + 1 << std::endl;
}

void displayCacheSize(uint16_t CacheSize) {
  int size = (getBit(CacheSize, 15)) ? 64 : 1;
  size *= getBits(CacheSize, 14, 0);
  std::cout << "Size: " << size << "K" << std::endl;
}

void displaySRAMType(uint16_t CurrentSRAMType) {
  std::cout << "\tSRAM:" << std::endl;
  if (getBit(CurrentSRAMType, 2)) std::cout << "\t\tNon-Burst" << std::endl;
  if (getBit(CurrentSRAMType, 3)) std::cout << "\t\tBurst" << std::endl;
  if (getBit(CurrentSRAMType, 4)) std::cout << "\t\tPipeline Burst" << std::endl;
  if (getBit(CurrentSRAMType, 5)) std::cout << "\t\tSynchronous" << std::endl;
  if (getBit(CurrentSRAMType, 6)) std::cout << "\t\tAsynchronous" << std::endl;
}
