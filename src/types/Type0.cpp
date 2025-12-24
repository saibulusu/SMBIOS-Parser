#include "Functions.h"
#include <cstring>

// Type 0 - BIOS
void SMBIOSParser::displayBIOSInformation(const SMBIOSStruct* curStruct) {
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
  
  if (curStruct->Length <= 0x0A) return;
  uint64_t BIOSCharacteristics = 0;
  std::memcpy(&BIOSCharacteristics, bytes + 0x0A, sizeof(uint64_t));
  displayBIOSCharacteristics(reinterpret_cast<uint8_t*>(&BIOSCharacteristics));

  if (curStruct->Length <= 0x12) return;
  uint8_t BIOSCharacteristicsExtensions[2];
  std::memcpy(&BIOSCharacteristicsExtensions, bytes + 0x12, sizeof(uint16_t));
  displayBIOSExtendedCharacteristics(BIOSCharacteristicsExtensions);

  if (curStruct->Length < 0x18) return;
  uint8_t ECFirmwareMajorRelease = bytes[0x16];
  uint8_t ECFirmwareMinorRelease = bytes[0x17];

  if (ECFirmwareMajorRelease == 0xFF && ECFirmwareMinorRelease == 0xFF) {
    std::cout << "\tEmbedded Controller Firmware: Not field-upgradable\n";
  } else {
    std::cout << "\tEmbedded Controller Firmware Major Release: " << (int)ECFirmwareMajorRelease << std::endl;
    std::cout << "\tEmbedded Controller Firmware Minor Release: " << (int)ECFirmwareMinorRelease << std::endl;
  }
}

void displayBIOSCharacteristics(uint8_t* BIOSCharacteristics) {
  std::vector<std::string> supported;
  std::vector<std::string> nonsupported;
  std::cout << "\tSupported Features: " << std::endl;
  if (!getBit(BIOSCharacteristics, 3, 8)) {
    std::cout << "\t\tBIOS" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 4, 8)) {
    std::cout << "\t\tISA" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 5, 8)) {
    std::cout << "\t\tMCA" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 6, 8)) {
    std::cout << "\t\tEISA" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 7, 8)) {
    std::cout << "\t\tPCI" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 8, 8)) {
    std::cout << "\t\tPC card (PCMCIA)" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 9, 8)) {
    std::cout << "\t\tPlug and Play" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 10, 8)) {
    std::cout << "\t\tAPM" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 11, 8)) {
    std::cout << "\t\tBIOS is upgradeable (flash)" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 12, 8)) {
    std::cout << "\t\tBIOS shadowing" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 13, 8)) {
    std::cout << "\t\tVL-VESA" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 14, 8)) {
    std::cout << "\t\tESCD support" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 15, 8)) {
    std::cout << "\t\tBoot from CD" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 16, 8)) {
    std::cout << "\t\tSelectable boot" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 17, 8)) {
    std::cout << "\t\tBIOS ROM is socketed" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 18, 8)) {
    std::cout << "\t\tBoot from PC card (PCMCIA)" << std::endl;
  }

  if (getBit(BIOSCharacteristics, 19, 8)) {
    std::cout << "\t\tEDD specification" << std::endl;
  }
}

void displayBIOSExtendedCharacteristics(uint8_t* BIOSCharacteristicsExtensions) {
  if (getBit(BIOSCharacteristicsExtensions[0], 0)) {
    std::cout << "\t\tACPI" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[0], 1)) {
    std::cout << "\t\tUSB Legacy" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[0], 2)) {
    std::cout << "\t\tAGP" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[0], 3)) {
    std::cout << "\t\tI2O Boot" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[0], 4)) {
    std::cout << "\t\tLS-120 SuperDisk boot" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[0], 5)) {
    std::cout << "\t\tATAPI ZIP drive boot" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[0], 6)) {
    std::cout << "\t\t1394 boot" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[0], 7)) {
    std::cout << "\t\tSmart battery" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[1], 0)) {
    std::cout << "\t\tBIOS Boot specification" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[1], 1)) {
    std::cout << "\t\tFunction key-initiated network service" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[1], 2)) {
    std::cout << "\t\tEnabled targeted content distribution" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[1], 3)) {
    std::cout << "\t\tUEFI Specification" << std::endl;
  }

  if (getBit(BIOSCharacteristicsExtensions[1], 4)) {
    std::cout << "\t\tSMBIOS Table describes a virtual machine" << std::endl;
  }
}
