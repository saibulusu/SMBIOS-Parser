#include "SMBIOSData.h"
#include "SMBIOSPlatform.h"
#include "SMBIOSParser.h"
#include <cstring>
#include <iomanip>
#include <string>

// constructing structs
std::vector<std::string> getStrings(const SMBIOSStruct* curStruct);
const SMBIOSStruct* getNextStruct(const SMBIOSStruct* curStruct);

// helper methods
int getBit(uint8_t bytes[], int bitNum, int numBytes);
int getBit(uint8_t byte, int bitNum);
int getBit(uint16_t word, int bitNum); 
int getBits(uint8_t byte, int startBit, int endBit);
int getBits(uint16_t word, int startBit, int endBit);

// type 0
void displayBIOSCharacteristics(uint8_t* BIOSCharacteristics);
void displayBIOSExtendedCharacteristics(uint8_t* BIOSCharacteristicsExtensions);

// type 1
std::string getWakeUpType(uint8_t WakeUpType);

// type 2
void displayFeatureFlags(uint8_t FeatureFlags);
std::string getBaseBoardType(uint8_t BoardType);

// type 3
void displayChassisType(uint8_t ChassisType);
std::string getChassisState(uint8_t field);
std::string getChassisSecurityState(uint8_t field);
