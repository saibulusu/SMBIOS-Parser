#include "Functions.h"

// Type 1 - System
void displaySystemInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t Manufacturer;
  uint8_t ProductName;
  uint8_t Version;
  uint8_t SerialNumber;

  std::memcpy(&Manufacturer, bytes + 0x04, sizeof(Manufacturer));
  std::memcpy(&ProductName, bytes + 0x05, sizeof(ProductName));
  std::memcpy(&Version, bytes + 0x06, sizeof(Version));
  std::memcpy(&SerialNumber, bytes + 0x07, sizeof(SerialNumber));

  std::cout << "\tManufacturer: " << strings[Manufacturer] << std::endl;
  std::cout << "\tProduct Name: " << strings[ProductName] << std::endl;
  std::cout << "\tVersion: " << strings[Version] << std::endl;
  std::cout << "\tSerial Number: " << strings[SerialNumber] << std::endl;

  if (curStruct->Length < 0x19) return;

  uint8_t UUID[16];
  uint8_t WakeUpType;

  std::memcpy(&UUID, bytes + 0x08, sizeof(UUID));
  std::memcpy(&WakeUpType, bytes + 0x18, sizeof(WakeUpType));

  std::cout << "\tUUID: ";

  for (size_t i = 0; i < 16; ++i) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(UUID[i]);
    if (i == 3 || i == 5 || i == 7 || i == 9) std::cout << "-";
  }
  std::cout << std::dec << std::endl;
  std::cout << "\tWake-up Type: " << getWakeUpType(WakeUpType) << std::endl;

  if (curStruct->Length < 0x1B) return;

  uint8_t SKUNumber;
  uint8_t Family;

  std::memcpy(&SKUNumber, bytes + 0x19, sizeof(SKUNumber));
  std::memcpy(&Family, bytes + 0x1A, sizeof(Family));

  std::cout << "\tSKU Number: " << strings[SKUNumber] << std::endl;
  std::cout << "\tFamily: " << strings[Family] << std::endl;
}

std::string getWakeUpType(uint8_t WakeUpType) {
  switch (WakeUpType) {
    case 0: return "Reserved";
    case 1: return "Other";
    case 2: return "Unkown";
    case 3: return "APM Timer";
    case 4: return "Modem Ring";
    case 5: return "LAN Remote";
    case 6: return "Power Switch";
    case 7: return "PCI PME#";
    case 8: return "AC Power Restored";
    default: return "Other";
  }
}
