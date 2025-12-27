#include "Functions.h"

// Type 6 - Memory Module
void displayMemoryModuleInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t SocketDesignation;
  uint8_t BankConnections;
  uint8_t CurrentSpeed;
  uint16_t CurrentMemoryType;
  uint8_t InstalledSize;
  uint8_t EnabledSize;
  uint8_t ErrorStatus;

  std::memcpy(&SocketDesignation, bytes + 0x04, sizeof(SocketDesignation));
  std::memcpy(&BankConnections, bytes + 0x05, sizeof(BankConnections));
  std::memcpy(&CurrentSpeed, bytes + 0x06, sizeof(CurrentSpeed));
  std::memcpy(&CurrentMemoryType, bytes + 0x07, sizeof(CurrentMemoryType));
  std::memcpy(&InstalledSize, bytes + 0x09, sizeof(InstalledSize));
  std::memcpy(&EnabledSize, bytes + 0x0A, sizeof(EnabledSize));
  std::memcpy(&ErrorStatus, bytes + 0x0B, sizeof(ErrorStatus));

  std::cout << "\tSocket Designation: " << strings[SocketDesignation] << std::endl;
  std::cout << "\tBank Connections: " << (int)BankConnections << std::endl;
  std::cout << "\tCurrent Speed: " << (int)CurrentSpeed << " ns" << std::endl;

  displayCurrentMemoryType(CurrentMemoryType);

  std::cout << "\tInstalled Size" << std::endl;
  displaySize(InstalledSize);
  std::cout << "\tEnabled Size" << std::endl;
  displaySize(EnabledSize);

  displayErrorStatus(ErrorStatus);
}

void displayCurrentMemoryType(uint16_t CurrentMemoryType) {
  std::cout << "\tMemory Module Information: " << std::endl;
  if (getBit(CurrentMemoryType, 2)) {
    std::cout << "\t\tStandard" << std::endl;
  }
  if (getBit(CurrentMemoryType, 3)) {
    std::cout << "\t\tFast Page Mode" << std::endl;
  }
  if (getBit(CurrentMemoryType, 4)) {
    std::cout << "\t\tEDO" << std::endl;
  }
  if (getBit(CurrentMemoryType, 5)) {
    std::cout << "\t\tParity" << std::endl;
  }
  if (getBit(CurrentMemoryType, 6)) {
    std::cout << "\t\tECC" << std::endl;
  }
  if (getBit(CurrentMemoryType, 7)) {
    std::cout << "\t\tSIMM" << std::endl;
  }
  if (getBit(CurrentMemoryType, 8)) {
    std::cout << "\t\tDIMM" << std::endl;
  }
  if (getBit(CurrentMemoryType, 9)) {
    std::cout << "\t\tBurst EDO" << std::endl;
  }
  if (getBit(CurrentMemoryType, 10)) {
    std::cout << "\t\tSDRAM" << std::endl;
  }
}

void displaySize(uint16_t size) {
  if (getBit(size, 7)) std::cout << "\t\tDouble-Bank Connection" << std::endl;
  else std::cout << "\t\tSingle-Bank Connection" << std::endl;

  int computed = pow(2, size);
  std::cout << "\t\t" << computed << "MB" << std::endl;
}

void displayErrorStatus(uint8_t ErrorStatus) {
  std::cout << "\tError Status:" << std::endl;
  if (getBit(ErrorStatus, 1)) {
    std::cout << "\t\tCorrectable Errors Recieved" << std::endl;
  }
  if (getBit(ErrorStatus, 0)) {
    std::cout << "\t\tUncorrectabled Errors Recieved" << std::endl;
  }
}
