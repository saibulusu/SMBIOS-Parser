#include "Functions.h"

// Type 5 - Memory Controller
void displayMemoryControllerInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t ErrorDetectingMethod;
  uint8_t ErrorCorrectingCompatibility;
  uint8_t SupportedInterleave;
  uint8_t CurrentInterleave;
  uint8_t MaximumMemoryModuleSize;
  uint16_t SupportedSpeeds;
  uint16_t SupportedMemoryTypes;
  uint8_t MemoryModuleVoltage;
  uint8_t NumberOfAssociatedMemorySlots;

  std::memcpy(&ErrorDetectingMethod, bytes + 0x04, sizeof(ErrorDetectingMethod));
  std::memcpy(&ErrorCorrectingCompatibility, bytes + 0x05, sizeof(ErrorCorrectingCompatibility));
  std::memcpy(&SupportedInterleave, bytes + 0x06, sizeof(SupportedInterleave));
  std::memcpy(&CurrentInterleave, bytes + 0x07, sizeof(CurrentInterleave));
  std::memcpy(&MaximumMemoryModuleSize, bytes + 0x08, sizeof(MaximumMemoryModuleSize));
  std::memcpy(&SupportedSpeeds, bytes + 0x09, sizeof(SupportedSpeeds));
  std::memcpy(&SupportedMemoryTypes, bytes + 0x0B, sizeof(SupportedMemoryTypes));
  std::memcpy(&MemoryModuleVoltage, bytes + 0x0D, sizeof(MemoryModuleVoltage));
  std::memcpy(&NumberOfAssociatedMemorySlots, bytes + 0x0E, sizeof(NumberOfAssociatedMemorySlots));

  std::cout << "\tError Detecting Method: " << getErrorDetectingMethod(ErrorDetectingMethod) << std::endl;

  displayErrorCorrectingCapability(ErrorCorrectingCompatibility);

  std::cout << "\tInterleave Support: " << getInterleaveSupport(SupportedInterleave) << std::endl;
  std::cout << "\tCurrent Interleave: " << getInterleaveSupport(CurrentInterleave) << std::endl;
  std::cout << "\tMaximum Memory Module Size: " << (int)MaximumMemoryModuleSize << std::endl;

  displaySupportedSpeeds(SupportedSpeeds);
  displaySupportedMemoryTypes(SupportedMemoryTypes);
  displayMemoryModuleVolate(MemoryModuleVoltage);

  std::cout << "\tNumber of Associated Memory Slots: " << (int)NumberOfAssociatedMemorySlots << std::endl;
}

std::string getErrorDetectingMethod(uint8_t ErrorDetectingMethod) {
  switch (ErrorDetectingMethod) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "None";
    case 4: return "8-bit Parity";
    case 5: return "32-bit ECC";
    case 6: return "64-bit ECC";
    case 7: return "128-bit ECC";
    case 8: return "CRC";
    default: return "Other";
  }
}

void displayErrorCorrectingCapability(uint8_t ErrorCorrectingCapability) {
  std::cout << "\tError Correcting Capabilities: " << std::endl;
  if (getBit(ErrorCorrectingCapability, 3)) {
    std::cout << "\t\tSingle-bit Error Correcting" << std::endl;
  }
  if (getBit(ErrorCorrectingCapability, 4)) {
    std::cout << "\t\tDouble-bit Error Correcting" << std::endl;
  }
  if (getBit(ErrorCorrectingCapability, 5)) {
    std::cout << "\t\tError Scrubbing" << std::endl;
  }
}

std::string getInterleaveSupport(uint8_t Interleave) {
  switch (Interleave) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "One-Way Interleave";
    case 4: return "Two-Way Interleave";
    case 5: return "Four-Way Interleave";
    case 6: return "Eight-Way Interleave";
    case 7: return "Sixteen-way Interleave";
    default: return "Other";
  }
}

void displaySupportedSpeeds(uint16_t SupportedSpeeds) {
  std::cout << "\tSupported Speeds: " << std::endl;
  if (getBit(SupportedSpeeds, 2)) {
    std::cout << "\t\t70 ns" << std::endl;
  }
  if (getBit(SupportedSpeeds, 3)) {
    std::cout << "\t\t60 ns" << std::endl;
  }
  if (getBit(SupportedSpeeds, 4)) {
    std::cout << "\t\t50 ns" << std::endl;
  }
}

void displaySupportedMemoryTypes(uint16_t SupportedMemoryTypes) {
  std::cout << "\tSupported Memory Types: " << std::endl;
  if (getBit(SupportedMemoryTypes, 2)) {
    std::cout << "\t\tStandard" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 3)) {
    std::cout << "\t\tFast Page Mode" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 4)) {
    std::cout << "\t\tEDO" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 5)) {
    std::cout << "\t\tParity" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 6)) {
    std::cout << "\t\tECC" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 7)) {
    std::cout << "\t\tSIMM" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 8)) {
    std::cout << "\t\tDIMM" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 9)) {
    std::cout << "\t\tBurst EDO" << std::endl;
  }
  if (getBit(SupportedMemoryTypes, 10)) {
    std::cout << "\t\tSDRAM" << std::endl;
  }
}

void displayMemoryModuleVolate(uint8_t MemoryModuleVoltage) {
  std::cout << "\tMemory Module Voltage: " << std::endl;
  if (getBit(MemoryModuleVoltage, 2)) {
    std::cout << "2.9V" << std::endl;
  }
  if (getBit(MemoryModuleVoltage, 1)) {
    std::cout << "3.3V" << std::endl;
  }
  if (getBit(MemoryModuleVoltage, 0)) {
    std::cout << "5V" << std::endl;
  }
}
