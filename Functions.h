#include "Structures.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

// Getter functions
RawSMBIOSData* getRawData();
std::vector<SMBIOS_struct*> getStructureTable(RawSMBIOSData* rawData);
SMBIOS_struct* getNextStruct(SMBIOS_struct* curStruct);
std::vector<std::string> getStrings(SMBIOS_struct* curStruct);
int getBit(BYTE bytes[], int bitNum, int numBits);
int getBit(BYTE byte, int bitNum);
int getBit(WORD word, int bitNum);
int getBits(BYTE byte, int startBit, int endBit);
int getBits(WORD word, int startBit, int endBit);
std::string getWakeUpType(SMBIOS_struct_type_1* curStruct);
std::string getChassisState(BYTE field);
std::string getChassisSecurityState(BYTE field);
std::string getProcessorType(SMBIOS_struct_type_4* curStruct);
std::string getProcessorFamily(SMBIOS_struct_type_4* curStruct);
std::string getVoltage(SMBIOS_struct_type_4* curStruct);
std::string getProcessorStatus(SMBIOS_struct_type_4* curStruct);
std::string getProcessorUpgrade(SMBIOS_struct_type_4* curStruct);
std::string getProcessorFamily2(SMBIOS_struct_type_4* curStruct);
std::string getErrorCorrectionTypeField(SMBIOS_struct_type_7* curStruct);
std::string getSystemCachetypeField(SMBIOS_struct_type_7* curStruct);
std::string getAssociativity(SMBIOS_struct_type_7* curStruct);

// Display functions
void displayAllStructures(RawSMBIOSData* rawData);
void displayBIOSCharacteristics(SMBIOS_struct_type_0* curStruct);
void displayBIOSExtendedCharacteristics(SMBIOS_struct_type_0* curStruct);
void displayChassisType(SMBIOS_struct_type_3* curStruct);
void displayProcessorCharacteristics(SMBIOS_struct_type_4* curStruct);
void displayHexContents(RawSMBIOSData* rawData);
void displayCacheConfiguration(SMBIOS_struct_type_7* curStruct);
void displayCacheSize(WORD CacheSize);
void displaySRAMType(SMBIOS_struct_type_7* curStruct);
void displayInformation(SMBIOS_struct_non_required* curStruct);
void displayInformation(SMBIOS_struct_type_0* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_1* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_3* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_4* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_7* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_9* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_16* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_17* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_19* curStruct, RawSMBIOSData* rawData);
void displayInformation(SMBIOS_struct_type_32* curStruct, RawSMBIOSData* rawData);