#include "SMBIOSData.h"
#include "SMBIOSPlatform.h"
#include "SMBIOSParser.h"
#include <cmath>
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

// type vendor specific
void displayVendorSpecificInformation(const SMBIOSStruct* curStruct);

// type 0
void displayBIOSInformation(const SMBIOSStruct* curStruct);
void displayBIOSCharacteristics(uint8_t* BIOSCharacteristics);
void displayBIOSExtendedCharacteristics(uint8_t* BIOSCharacteristicsExtensions);

// type 1
void displaySystemInformation(const SMBIOSStruct* curStruct);
std::string getWakeUpType(uint8_t WakeUpType);

// type 2
void displayBaseboardInformation(const SMBIOSStruct* curStruct);
void displayFeatureFlags(uint8_t FeatureFlags);
std::string getBaseBoardType(uint8_t BoardType);

// type 3
void displayChassisInformation(const SMBIOSStruct* curStruct);
void displayChassisType(uint8_t ChassisType);
std::string getChassisState(uint8_t field);
std::string getChassisSecurityState(uint8_t field);

// type 4
void displayProcessorInformation(const SMBIOSStruct* curStruct);
std::string getProcessorType(uint8_t ProcessorType);
std::string getProcessorFamily(uint16_t ProcessorFamily);
std::string getVoltage(uint8_t Voltage);
void getProcessorStatus(uint8_t Status);
std::string getProcessorUpgrade(uint8_t ProcessorUpgrade);
void displayProcessorCharacteristics(uint16_t ProcessorCharacteristics);

// type 5
void displayMemoryControllerInformation(const SMBIOSStruct* curStruct);
std::string getErrorDetectingMethod(uint8_t ErrorDetectingMethod);
void displayErrorCorrectingCapability(uint8_t ErrorCorrectingCapability);
std::string getInterleaveSupport(uint8_t Interleave);
void displaySupportedSpeeds(uint16_t SupportedSpeeds);
void displaySupportedMemoryTypes(uint16_t SupportedMemoryTypes);
void displayMemoryModuleVolate(uint8_t MemoryModuleVoltage);

// type 6
void displayMemoryModuleInformation(const SMBIOSStruct* curStruct);
void displayCurrentMemoryType(uint16_t CurrentMemoryType);
void displaySize(uint16_t size);
void displayErrorStatus(uint8_t ErrorStatus);

// type 7
void displayCacheInformation(const SMBIOSStruct* curStruct);
std::string getErrorCorrectionTypeField(uint8_t ErrorCorrectionType);
std::string getSystemCacheTypeField(uint8_t SystemCacheType);
std::string getAssociativity(uint8_t Associativity);
void displayCacheConfiguration(uint16_t CacheConfiguration);
void displayCacheSize(uint16_t CacheSize);
void displaySRAMType(uint16_t CurrentSRAMType);

// type 8
void displayPortConnectorInformation(const SMBIOSStruct* curStruct);
std::string getConnectorType(uint8_t connector);
std::string getPortType(uint8_t PortType);

// type 9
void displaySystemSlotsInformation(const SMBIOSStruct* curStruct);
std::string getSlotTypeField(uint8_t SlotType);
std::string getSlotDataBusWidth(uint8_t SlotDataBusWidth);
std::string getCurrentUsage(uint8_t CurrentUsage);
std::string getSlotLength(uint8_t SlotLength);
void displaySlotCharacteristics1(uint8_t SlotCharacteristics1);
void displaySlotCharacteristics2(uint8_t SlotCharacteristics2);

// type 10
void displayOnBoardDevicesInformation(const SMBIOSStruct* curStruct);
void displayDeviceInformation(uint8_t Device);

// type 11
void displayOEMStringsInformation(const SMBIOSStruct* curStruct);

// type 12
void displaySystemConfigurationOptionsInformation(const SMBIOSStruct* curStruct);
