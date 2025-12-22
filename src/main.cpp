#include "SMBIOSPlatform.h"
#include "SMBIOSData.h"
#include "SMBIOSStructure.h"
#include "SMBIOSParser.h"
#include <string>
#include <iostream>

int main() {
  SMBIOSData* data = loadSMBIOSFromLinux();
  SMBIOSParser parser(*data);
  
  std::cout << "SMBIOS table length: " << data->raw()->Length << std::endl;
  parser.parse();
  auto& structs = parser.structures();
  if (!structs.empty()) {
    std::cout << "First structure type: "
              << (int)structs[0]->type() << std::endl;
  }
  delete data;

  return 0;
}