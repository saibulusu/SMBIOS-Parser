#include "SMBIOSData.h"
#include "SMBIOSPlatform.h"
#include "SMBIOSParser.h"

std::vector<std::string> getStrings(const SMBIOSStruct* curStruct);
const SMBIOSStruct* getNextStruct(const SMBIOSStruct* curStruct);
