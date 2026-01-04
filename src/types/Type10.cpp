#include "Functions.h"

// Type 10 - On Board Devices
void displayOnBoardDevicesInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  int numDevices = (curStruct->Length - 4) / 2;

  uint8_t Device;
  uint8_t Description;

  for (int n = 1; n <= numDevices; ++n) {
    std::memcpy(&Device, bytes + 0x04 + 2 * (n - 1), sizeof(Device));
    std::memcpy(&Description, bytes + 0x05 + 2 * (n - 1), sizeof(Description));

    std::cout << "\tDevice " << n << ":" << std::endl;
    displayDeviceInformation(Device);
    std::cout << "\t\tDescription: " << strings[Description] << std::endl;
  }
}

void displayDeviceInformation(uint8_t Device) {
  std::cout << "\t\tInformation: ";
  
  if (getBit(Device, 7)) std::cout << "Enabled";
  else std::cout << "Disabled";
  
  std::cout << ", ";
  
  Device = (Device << 1) >> 1;

  switch (Device) {
    case 1:
      std::cout << "Other" << std::endl;
      break;
    case 2:
      std::cout << "Unknown" << std::endl;
      break;
    case 3:
      std::cout << "Video" << std::endl;
      break;
    case 4:
      std::cout << "SCSI Controller" << std::endl;
      break;
    case 5:
      std::cout << "Ethernet" << std::endl;
      break;
    case 6:
      std::cout << "Token Ring" << std::endl;
      break;
    case 7:
      std::cout << "Sound" << std::endl;
      break;
    case 8:
      std::cout << "PATA Controller" << std::endl;
      break;
    case 9:
      std::cout << "SATA Controller" << std::endl;
      break;
    case 10:
      std::cout << "SAS Controller" << std::endl;
      break;
    default:
      std::cout << "Other" << std::endl;
      break;
  }
}
