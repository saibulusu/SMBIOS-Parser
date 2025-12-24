#include "SMBIOSData.h"
#include "SMBIOSPlatform.h"
#include "SMBIOSParser.h"

std::vector<std::string> getStrings(const SMBIOSStruct* curStruct);
const SMBIOSStruct* getNextStruct(const SMBIOSStruct* curStruct);

int getBit(uint8_t bytes[], int bitNum, int numBytes);
int getBit(uint8_t byte, int bitNum);
int getBit(uint16_t word, int bitNum); 
int getBits(uint8_t byte, int startBit, int endBit);
int getBits(uint16_t word, int startBit, int endBit);

void displayBIOSCharacteristics(uint8_t* BIOSCharacteristics);
void displayBIOSExtendedCharacteristics(uint8_t* BIOSCharacteristicsExtensions);
