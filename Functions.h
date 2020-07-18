#include "Structures.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

/** Get the Raw SMBIOS table */
RawSMBIOSData* getRawData();

/** Display available user commands */
void displayCommands();

/** Display the entire SMBIOS table of data in hexadecimal by byte */
void displayHexContents(RawSMBIOSData* rawData);

/** Display each structure in a list */
void displayAllStructures(RawSMBIOSData* rawData);

/** Get a list of structures from the raw data */
std::vector<SMBIOSStruct*> getStructureTable(RawSMBIOSData* rawData);

/** Get the next SMBIOS structure after the current one */
SMBIOSStruct* getNextStruct(SMBIOSStruct* curStruct);

/** Get the strings that are associated with the current structure */
std::vector<std::string> getStrings(SMBIOSStruct* curStruct);

/** Display the structure table alone */
void displayStructureTable(RawSMBIOSData* rawData);

/** Display a specific SMBIOS structure from the table */
void displayStructure(RawSMBIOSData* rawData, int id);

/** Get a specific bit from an array of bytes */
int getBit(BYTE bytes[], int bitNum, int numBits);

/** Get a specific bit from a byte */
int getBit(BYTE byte, int bitNum);

/** Get a specific bit from a word */
int getBit(WORD word, int bitNum);

/** Get consecutive bits from a byte */
int getBits(BYTE byte, int startBit, int endBit);

/** Get consecutive bits from a word */
int getBits(WORD word, int startBit, int endBit);

/** Display minimal information about the vendor-specific, non-required structures */
void displayInformation(SMBIOSStructNonRequired* curStruct);



/** Display System BIOS Information (Type 0) */
void displayInformation(SMBIOSStructType0* curStruct, RawSMBIOSData* rawData);

/** Display BIOS Characteristics for the type 0 structure */
void displayBIOSCharacteristics(SMBIOSStructType0* curStruct);

/** Display BIOS Extended characteristics for the type 0 structure */
void displayBIOSExtendedCharacteristics(SMBIOSStructType0* curStruct);



/** Display System Information (Type 1) */
void displayInformation(SMBIOSStructType1* curStruct, RawSMBIOSData* rawData);

/** Get the wakeup type field for the type 1 structure */
std::string getWakeUpType(SMBIOSStructType1* curStruct);



/** Display Baseboard Information (Type 2) */
void displayInformation(SMBIOSStructType2* curStruct, RawSMBIOSData* rawData);

/** Display Feature Flags for the type 2 structure */
void displayFeatureFlags(SMBIOSStructType2* curStruct);

/** Determine the Baseboard type for the type 2 structure */
std::string getBaseBoardType(SMBIOSStructType2* curStruct);

/** Display Chassis Information (Type 3) */
void displayInformation(SMBIOSStructType3* curStruct, RawSMBIOSData* rawData);

/** Display the Chassis Type for the type 3 structure */
void displayChassisType(SMBIOSStructType3* curStruct);

/** Get the chassis state for the type 3 structure */
std::string getChassisState(BYTE field);

/** Get the chassis security state for the type 3 structure */
std::string getChassisSecurityState(BYTE field);



/** Display Processor Information (Type 4) */
void displayInformation(SMBIOSStructType4* curStruct, RawSMBIOSData* rawData);

/** Display the processor's characteristics for the type 4 structure */
void displayProcessorCharacteristics(SMBIOSStructType4* curStruct);

/** Get the processor's type for the type 4 structure */
std::string getProcessorType(SMBIOSStructType4* curStruct);

/** Get the processor's family for the type 4 structure */
std::string getProcessorFamily(SMBIOSStructType4* curStruct);

/** Get the voltage for the type 4 structure */
std::string getVoltage(SMBIOSStructType4* curStruct);

/** Get the status of the processor for the type 4 structure*/
void getProcessorStatus(SMBIOSStructType4* curStruct);

/** Get the processor upgrade information for the type 4 structure */
std::string getProcessorUpgrade(SMBIOSStructType4* curStruct);

/** Get the processor's second family for the type 4 structure */
std::string getProcessorFamily2(SMBIOSStructType4* curStruct);



/** Display Memory Controller Information (Type 5) */
void displayInformation(SMBIOSStructType5* curStruct, RawSMBIOSData* rawData);

/** Get the error detecting method for the type 5 structure */
std::string getErrorDetectingMethod(SMBIOSStructType5* curStruct);

/** Get the error correcting capability for the type 5 structure */ 
void displayErrorCorrectingCapability(SMBIOSStructType5* curStruct);

/** Get the interleave support for the type 5 structure */
std::string getInterleaveSupport(BYTE Interleave);

/** Get the supported speeds for the type 5 structure */
void displaySupportedSpeeds(SMBIOSStructType5* curStruct);

/** Get the supported memory types for the type 5 structure */
void displaySupportedMemoryTypes(SMBIOSStructType5* curStruct);

/** Get the required voltages for the memory module sockets */
void displayMemoryModuleVolate(SMBIOSStructType5* curStruct);



/** Display Memory Module Information (Type 6) */
void displayInformation(SMBIOSStructType6* curStruct, RawSMBIOSData* rawData);

/** Get the current memory type for the type 6 structure */
void displayCurrentMemoryType(SMBIOSStructType6* curStruct);

/** Get the specified size for the type 6 structure */
void displaySize(WORD size);

/** Get the error status for the type 6 structure */
void displayErrorStatus(SMBIOSStructType6* curStruct);



/** Display Cache Information (Type 7) */
void displayInformation(SMBIOSStructType7* curStruct, RawSMBIOSData* rawData);

/** Get the error correction type for the type 7 structure */
std::string getErrorCorrectionTypeField(SMBIOSStructType7* curStruct);

/** Get the system cache type field for the type 7 structure */
std::string getSystemCachetypeField(SMBIOSStructType7* curStruct);

/** Get the associativity of the cache for the type 7 structure */
std::string getAssociativity(SMBIOSStructType7* curStruct);

/** Display the cache configuration information for the type 7 structure */
void displayCacheConfiguration(SMBIOSStructType7* curStruct);

/** Display the cache size for the type 7 structure */
void displayCacheSize(WORD CacheSize);

/** Display the SRAM type for the type 7 structure */
void displaySRAMType(SMBIOSStructType7* curStruct);



/** Display Port Connector Information (Type 8) */
void displayInformation(SMBIOSStructType8* curStruct, RawSMBIOSData* rawData);

/** Display the internal connector type for the type 8 structure */
std::string getConnectorType(BYTE connector);

/** Display the port type for the type 8 structure */
std::string getPortType(SMBIOSStructType8* curStruct);



/** Display System Slots Information (Type 9) */
void displayInformation(SMBIOSStructType9* curStruct, RawSMBIOSData* rawData);

/** Display the slot's first set of characteristics for the type 9 structure */
void displaySlotCharacteristics1(SMBIOSStructType9* curStruct);

/** Display the slot's second set of characteristics for the type 9 structure */
void displaySlotCharacteristics2(SMBIOSStructType9* curStruct);

/** Get the slot type field for the type 9 structure */
std::string getSlotTypeField(SMBIOSStructType9* curStruct);

/** Get the slot's data bus width for the type 9 structure */
std::string getSlotDataBusWidth(SMBIOSStructType9* curStruct);

/** Get the current usage enumeration for the type 9 structure */
std::string getCurrentUsage(SMBIOSStructType9* curStruct);

/** Get the slot's length enumeration for the type 9 structure */
std::string getSlotLength(SMBIOSStructType9* curStruct);



/** Display On Board Devices Information (Type 10) */
void displayInformation(SMBIOSStructType10* curStruct, RawSMBIOSData* rawData);

/** Display the device type for the type 10 structure */
std::string getDeviceType(SMBIOSStructType10* curStruct);



/** Display OEM Strings Information (Type 11) */
void displayInformation(SMBIOSStructType11* curStruct, RawSMBIOSData* rawData);



/** Display System Configuration Options Information (Type 12) */
void displayInformation(SMBIOSStructType12* curStruct, RawSMBIOSData* rawData);



/** Dispay BIOS Language Information (Type 13) */
void displayInformation(SMBIOSStructType13* curStruct, RawSMBIOSData* rawData);



/** Display Group Associations Information (Type 14) */
void displayInformation(SMBIOSStructType14* curStruct, RawSMBIOSData* rawData);



/** Display System Event Log Information (Type 15) */
void displayInformation(SMBIOSStructType15* curStruct, RawSMBIOSData* rawData);

/** Get the access method for the type 15 structure */
std::string getAccessMethod(BYTE accessMethod);



/** Display Physical Memory Array Information (Type 16) */
void displayInformation(SMBIOSStructType16* curStruct, RawSMBIOSData* rawData);

/** Get the location enumeration for the type 16 structure */
std::string getLocation(SMBIOSStructType16* curStruct);

/** Get the use enumeration for the type 16 structure */
std::string getUse(SMBIOSStructType16* curStruct);

/** Get the error correction type enumeration for the type 16 structure */
std::string getErrorCorrectionType(SMBIOSStructType16* curStruct);



/** Display Memory Device Information (Type 17) */
void displayInformation(SMBIOSStructType17* curStruct, RawSMBIOSData* rawData);

/** Get the form factor enumeration for the type 17 structure */
std::string getFormFactor(SMBIOSStructType17* curStruct);

/** Get the memory device type enumeration for the type 17 structure */
std::string getMemoryDeviceType(SMBIOSStructType17* curStruct);

/** Display details about the memory device type */
void displayTypeDetail(SMBIOSStructType17* curStruct);



/** Display Memory Array Mapped Address (Type 19) */
void displayInformation(SMBIOSStructType19* curStruct, RawSMBIOSData* rawData);



/** Display System Boot Information (Type 32) */
void displayInformation(SMBIOSStructType32* curStruct, RawSMBIOSData* rawData);

/** Get the boot status enumeration for the type structure */
std::string getBootStatus(SMBIOSStructType32* curStruct);