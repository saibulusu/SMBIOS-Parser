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

// type -> name (BIOS, Processor, etc.)
std::string getTypeName(uint8_t type);

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

// type 4
std::string getProcessorType(uint8_t ProcessorType);
std::string getProcessorFamily(uint8_t ProcessorFamily);
std::string getVoltage(uint8_t Voltage);
void getProcessorStatus(uint8_t Status);
std::string getProcessorUpgrade(uint8_t ProcessorUpgrade);
void displayProcessorCharacteristics(uint16_t ProcessorCharacteristics);
std::string getProcessorFamily2(uint16_t ProcessorFamily2);

// type 5
std::string getErrorDetectingMethod(uint8_t ErrorDetectingMethod);
void displayErrorCorrectingCapability(uint8_t ErrorCorrectingCapability);
std::string getInterleaveSupport(uint8_t Interleave);
void displaySupportedSpeeds(uint16_t SupportedSpeeds);
void displaySupportedMemoryTypes(uint16_t SupportedMemoryTypes);
void displayMemoryModuleVolate(uint8_t MemoryModuleVoltage);

// type 6
void displayCurrentMemoryType(uint16_t CurrentMemoryType);
void displaySize(uint16_t size);
void displayErrorStatus(uint8_t ErrorStatus);

// type 7
std::string getErrorCorrectionTypeField(uint8_t ErrorCorrectionType);
std::string getSystemCacheTypeField(uint8_t SystemCacheType);
std::string getAssociativity(uint8_t Associativity);
void displayCacheConfiguration(uint16_t CacheConfiguration);
void displayCacheSize(uint16_t CacheSize);
void displaySRAMType(uint16_t CurrentSRAMType);
