#include "Functions.h"

// Type 12 - System Configuation Options 
void displaySystemConfigurationOptionsInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t Count;

  std::memcpy(&Count, bytes + 0x04, sizeof(Count));

  std::cout << "\tCount: " << (int)Count << std::endl;

  std::cout << "\tStrings:" << std::endl;

  for (int i = 1; i <= Count; ++i) {
    std::cout << "\t\t" << strings[i] << std::endl;
  }
}
