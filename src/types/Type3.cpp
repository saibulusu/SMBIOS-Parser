#include "Functions.h"

// Type 3 - Chassis
void SMBIOSParser::displayChassisInformation(const SMBIOSStruct* curStruct) {
  std::cout << "Chassis Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;
  
  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t Manufacturer = bytes[0x04];
  uint8_t Type = bytes[0x05];
  uint8_t Version = bytes[0x06];
  uint8_t SerialNumber = bytes[0x07];
  uint8_t AssetTagNumber = bytes[0x08];

  std::cout << "\tManufacturer: " << strings[Manufacturer] << std::endl;
  displayChassisType(Type);
  std::cout << "\tVersion: " << strings[Version] << std::endl;
  std::cout << "\tSerial Number: " << strings[SerialNumber] << std::endl;
  std::cout << "\tAsset Tag Number: " << strings[AssetTagNumber] << std::endl;

  if (curStruct->Length < 0x0D) return;

  uint8_t BootUpState = bytes[0x09];
  uint8_t PowerSupplyState = bytes[0x0A];
  uint8_t ThermalState = bytes[0x0B];
  uint8_t SecurityStatus = bytes[0x0C];

  std::cout << "\tBoot-up State: " << getChassisState(BootUpState) << std::endl;
  std::cout << "\tPower Supply State: " << getChassisState(PowerSupplyState) << std::endl;
  std::cout << "\tThermal State: " << getChassisState(ThermalState) << std::endl;
  std::cout << "\tSecurity State: " << getChassisSecurityState(SecurityStatus) << std::endl;

  if (curStruct->Length < 0x15) return;
}

void displayChassisType(uint8_t ChassisType) {
  if (getBit(ChassisType, 1)) {
    std::cout << "\tChassis is locked" << std::endl;
    ChassisType %= 128;
  }

  std::cout << "\tChassis Type: ";
  switch (ChassisType) {
  case 1:
    std::cout << "Other";
    break;
  case 2:
    std::cout << "Unknown";
    break;
  case 3:
    std::cout << "Desktop";
    break;
  case 4:
    std::cout << "Low Profile Desktop";
    break;
  case 5:
    std::cout << "Pizza Box";
    break;
  case 6:
    std::cout << "Mini Tower";
    break;
  case 7:
    std::cout << "Tower";
    break;
  case 8:
    std::cout << "Portable";
    break;
  case 9:
    std::cout << "Laptop";
    break;
  case 10:
    std::cout << "Notebook";
    break;
  case 11:
    std::cout << "Hand Held";
    break;
  case 12:
    std::cout << "Docking Station";
    break;
  case 13:
    std::cout << "All in One";
    break;
  case 14:
    std::cout << "Sub Notebook";
    break;
  case 15:
    std::cout << "Space-saving";
    break;
  case 16:
    std::cout << "Lunch Box";
    break;
  case 17:
    std::cout << "Main Server Chassis";
    break;
  case 18:
    std::cout << "Expansion Chassis";
    break;
  case 19:
    std::cout << "SubChassis";
    break;
  case 20:
    std::cout << "Bus Expansion Chassis";
    break;
  case 21:
    std::cout << "Peripheral chassis";
    break;
  case 22:
    std::cout << "RAID Chassis";
    break;
  case 23:
    std::cout << "Rack Mount Chassis";
    break;
  case 24:
    std::cout << "Sealed-case PC";
    break;
  case 25:
    std::cout << "Multi-system Chassis";
    break;
  case 26:
    std::cout << "Compact PCI";
    break;
  case 27:
    std::cout << "Advanced TCA";
    break;
  case 28:
    std::cout << "Blade";
    break;
  case 29:
    std::cout << "Blade Enclosure";
    break;
  case 30:
    std::cout << "Tablet";
    break;
  case 31:
    std::cout << "Convertible";
    break;
  case 32:
    std::cout << "Detachable";
    break;
  default:
    std::cout << "Other";
    break;
  }
  std::cout << std::endl;
}

std::string getChassisState(uint8_t field) {
  switch (field) {
  case 1:
    return "Other";
  case 2:
    return "Unkown";
  case 3:
    return "Safe";
  case 4:
    return "Warning";
  case 5:
    return "Critical";
  case 6:
    return "Non-recoverable";
  default:
    return "Other";
  }
}

std::string getChassisSecurityState(uint8_t field) {
  switch (field) {
  case 1:
    return "Other";
  case 2:
    return "Unknown";
  case 3:
    return "None";
  case 4:
    return "External interface locked out";
  case 5:
    return "External interface enabled";
  default:
    return "Other";
  }
}
