#include "Functions.h"
#include <iostream>

RawSMBIOSData* getRawData() {
    DWORD error = ERROR_SUCCESS;
    DWORD smBiosDataSize = 0;
    RawSMBIOSData* smBiosData = NULL;
    DWORD bytesWritten = 0;

    // Make sure that there is enough space in the heap for this table
    smBiosDataSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
    smBiosData = (RawSMBIOSData*)HeapAlloc(GetProcessHeap(), 0, smBiosDataSize);
    if (!smBiosData) {
        error = ERROR_OUTOFMEMORY;
        exit(1);
    }

    // Make sure that the data used is valid (by checking the amount of data received)
    bytesWritten = GetSystemFirmwareTable('RSMB', 0, smBiosData, smBiosDataSize);
    if (bytesWritten != smBiosDataSize) {
        error = ERROR_INVALID_DATA;
        exit(1);
    }

    return smBiosData;
}

void displayHexContents(RawSMBIOSData* rawData) {
    for (int i = 0; i < rawData->Length; ++i) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)rawData->SMBIOSTableData[i] << " ";
        if (i % 32 == 31) {
            std::cout << std::endl;
        }
    }
    std::cout << std::dec << std::endl;
}

std::vector<SMBIOSStruct*> getStructureTable(RawSMBIOSData* rawData) {
    std::vector<SMBIOSStruct*> structure_table;
    SMBIOSStruct* curStruct = (SMBIOSStruct*)rawData->SMBIOSTableData;
    while ((char*)curStruct < (char*)rawData + rawData->Length) {
        structure_table.push_back(curStruct);
        curStruct = getNextStruct(curStruct);
    }
    return structure_table;
}

void displayAllStructures(RawSMBIOSData* rawData) {
    std::vector<SMBIOSStruct*> structureTable = getStructureTable(rawData);
    for (int i = 0; i < structureTable.size(); ++i) {
        displayStructure(rawData, i);
    }
}

void displayStructureTable(RawSMBIOSData* rawData) {
    std::vector<SMBIOSStruct*> structureTable = getStructureTable(rawData);
    std::cout << "ID\t" << "Type\t" << "Description" << std::endl;
    for (int i = 0; i < structureTable.size(); ++i) {
        std::cout << i << "\t" << (int)structureTable[i]->Type << "\t";
        switch (structureTable[i]->Type) {
        case 0:
            std::cout << "BIOS" << std::endl;
            break;
        case 1:
            std::cout << "System" << std::endl;
            break;
        case 2:
            std::cout << "Baseboard" << std::endl;
            break;
        case 3:
            std::cout << "System Enclosure/Chassis" << std::endl;
            break;
        case 4:
            std::cout << "Processor" << std::endl;
            break;
        case 5:
            std::cout << "Memory Controller" << std::endl;
            break;
        case 6:
            std::cout << "Memory Module" << std::endl;
            break;
        case 7:
            std::cout << "Cache" << std::endl;
            break;
        case 8:
            std::cout << "Port Connector" << std::endl;
            break;
        case 9:
            std::cout << "System Slots" << std::endl;
            break;
        case 10:
            std::cout << "On Board Devices" << std::endl;
            break;
        case 11:
            std::cout << "OEM Strings" << std::endl;
            break;
        case 12:
            std::cout << "System Configuration Options" << std::endl;
            break;
        case 13:
            std::cout << "BIOS Language" << std::endl;
            break;
        case 14:
            std::cout << "Group Associations" << std::endl;
            break;
        case 15:
            std::cout << "System Event Log" << std::endl;
            break;
        case 16:
            std::cout << "Physical Memory Array" << std::endl;
            break;
        case 17:
            std::cout << "Memory Device" << std::endl;
            break;
        case 19:
            std::cout << "Memory Array Mapped Address" << std::endl;
            break;
        case 32:
            std::cout << "System Boot" << std::endl;
            break;
        default:
            std::cout << "Vendor-Specific Structure" << std::endl;
            break;
        }
    }
}

void displayStructure(RawSMBIOSData* rawData, int id) {
    std::vector<SMBIOSStruct*> structureTable = getStructureTable(rawData);
    switch (structureTable[id]->Type) {
    case 0:
        displayInformation((SMBIOSStructType0*)structureTable[id], rawData);
        break;
    case 1:
        displayInformation((SMBIOSStructType1*)structureTable[id], rawData);
        break;
    case 2:
        displayInformation((SMBIOSStructType2*)structureTable[id], rawData);
        break;
    case 3:
        displayInformation((SMBIOSStructType3*)structureTable[id], rawData);
        break;
    case 4:
        displayInformation((SMBIOSStructType4*)structureTable[id], rawData);
        break;
    case 5:
        displayInformation((SMBIOSStructType5*)structureTable[id], rawData);
        break;
    case 6:
        displayInformation((SMBIOSStructType6*)structureTable[id], rawData);
        break;
    case 7:
        displayInformation((SMBIOSStructType7*)structureTable[id], rawData);
        break;
    case 8:
        displayInformation((SMBIOSStructType8*)structureTable[id], rawData);
        break;
    case 9:
        displayInformation((SMBIOSStructType9*)structureTable[id], rawData);
        break;
    case 10:
        displayInformation((SMBIOSStructType10*)structureTable[id], rawData);
        break;
    case 11:
        displayInformation((SMBIOSStructType11*)structureTable[id], rawData);
        break;
    case 12:
        displayInformation((SMBIOSStructType12*)structureTable[id], rawData);
        break;
    case 13:
        displayInformation((SMBIOSStructType13*)structureTable[id], rawData);
        break;
    case 14:
        displayInformation((SMBIOSStructType14*)structureTable[id], rawData);
        break;
    case 15:
        displayInformation((SMBIOSStructType15*)structureTable[id], rawData);
        break;
    case 16:
        displayInformation((SMBIOSStructType16*)structureTable[id], rawData);
        break;
    case 17:
        displayInformation((SMBIOSStructType17*)structureTable[id], rawData);
        break;
    case 19:
        displayInformation((SMBIOSStructType19*)structureTable[id], rawData);
        break;
    case 32:
        displayInformation((SMBIOSStructType19*)structureTable[id], rawData);
        break;
    default:
        displayInformation((SMBIOSStructNonRequired*)structureTable[id]);
        break;
    }
}

SMBIOSStruct* getNextStruct(SMBIOSStruct* curStruct) {
    char* strings_begin = (char*)curStruct + curStruct->Length;
    char* next_strings = strings_begin + 1;
    while (*strings_begin != NULL || *next_strings != NULL) {
        ++strings_begin;
        ++next_strings;
    }
    return (SMBIOSStruct*)(next_strings + 1);
}

std::vector<std::string> getStrings(SMBIOSStruct* curStruct) {
    std::vector<std::string> strings;
    std::string res = "";
    strings.push_back(res);
    char* cur_char = (char*)curStruct + curStruct->Length;
    SMBIOSStruct* next_struct = getNextStruct(curStruct);

    while (cur_char < (char*)next_struct) {
        res.push_back(*cur_char);
        if (*cur_char == NULL) {
            strings.push_back(res);
            res = "";
        }
        ++cur_char;
    }
    return strings;
}

void displayInformation(SMBIOSStructNonRequired* curStruct) {
    std::cout << "Vendor-Specific SMBIOS structure (Type " << (int)curStruct->Type << ")" << std::endl;
    std::cout << "\tCannot display more information" << std::endl;
    std::cout << std::endl;
}

int getBit(BYTE bytes[], int bitNum, int numBytes) {
    int whichBit = numBytes - 1 - bitNum / 8;
    bitNum %= 8;
    return getBit(bytes[whichBit], bitNum);
}

int getBit(BYTE byte, int bitNum) {
    return (byte >> bitNum) % 2;
}

int getBit(WORD word, int bitNum) {
    return (word >> bitNum) % 2;
}

int getBits(BYTE byte, int startBit, int endBit) {
    return (byte >> endBit) % (1 << (startBit - endBit));
}

int getBits(WORD word, int startBit, int endBit) {
    return (word >> endBit) % (1 << (startBit - endBit));
}

void displayInformation(SMBIOSStructType0* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "SMBIOS Information (Type " << (int)curStruct->Type << ")" << std::endl;
    if ((int)rawData->SMBIOSMajorVersion < 2) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tVendor: " << strings[curStruct->Vendor] << std::endl;
    std::cout << "\tBIOS Version: " << strings[curStruct->BIOSVersion] << std::endl;
    std::cout << "\tBIOS release Date: " << strings[curStruct->BIOSReleaseDate] << std::endl;

    std::cout << "\tBIOS Rom Size: " << 64 + 64 * (int)curStruct->BIOSROMSize << "K" << std::endl;
    displayBIOSCharacteristics(curStruct);
    if ((int)rawData->SMBIOSMajorVersion == 2 && (int)rawData->SMBIOSMinorVersion < 4) {
        std::cout << std::endl;
        return;
    }
    displayBIOSExtendedCharacteristics(curStruct);
    std::cout << "\tEmbedded Controller Firmware Major Release: " << (int)curStruct->ECFirmwareMajorRelease << std::endl;
    std::cout << "\tEmbedded Controller Firmware Minor Release: " << (int)curStruct->ECFirmwareMinorRelease << std::endl;
    std::cout << std::endl;
}

void displayBIOSCharacteristics(SMBIOSStructType0* curStruct) {
    std::vector<std::string> supported;
    std::vector<std::string> nonsupported;
    std::cout << "\tSupported Features: " << std::endl;
    if (!getBit(curStruct->BIOSCharacteristics, 3, 8)) {
        std::cout << "\t\tBIOS" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 4, 8)) {
        std::cout << "\t\tISA" << std::endl;
    }


    if (getBit(curStruct->BIOSCharacteristics, 5, 8)) {
        std::cout << "\t\tMCA" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 6, 8)) {
        std::cout << "\t\tEISA" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 7, 8)) {
        std::cout << "\t\tPCI" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 8, 8)) {
        std::cout << "\t\tPC card (PCMCIA)" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 9, 8)) {
        std::cout << "\t\tPlug and Play" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 10, 8)) {
        std::cout << "\t\tAPM" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 11, 8)) {
        std::cout << "\t\tBIOS is upgradeable (flash)" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 12, 8)) {
        std::cout << "\t\tBIOS shadowing" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 13, 8)) {
        std::cout << "\t\tVL-VESA" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 14, 8)) {
        std::cout << "\t\tESCD support" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 15, 8)) {
        std::cout << "\t\tBoot from CD" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 16, 8)) {
        std::cout << "\t\tSelectable boot" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 17, 8)) {
        std::cout << "\t\tBIOS ROM is socketed" << std::endl;
    }
    
    if (getBit(curStruct->BIOSCharacteristics, 18, 8)) {
        std::cout << "\t\tBoot from PC card (PCMCIA)" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristics, 19, 8)) {
        std::cout << "\t\tEDD specification" << std::endl;
    }
}

void displayBIOSExtendedCharacteristics(SMBIOSStructType0* curStruct) {
    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 0)) {
        std::cout << "\t\tACPI" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 1)) {
        std::cout << "\t\tUSB Legacy" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 2)) {
        std::cout << "\t\tAGP" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 3)) {
        std::cout << "\t\tI2O Boot" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 4)) {
        std::cout << "\t\tLS-120 SuperDisk boot" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 5)) {
        std::cout << "\t\tATAPI ZIP drive boot" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 6)) {
        std::cout << "\t\t1394 boot" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[0], 7)) {
        std::cout << "\t\tSmart battery" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[1], 0)) {
        std::cout << "\t\tBIOS Boot specification" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[1], 1)) {
        std::cout << "\t\tFunction key-initiated network service" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[1], 2)) {
        std::cout << "\t\tEnabled targeted content distribution" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[1], 3)) {
        std::cout << "\t\tUEFI Specification" << std::endl;
    }

    if (getBit(curStruct->BIOSCharacteristicsExtensions[1], 4)) {
        std::cout << "\t\tSMBIOS Table describes a virtual machine" << std::endl;
    }
}

void displayInformation(SMBIOSStructType1* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "System Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if ((int)rawData->SMBIOSMajorVersion < 2) {
        std::cout << std::endl;
        return;
    }
    
    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tManufacturer: " << strings[curStruct->Manufacturer] << std::endl;
    std::cout << "\tProduct Name: " << strings[curStruct->ProductName] << std::endl;
    std::cout << "\tVersion: " << strings[curStruct->Version] << std::endl;
    std::cout << "\tSerial Number: " << strings[curStruct->SerialNumber] << std::endl;

    if ((int)rawData->SMBIOSMajorVersion == 2 && (int)rawData->SMBIOSMinorVersion < 1) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tUUID: " << std::hex << (int)curStruct->UUID << std::dec<< std::endl;
    std::cout << "\tWake-up Type: " << getWakeUpType(curStruct) << std::endl;
    
    if ((int)rawData->SMBIOSMajorVersion == 2 && (int)rawData->SMBIOSMinorVersion < 4) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tSKU Number: " << strings[curStruct->SKUNumber] << std::endl;
    std::cout << "\tFamily: " << strings[curStruct->Family] << std::endl;

    std::cout << std::endl;
}

std::string getWakeUpType(SMBIOSStructType1* curStruct) {
    switch (curStruct->WakeUpType) {
        case 0:
            return "Reserved";
        case 1:
            return "Other";
        case 2:
            return "Unkown";
        case 3:
            return "APM Timer";
        case 4:
            return "Modem Ring";
        case 5:
            return "LAN Remote";
        case 6:
            return "Power Switch";
        case 7:
            return "PCI PME#";
        case 8:
            return "AC Power Restored";
        default:
            return "Other";
    }
}

void displayInformation(SMBIOSStructType2* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Baseboard Information (Type " << (int)curStruct->Type << ")" << std::endl;

    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tManufacturer: " << strings[curStruct->Manufacturer] << std::endl;
    std::cout << "\tProduct: " << strings[curStruct->Product] << std::endl;
    std::cout << "\tVersion: " << strings[curStruct->Version] << std::endl;
    std::cout << "\tSerial Number: " << strings[curStruct->SerialNumber] << std::endl;
    std::cout << "\tAsset Tag: " << strings[curStruct->AssetTag] << std::endl;
    
    displayFeatureFlags(curStruct);
    
    std::cout << "\tLocation in Chassis: " << strings[curStruct->LocationInChassis] << std::endl;
    std::cout << "\tChassis Handle: " << (int)curStruct->ChassisHandle << std::endl;
    std::cout << "\tBaseboard Type: " << getBaseBoardType(curStruct) << std::endl;

    std::cout << std::endl;
}

void displayFeatureFlags(SMBIOSStructType2* curStruct) {
    BYTE flag = curStruct->FeatureFlags;
    
    std::cout << "\tFeatures: " << std::endl;
    if (getBit(flag, 4)) {
        std::cout << "\t\tThe board is hot swappable" << std::endl;
    }
    if (getBit(flag, 3)) {
        std::cout << "\t\tThe board is replaceable" << std::endl;
    }
    if (getBit(flag, 2)) {
        std::cout << "\t\tThe board is removable" << std::endl;
    }
    if (getBit(flag, 1)) {
        std::cout << "\t\tThe board requires at least one daughter board" << std::endl;
    }
    if (getBit(flag, 0)) {
        std::cout << "\t\tThe board is a hosting board" << std::endl;
    }
}

std::string getBaseBoardType(SMBIOSStructType2* curStruct) {
    switch (curStruct->BoardType) {
    case 1:
        return "Unknown";
    case 2:
        return "Other";
    case 3:
        return "Server Blade";
    case 4:
        return "Connectivity Switch";
    case 5:
        return "System Management Module";
    case 6:
        return "Processor Module";
    case 7:
        return "I/O Module";
    case 8:
        return "Memory Module";
    case 9:
        return "Daughter Board";
    case 10:
        return "Motherboard";
    case 11:
        return "Processor/Memory Module";
    case 12:
        return "Processor/IO Module";
    case 13:
        return "Interconnect Board";
    default:
        return "Other";
    }
}

void displayInformation(SMBIOSStructType3* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Chassis Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        std::cout << std::endl;
        return;
    }
    
    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tManufacturer: " << strings[curStruct->Manufacturer] << std::endl;

    displayChassisType(curStruct);
    
    std::cout << "\tVersion: " << strings[curStruct->Version] << std::endl;
    std::cout << "\tSerial Number: " << strings[curStruct->SerialNumber] << std::endl;
    std::cout << "\tAsset Tag Number: " << strings[curStruct->AssetTagNumber] << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tBoot-up State: " << getChassisState(curStruct->BootUpState) << std::endl;
    std::cout << "\tPower Supply State: " << getChassisState(curStruct->PowerSupplyState) << std::endl;
    std::cout << "\tThermal State: " << getChassisState(curStruct->ThermalState) << std::endl;

    std::cout << "\tSecurity State: " << getChassisSecurityState(curStruct->SecurityStatus) << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 3) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tNumber of Power Chords: " << (int)curStruct->NumberOfPowerCords << std::endl;

    std::cout << std::endl;
}

void displayChassisType(SMBIOSStructType3* curStruct) {
    BYTE characteristics = curStruct->ChassisType;
    if (getBit(characteristics, 1)) {
        std::cout << "\tChassis is locked" << std::endl;
        characteristics %= 128;
    }

    std::cout << "\tChassis Type: ";
    switch (characteristics) {
    case 1:
        std::cout << "Other";
        break;
    case 2:
        std::cout << "Unknown";
        break;
    case 3:
        std::cout << "Desktop";
        break;
    case 4:
        std::cout << "Low Profile Desktop";
        break;
    case 5:
        std::cout << "Pizza Box";
        break;
    case 6:
        std::cout << "Mini Tower";
        break;
    case 7:
        std::cout << "Tower";
        break;
    case 8:
        std::cout << "Portable";
        break;
    case 9:
        std::cout << "Laptop";
        break;
    case 10:
        std::cout << "Notebook";
        break;
    case 11:
        std::cout << "Hand Held";
        break;
    case 12:
        std::cout << "Docking Station";
        break;
    case 13:
        std::cout << "All in One";
        break;
    case 14:
        std::cout << "Sub Notebook";
        break;
    case 15:
        std::cout << "Space-saving";
        break;
    case 16:
        std::cout << "Lunch Box";
        break;
    case 17:
        std::cout << "Main Server Chassis";
        break;
    case 18:
        std::cout << "Expansion Chassis";
        break;
    case 19:
        std::cout << "SubChassis";
        break;
    case 20:
        std::cout << "Bus Expansion Chassis";
        break;
    case 21:
        std::cout << "Peripheral chassis";
        break;
    case 22:
        std::cout << "RAID Chassis";
        break;
    case 23:
        std::cout << "Rack Mount Chassis";
        break;
    case 24:
        std::cout << "Sealed-case PC";
        break;
    case 25:
        std::cout << "Multi-system Chassis";
        break;
    case 26:
        std::cout << "Compact PCI";
        break;
    case 27:
        std::cout << "Advanced TCA";
        break;
    case 28:
        std::cout << "Blade";
        break;
    case 29:
        std::cout << "Blade Enclosure";
        break;
    case 30:
        std::cout << "Tablet";
        break;
    case 31:
        std::cout << "Convertible";
        break;
    case 32:
        std::cout << "Detachable";
        break;
    default:
        std::cout << "Other";
        break;
    }
    std::cout << std::endl;
}

std::string getChassisState(BYTE field) {
    switch (field) {
    case 1:
        return "Other";
    case 2:
        return "Unkown";
    case 3:
        return "Safe";
    case 4:
        return "Warning";
    case 5:
        return "Critical";
    case 6:
        return "Non-recoverable";
    default:
        return "Other";
    }
}

std::string getChassisSecurityState(BYTE field) {
    switch (field) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "None";
    case 4:
        return "External interface locked out";
    case 5:
        return "External interface enabled";
    default:
        return "Other";
    }
}

void displayInformation(SMBIOSStructType4* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Processor Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        return;
    }

    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tSocket Designation: " << strings[curStruct->SocketDesignation] << std::endl;
    std::cout << "\tProcessor Type: " << getProcessorType(curStruct) << std::endl;
    std::cout << "\tProcessor Family: " << getProcessorFamily(curStruct) << std::endl;
    std::cout << "\tProcessor Manufacturer: " << strings[curStruct->ProcessorManufacturer] << std::endl;
    std::cout << "\tProcessor ID: " << (int)curStruct->ProcessorID << std::endl;
    std::cout << "\tProcessor Version: " << strings[curStruct->ProcessorVersion] << std::endl;

    std::cout << "\tVoltage: " << getVoltage(curStruct) << std::endl;
    std::cout << "\tExternal Clock: " << (int)curStruct->ExternalClock << "MHz" << std::endl;
    std::cout << "\tMax Processor Speed: " << (int)curStruct->MaxSpeed << "MHz" << std::endl;
    std::cout << "\tCurrent Processor Speed: " << (int)curStruct->CurrentSpeed << "MHz" << std::endl;
    getProcessorStatus(curStruct);
    std::cout << "\tProcessor Upgrade: " << getProcessorUpgrade(curStruct) << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tL1 Cache Handle: " << (int)curStruct->L1CacheHandle << std::endl;
    std::cout << "\tL2 Cache Handle: " << (int)curStruct->L2CacheHandle << std::endl;
    std::cout << "\tL3 Cache Handle: " << (int)curStruct->L3CacheHandle << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 3) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tSerial Number: " << strings[curStruct->SerialNumber] << std::endl;
    std::cout << "\tAsset Tag: " << strings[curStruct->AssetTag] << std::endl;

    std::cout << "\tPart Number: " << strings[curStruct->PartNumber] << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 5) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tCore Count: " << (int)curStruct->CoreCount << std::endl;
    std::cout << "\tCore Enabled: " << (int)curStruct->CoreEnabled << std::endl;
    std::cout << "\tThread Count: " << (int)curStruct->ThreadCount << std::endl;

    displayProcessorCharacteristics(curStruct);
    std::cout << "\tProcessor Family 2: " << getProcessorFamily2(curStruct) << std::endl;
    std::cout << "\tCore Count 2: " << (int)curStruct->CoreCount2 << std::endl;
    std::cout << "\tCore Enabled 2: " << (int)curStruct->CoreEnabled2 << std::endl;
    std::cout << "\tThread Count 2: " << (int)curStruct->ThreadCount2 << std::endl;

    std::cout << std::endl;
}

std::string getProcessorType(SMBIOSStructType4* curStruct) {
    switch (curStruct->ProcessorType) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "Central Processor";
    case 4:
        return "Math Processor";
    case 5:
        return "DSP Proceessor";
    case 6:
        return "Video Processor";
    default:
        return "Other";
    }
}

std::string getProcessorFamily(SMBIOSStructType4* curStruct) {
    switch (curStruct->ProcessorFamily) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "8086";
    case 4:
        return "80286";
    case 5:
        return "Intel386 Processor";
    case 6:
        return "Intel486 Processor";
    case 7:
        return "8087";
    case 8:
        return "80287";
    case 9:
        return "80387";
    case 10:
        return "80487";
    case 11:
        return "Intel Pentium Processor";
    case 12:
        return "Pentium Pro Processsor";
    case 13:
        return "Pentium II Processor";
    case 14:
        return "Pentium Processor with MMX Technology";
    case 15:
        return "Intel Celeron Processor";
    case 16:
        return "Pentium II Xeon Processor";
    case 17:
        return "Pentium III Processor";
    case 18:
        return "M1 Family";
    case 19:
        return "M2 Family";
    case 20:
        return "Intel Celeron M Processor";
    case 21:
        return "Intel Pentium 4 HT Processor";
    case 24:
        return "AMD Duron Processor Family";
    case 25:
        return "K5 Family";
    case 26:
        return "K6 Family";
    case 27:
        return "K6-2";
    case 28:
        return "K6-3";
    case 29:
        return "AMD Athlon Processor Family";
    case 30:
        return "AMD29000 Family";
    case 31:
        return "K6-2+";
    case 32:
        return "Power PC Family";
    case 33:
        return "Power PC 601";
    case 34:
        return "Power PC 603";
    case 35:
        return "Power PC 603+";
    case 36:
        return "Power PC 604";
    default:
        return "Other";
    }
}

std::string getVoltage(SMBIOSStructType4* curStruct) {
    BYTE volts;
    volts = curStruct->Voltage;

    bool five = getBit(volts, 0);
    bool three = getBit(volts, 1);
    bool two = getBit(volts, 2);

    if (five && !three && !two) {
        return "5V";
    }
    else if (three && !five && !two) {
        return "3.3V";
    }
    else if (two && !five && !three) {
        return "2.9V";
    }
    return "Configurable";
}

void getProcessorStatus(SMBIOSStructType4* curStruct) {
    BYTE stats;
    stats = curStruct->Status;
    
    std::cout << "\tProcessor Status: " << std::endl;

    if (getBit(stats, 6) == 1) {
        std::cout << "\t\tCPU Socket Population" << std::endl;
    }
    else {
        std::cout << "\t\tCPU Socket Unpopulated" << std::endl;
    }

    int lowerBits = curStruct->Status % 8;
    switch (lowerBits) {
    case 0:
        std::cout << "\t\tUnknown" << std::endl;
        break;
    case 1:
        std::cout << "\t\tCPU Enabled" << std::endl;
        break;
    case 2:
        std::cout << "\t\tCPU Disabled by User Through BIOS Setup" << std::endl;
        break;
    case 3:
        std::cout << "\t\tCPU Disabled by BIOS (POST Error)" << std::endl;
        break;
    case 4:
        std::cout << "\t\tCPU is Idle, Waiting to be Enabled" << std::endl;
        break;
    default:
        break;
    }
}

std::string getProcessorUpgrade(SMBIOSStructType4* curStruct) {
    switch (curStruct->ProcessorUpgrade) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "Daughter Board";
    case 4:
        return "ZIF Socket";
    case 5:
        return "Replaceable Piggy Back";
    case 6:
        return "None";
    case 7:
        return "LIF Socket";
    case 8:
        return "Slot 1";
    case 9:
        return "Slot 2";
    case 10:
        return "370-Pin Socket";
    case 11:
        return "Slot A";
    case 12:
        return "Slot M";
    case 13:
        return "Socket 423";
    case 14:
        return "Socket A (Socket 462)";
    case 15:
        return "478";
    case 16:
        return "754";
    case 17:
        return "940";
    case 18:
        return "939";
    case 19:
        return "Socket mPGA604";
    case 20:
        return "LGA771";
    case 21:
        return "LGA775";
    case 22:
        return "Socket S1";
    case 23:
        return "Socket AM2";
    case 24:
        return "Socket F (1207)";
    case 25:
        return "Socket LGA 1366";
    case 26:
        return "Socket G34";
    case 27:
        return "Socket AM3";
    case 28:
        return "Socket C32";
    case 29:
        return "Socket LGA1156";
    case 30:
        return "Socket LGA1567";
    case 31:
        return "Socket PGA988A";
    case 32:
        return "Sockt BGA1288";
    case 33:
        return "Socket rPGA988B";
    case 34:
        return "Socket BGA 1023";
    case 35:
        return "Socket BGA 1224";
    case 36:
        return "Socket LGA1155";
    case 37:
        return "Socket LGA1356";
    case 38:
        return "Socket LGA2011";
    case 39:
        return "Socket FS1";
    case 40:
        return "Socket FS2";
    case 41:
        return "Socket FM1";
    case 42:
        return "Socket FM2";
    case 43:
        return "Socket LGA2011-3";
    case 44:
        return "Socket LGA1356-3";
    case 45:
        return "Socket LGA1150";
    case 46:
        return "Socket BGA1168";
    case 47:
        return "Socket BGA1234";
    case 48:
        return "Socket BGA1364";
    default:
        return "Other";
    }
}

void displayProcessorCharacteristics(SMBIOSStructType4* curStruct) {
    BYTE characteristics = curStruct->ProcessorCharacteristics;
    std::cout << "\tCapabilities: " << std::endl;
    if (getBit(characteristics, 2)) {
        std::cout << "\t\t64-bit Capable" << std::endl;
    }
    if (getBit(characteristics, 3)) {
        std::cout << "\t\tMulti-Core" << std::endl;
    }
    if (getBit(characteristics, 4)) {
        std::cout << "\t\tHardware Thread" << std::endl;
    }
    if (getBit(characteristics, 5)) {
        std::cout << "\t\tExecute Protection" << std::endl;
    }
    if (getBit(characteristics, 6)) {
        std::cout << "\t\tEnhanced Virtualization" << std::endl;
    }
    if (getBit(characteristics, 7)) {
        std::cout << "\t\tPower/Performance Control" << std::endl;
    }
}

std::string getProcessorFamily2(SMBIOSStructType4* curStruct) {
    switch (curStruct->ProcessorFamily2) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "8086";
    case 4:
        return "80286";
    case 5:
        return "Intel386 Processor";
    case 6:
        return "Intel486 Processor";
    case 7:
        return "8087";
    case 8:
        return "80287";
    case 9:
        return "80387";
    case 10:
        return "80487";
    case 11:
        return "Intel Pentium Processor";
    case 12:
        return "Pentium Pro Processor";
    case 13:
        return "Pentium II Processor";
    case 14:
        return "Pentium Processor with MMX Technology";
    case 15:
        return "Intel Celeron Processor";
    case 16:
        return "Pentium II Xeon Processor";
    case 17:
        return "Pentium III Processor";
    case 18:
        return "M1 Family";
    case 19:
        return "M2 Family";
    case 20:
        return "Intel Celeron M Processor";
    case 21:
        return "Intel Pentium 4 HT Processor";
    case 24:
        return "AMD Curon Processor Family";
    case 25:
        return "K5 Family";
    case 26:
        return "K6 Family";
    case 27:
        return "K6-2";
    case 28:
        return "K6-3";
    case 29:
        return "AMD Athlon Processor Family";
    case 30:
        return "AMD29000 Family";
    case 31:
        return "K6-2+";
    case 32:
        return "Power PC Family";
    case 33:
        return "Power PC 601";
    case 34:
        return "Poewr PC 603";
    case 35:
        return "Power PC 603+";
    case 36:
        return "Power PC 604";
    case 37:
        return "Power PC 620";
    case 38:
        return "Power PC x704";
    case 39:
        return "Power PC 750";
    case 40:
        return "Intel Core Duo Processor";
    case 41:
        return "Intel Core Duo Mobile Processor";
    case 42:
        return "Intel Core Solo Mobile Processor";
    case 43:
        return "Intel Atom Processor";
    case 44:
        return "Intel Core M Processor";
    case 48:
        return "Alpha Family";
    case 49:
        return "Alpha 21064";
    case 50:
        return "Alpha 21066";
    case 51:
        return "Alpha 21164";
    case 52:
        return "Alpha 21164PC";
    case 53:
        return "Alpha 21164a";
    case 54:
        return "Alpha 21264";
    case 55:
        return "Alhpa 21364";
    case 56:
        return "AMD Turion II Ultra Dual-Core Mobile M Processor Family";
    case 57:
        return "AMD Turio II Dual-Core Mobile M Processor Family";
    case 58:
        return "AMD Athlon II Dual-Core M Processor Family";
    case 59:
        return "AMD Opteron 6100 Series Processor";
    case 60:
        return "AMD Opteron 4100 Series Processor";
    case 61:
        return "AMD Opteron 6200 Series Processor";
    case 62:
        return "AMD Opteron 4200 Series Processor";
    case 63:
        return "AMD FX Series Processor";
    case 64:
        return "MIPS Family";
    case 65:
        return "MIPS R4000";
    case 66:
        return "MIPS R4200";
    case 67:
        return "MIPS R4400";
    case 68:
        return "MIPS R4600";
    case 69:
        return "MIPS R10000";
    case 70:
        return "AMD C-Series Processor";
    case 71:
        return "AMD E-Series Processor";
    case 72:
        return "AMD A-Series Processor";
    case 73:
        return "AMD G-Series Processor";
    case 74:
        return "AMD Z-Series Processor";
    case 75:
        return "AMD R-Series Processor";
    case 76:
        return "AMD Opteron 4300 Series Processor";
    case 77:
        return "AMD Opteron 6300 Series Processor";
    case 78:
        return "AMD Opteron 3300 Series Processor";
    case 79:
        return "AMD FirePro Series Processor";
    case 80:
        return "SPARC Family";
    case 81:
        return "SuperSPARC";
    case 82:
        return "microSparc II";
    case 83:
        return "microSPARCK IIep";
    case 84:
        return "UltraSPARC";
    case 85:
        return "UltraSPARC II";
    case 86:
        return "UltraSPARC Iii";
    case 87:
        return "UltraSPARC III";
    case 88:
        return "UltraSPARC IIIi";
    case 96:
        return "68040 Family";
    case 97:
        return "68xxx";
    case 98:
        return "68000";
    case 99:
        return "68010";
    case 100:
        return "68020";
    case 101:
        return "68030";
    case 102:
        return "AMD Athlon(TM) X4 Quad-Core Processor Family";
    case 103:
        return "AMD Opteron(TM) X1000 Series Processor";
    case 104:
        return "AMD Opteron(TM) X2000 Series APU";
    case 112:
        return "Hobbit Family";
    case 120:
        return "Crusoe TM5000 Family";
    case 121:
        return "Crusoe TM3000 Family";
    case 122:
        return "Efficeon TM8000 Family";
    case 128:
        return "Weitek";
    case 130:
        return "Itanium Processor";
    case 131:
        return "AMD Athlon 64 Processor Fmaily";
    case 132:
        return "AMD Opteron Processor Family";
    case 133:
        return "AMD Sempron Processor Family";
    case 134:
        return "AMD Turion 64 Mobile Technology";
    case 135:
        return "Dual-Core AMD Opteron Processor Family";
    case 136:
        return "AMD Athlon 64 X2 Dual-Core Processor Family";
    case 137:
        return "AMD Turion 64 X2 Mobile Technology";
    case 138:
        return "Quad-Core AMD Opteron Processor Family";
    case 139:
        return "Thrid-Generation AMD Opteron Processor Family";
    case 140:
        return "AMD Phenom FX Quad-Core Processor Family";
    case 141:
        return "AMD Phenom X4 Quad-Core Processor Family";
    case 142:
        return "AMD Phenom X2 Dual-Core Processor Family";
    case 143:
        return "AMD Athlon X2 Dual-Core Processor Family";
    case 144:
        return "PA-RISC Family";
    case 145:
        return "PA-RISC 8500";
    case 146:
        return "PA-RISC 8000";
    case 147:
        return "PA-RISC 7300LC";
    case 148:
        return "PA-RISC 7200";
    case 149:
        return "PA-RISC 7100LC";
    case 150:
        return "PA-RISC 7100";
    case 160:
        return "V30 Family";
    case 161:
        return "Quad-Core Intel Xeon Processor 3200 Series";
    case 162:
        return "Dual-Core Intel Xeon Processor 3200 Series";
    case 163:
        return "Quad-Core Intel Xeon Processor 5300 Series";
    case 164:
        return "Dual-Core Intel Xeon Processor 5100 Series";
    case 165:
        return "Dual-Core Intel Xeon Processor 5000 Series";
    case 166:
        return "Dual-Core Intel Xeon Processor LV";
    case 167:
        return "Dual-Core Intel Xeon Processor ULV";
    case 168:
        return "Dual-Core Intel Xeon Processor 7100 Series";
    case 169:
        return "Quad-Core Intel Xeon Processor 5400 Series";
    case 170:
        return "Quad-Core Intel Xeon Processor";
    case 171:
        return "Dual-Core Intel Xeon Processor 5200 Series";
    case 172:
        return "Dual-Core Intel Xeon Processor 7200 Series";
    case 173:
        return "Quad-Core Intel Xeon Processor 7300 Series";
    case 174:
        return "Quad-Core Intel Xeon Processor 7400 Series";
    case 175:
        return "Multi-Core Intel Xeon Processor 7400 Series";
    case 176:
        return "Pentium III Xeon Processor";
    case 177:
        return "Pentium III Processor with Intel SpeedStep Technology";
    case 178:
        return "Pentium 4 Processor";
    case 179:
        return "Intel Xeon Processor";
    case 180:
        return "AS400 Family";
    case 181:
        return "Intel Xeon Processor MP";
    case 182:
        return "AMD Athlon XP Processor Family";
    case 183:
        return "AMD Athlon MP Processor Family";
    case 184:
        return "Intel Itanium 2 Processor";
    case 185:
        return "Intel Pentium M Processor";
    case 186:
        return "Intel Celeron D Processor";
    case 187:
        return "Intel Pentium D Processor";
    case 188:
        return "Intel Pentium Processor Extreme Edition";
    case 189:
        return "Intel Core Solo Processor";
    case 191:
        return "Intel Core 2 Duo Processor";
    case 192:
        return "Intel Core 2 Solo Processor";
    case 193:
        return "Intel Core 2 Extreme Processor";
    case 194:
        return "Intel Core 2 Quad Processor";
    case 195:
        return "Intel Core 2 Extreme Mobile Processor";
    case 196:
        return "Intel Core 2 Duo Mobile Processor";
    case 197:
        return "Intel Core 2 Solo Mobile Processor";
    case 198:
        return "Intel Core i7 Processor";
    case 199:
        return "Dual-Core Intel Celeron Processor";
    case 200:
        return "IBM390 Family";
    case 201:
        return "G4";
    case 202:
        return "G5";
    case 203:
        return "ESA/390 G6";
    case 204:
        return "z/Architecture Base";
    case 205:
        return "Intel Core i5 Processor";
    case 206:
        return "Intel Core i3 Processor";
    case 210:
        return "VIA C7-M Processor Family";
    case 211:
        return "VIA C7-D Processor Family";
    case 212:
        return "VIA C7 Processor Family";
    case 213:
        return "VIA Eden Processor Family";
    case 214:
        return "Multi-Core Intel Xeon Processor";
    case 215:
        return "Dual-Core Intel Xeon Processor 3xxx Series";
    case 216:
        return "Quad-Core Intel Xeon Processor 3xxx Series";
    case 217:
        return "VIA Nano Processor Family";
    case 218:
        return "Dual-Core Intel Xeon Processor 5xxx Series";
    case 219:
        return "Quad-Core Intel Xeon Processor 5xxx Series";
    case 221:
        return "Dual-Core Intel Xeon Processor 7xxx Series";
    case 222:
        return "Quad-Core Intel Xeon Processor 7xxx Series";
    case 223:
        return "Multi-Core Intel Xeon Processor 7xxx Series";
    case 224:
        return "Multi-Core Intel Xeon Processor 3400 Series";
    case 228:
        return "AMD Opteron 3000 Series Processor";
    case 229:
        return "AMD Sempron II Processor";
    case 230:
        return "Embedded AMD Opteron Quad-Core Processor Family";
    case 231:
        return "AMD Phenom Triple-Core Processor Family";
    case 232:
        return "AMD Turion Ultra Dual-Core Mobile Processor Family";
    case 233:
        return "AMD Turion Dual-Core Mobile Processor Family";
    case 234:
        return "AMD Athlon Dual-Core Processor Family";
    case 235:
        return "AMD Sempron SI Processor Family";
    case 236:
        return "AMD Phenom II Processor Family";
    case 237:
        return "AMD Athlon II Processor Family";
    case 238:
        return "Six-Core AMD Opteron Processor Family";
    case 239:
        return "AMD Sempron M Processor Family";
    case 250:
        return "i860";
    case 251:
        return "i960";
    case 254:
        return "Indicator to obtain the processor family from the Processor Family 2 Field";
    case 260:
        return "SH-3";
    case 261:
        return "SH-4";
    case 280:
        return "ARM";
    case 281:
        return "StrongARM";
    case 300:
        return "6x86";
    case 301:
        return "MediaGX";
    case 302:
        return "MII";
    case 320:
        return "WinChip";
    case 350:
        return "DSP";
    case 500:
        return "Video Processor";
    default:
        return "Other";
    }
}

void displayInformation(SMBIOSStructType5* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Memory Controller Information (Type " << curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tError Detecting Method: " << getErrorDetectingMethod(curStruct) << std::endl;
    displayErrorCorrectingCapability(curStruct);

    std::cout << "\tInterleave Support: " << getInterleaveSupport(curStruct->SupportedInterleave) << std::endl;
    std::cout << "\tCurrent Interleave: " << getInterleaveSupport(curStruct->CurrentInterleave) << std::endl;
    std::cout << "\tMaximum Memory Module Size: " << (int)curStruct->MaximumMemoryModuleSize << std::endl;
    
    displaySupportedSpeeds(curStruct);
    displaySupportedMemoryTypes(curStruct);
    displayMemoryModuleVolate(curStruct);
    
    std::cout << "\tNumber of Associated Memory Slots: " << (int)curStruct->NumberOfAssociatedMemorySlots << std::endl;

    std::cout << std::endl;
}

std::string getErrorDetectingMethod(SMBIOSStructType5* curStruct) {
    switch (curStruct->ErrorDetectingMethod) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "None";
    case 4:
        return "8-bit Parity";
    case 5:
        return "32-bit ECC";
    case 6:
        return "64-bit ECC";
    case 7:
        return "128-bit ECC";
    case 8:
        return "CRC";
    default:
        return "Other";
    }
}

void displayErrorCorrectingCapability(SMBIOSStructType5* curStruct) {
    std::cout << "\tError Correcting Capabilities: " << std::endl;
    BYTE errorCorr = curStruct->ErrorCorrectingCapability;
    if (getBit(errorCorr, 3)) {
        std::cout << "\t\tSingle-bit Error Correcting" << std::endl;
    }
    if (getBit(errorCorr, 4)) {
        std::cout << "\t\tDouble-bit Error Correcting" << std::endl;
    }
    if (getBit(errorCorr, 5)) {
        std::cout << "\t\tError Scrubbing" << std::endl;
    }
}

std::string getInterleaveSupport(BYTE Interleave) {
    switch (Interleave) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "One-Way Interleave";
    case 4:
        return "Two-Way Interleave";
    case 5:
        return "Four-Way Interleave";
    case 6:
        return "Eight-Way Interleave";
    case 7:
        return "Sixteen-way Interleave";
    default:
        return "Other";
    }
}

void displaySupportedSpeeds(SMBIOSStructType5* curStruct) {
    WORD speeds = curStruct->SupportedSpeeds;
    std::cout << "\tSupported Speeds: " << std::endl;
    if (getBit(speeds, 2)) {
        std::cout << "\t\t70 ns" << std::endl;
    }
    if (getBit(speeds, 3)) {
        std::cout << "\t\t60 ns" << std::endl;
    }
    if (getBit(speeds, 4)) {
        std::cout << "\t\t50 ns" << std::endl;
    }
}

void displaySupportedMemoryTypes(SMBIOSStructType5* curStruct) {
    WORD memory = curStruct->SupportedMemoryTypes;
    std::cout << "\tSupported Memory Types: " << std::endl;
    if (getBit(memory, 2)) {
        std::cout << "\t\tStandard" << std::endl;
    }
    if (getBit(memory, 3)) {
        std::cout << "\t\tFast Page Mode" << std::endl;
    }
    if (getBit(memory, 4)) {
        std::cout << "\t\tEDO" << std::endl;
    }
    if (getBit(memory, 5)) {
        std::cout << "\t\tParity" << std::endl;
    }
    if (getBit(memory, 6)) {
        std::cout << "\t\tECC" << std::endl;
    }
    if (getBit(memory, 7)) {
        std::cout << "\t\tSIMM" << std::endl;
    }
    if (getBit(memory, 8)) {
        std::cout << "\t\tDIMM" << std::endl;
    }
    if (getBit(memory, 9)) {
        std::cout << "\t\tBurst EDO" << std::endl;
    }
    if (getBit(memory, 10)) {
        std::cout << "\t\tSDRAM" << std::endl;
    }
}

void displayMemoryModuleVolate(SMBIOSStructType5* curStruct) {
    BYTE voltage = curStruct->MemoryModuleVoltage;
    std::cout << "\tMemory Module Voltage: " << std::endl;
    if (getBit(voltage, 2)) {
        std::cout << "2.9V" << std::endl;
    }
    if (getBit(voltage, 1)) {
        std::cout << "3.3V" << std::endl;
    }
    if (getBit(voltage, 0)) {
        std::cout << "5V" << std::endl;
    }
}

void displayInformation(SMBIOSStructType6* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Memory Module (Type " << (int)curStruct->Type << ")" << std::endl;
    
    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tSocket Designation: " << strings[curStruct->SocketDesignation] << std::endl;
    std::cout << "\tBank Connections: " << (int)curStruct->BankConnections << std::endl;
    std::cout << "\tCurrent Speed: " << (int)curStruct->CurrentSpeed << " ns" << std::endl;
    
    displayCurrentMemoryType(curStruct);
    
    std::cout << "\tInstalled Size" << std::endl;
    displaySize(curStruct->InstalledSize);
    std::cout << "\tEnabled Size" << std::endl;
    displaySize(curStruct->EnabledSize);

    displayErrorStatus(curStruct);
}

void displaySize(WORD size) {
    if (getBit(size, 7)) {
        std::cout << "\t\tDouble-Bank Connection" << std::endl;
    }
    else {
        std::cout << "\t\tSingle-Bank Connection" << std::endl;
    }

    int computed = pow(2, size);
    std::cout << "\t\t" << computed << "MB" << std::endl;
}

void displayCurrentMemoryType(SMBIOSStructType6* curStruct) {
    WORD memory = curStruct->CurrentMemoryType;
    std::cout << "\tMemory Module Information: " << std::endl;
    if (getBit(memory, 2)) {
        std::cout << "\t\tStandard" << std::endl;
    }
    if (getBit(memory, 3)) {
        std::cout << "\t\tFast Page Mode" << std::endl;
    }
    if (getBit(memory, 4)) {
        std::cout << "\t\tEDO" << std::endl;
    }
    if (getBit(memory, 5)) {
        std::cout << "\t\tParity" << std::endl;
    }
    if (getBit(memory, 6)) {
        std::cout << "\t\tECC" << std::endl;
    }
    if (getBit(memory, 7)) {
        std::cout << "\t\tSIMM" << std::endl;
    }
    if (getBit(memory, 8)) {
        std::cout << "\t\tDIMM" << std::endl;
    }
    if (getBit(memory, 9)) {
        std::cout << "\t\tBurst EDO" << std::endl;
    }
    if (getBit(memory, 10)) {
        std::cout << "\t\tSDRAM" << std::endl;
    }
}

void displayErrorStatus(SMBIOSStructType6* curStruct) {
    BYTE err = curStruct->ErrorStatus;
    std::cout << "\tError Status:" << std::endl;
    if (getBit(err, 1)) {
        std::cout << "\t\tCorrectable Errors Recieved" << std::endl;
    }
    if (getBit(err, 0)) {
        std::cout << "\t\tUncorrectabled Errors Recieved" << std::endl;
    }
}

void displayInformation(SMBIOSStructType7* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Cache Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tSocket Designation: " << strings[curStruct->SocketDesignation] << std::endl;

    displayCacheConfiguration(curStruct);
    std::cout << "\tMaximum ";
    displayCacheSize(curStruct->MaximumCacheSize);
    std::cout << "\tInstalled ";
    displayCacheSize(curStruct->InstalledSize);
    displaySRAMType(curStruct);

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tCache Module Speed: " << (int)curStruct->CacheSpeed << " ns" << std::endl;

    std::cout << "\tError Correction Type: " << getErrorCorrectionTypeField(curStruct) << std::endl;
    std::cout << "\tSystem Cache Type: " << getSystemCachetypeField(curStruct) << std::endl;
    std::cout << "\tAssociativity: " << getAssociativity(curStruct) << std::endl;

    std::cout << std::endl;
}

std::string getErrorCorrectionTypeField(SMBIOSStructType7* curStruct) {
    switch (curStruct->ErrorCorrectionType) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "None";
    case 4:
        return "Parity";
    case 5:
        return "Single-bit ECC";
    case 6:
        return "Multi-bit ECC";
    default:
        return "Other";
    }
}

std::string getSystemCachetypeField(SMBIOSStructType7* curStruct) {
    switch (curStruct->SystemCachetype) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "Instruction";
    case 4:
        return "Data";
    case 5:
        return "Unified";
    default:
        return "Other";
    }
}

std::string getAssociativity(SMBIOSStructType7* curStruct) {
    switch (curStruct->Associativity) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "Direct Mapped";
    case 4:
        return "2-Way Set-Associative";
    case 5:
        return "4-Way Set-Associative";
    case 6:
        return "Fully Associative";
    case 7:
        return "8-Way Set-Associative";
    case 8:
        return "16-Way Set-Associative";
    case 9:
        return "12-Way Set-Associative";
    case 10:
        return "24-Way Set-Associative";
    case 11:
        return "32-Way Set-Associative";
    case 12:
        return "48-Way Set-Associative";
    case 13:
        return "64-Way Set-Associative";
    case 14:
        return "20-Way Set-Associative";
    default:
        return "Other";
    }
}

void displayCacheConfiguration(SMBIOSStructType7* curStruct) {
    int operationalMode = getBits(curStruct->CacheConfiguration, 9, 8);
    std::cout << "\tCache Configuration:" << std::endl;
    switch (operationalMode) {
    case 0:
        std::cout << "\t\tWrite Through" << std::endl;
        break;
    case 1:
        std::cout << "\t\tWrite Back" << std::endl;
        break;
    }

    int enabledDisabled = getBit(curStruct->CacheConfiguration, 7);
    switch (enabledDisabled) {
    case 0:
        std::cout << "\t\tDisabled at boot time" << std::endl;
        break;
    case 1:
        std::cout << "\t\tEnabled at boot time" << std::endl;
        break;
    }

    int location = getBits(curStruct->CacheConfiguration, 6, 5);
    switch (location) {
    case 0:
        std::cout << "\t\tInternal to the CPU Module" << std::endl;
        break;
    case 1:
        std::cout << "\t\tExternal to the CPU Module" << std::endl;
        break;
    default:
        std::cout << "\t\tLocation unknown" << std::endl;
        break;
    }

    int socketed = getBit(curStruct->CacheConfiguration, 3);
    switch (socketed) {
    case 0:
        std::cout << "\t\tSocketed" << std::endl;
        break;
    case 1:
        std::cout << "\t\tNot Socketed" << std::endl;
        break;
    }

    int level = getBits(curStruct->CacheConfiguration, 2, 0);
    std::cout << "\t\tLevel: " << level + 1 << std::endl;
}

void displayCacheSize(WORD CacheSize) {
    int size = (getBit(CacheSize, 15)) ? 64 : 1;
    size *= getBits(CacheSize, 14, 0);
    std::cout << "Size: " << size << "K" << std::endl;
}

void displaySRAMType(SMBIOSStructType7* curStruct) {
    std::cout << "\tSRAM:" << std::endl;
    if (getBit(curStruct->CurrentSRAMType, 2)) {
        std::cout << "\t\tNon-Burst" << std::endl;
    }
    if (getBit(curStruct->CurrentSRAMType, 3)) {
        std::cout << "\t\tBurst" << std::endl;
    }
    if (getBit(curStruct->CurrentSRAMType, 4)) {
        std::cout << "\t\tPipeline Burst" << std::endl;
    }
    if (getBit(curStruct->CurrentSRAMType, 5)) {
        std::cout << "\t\tSynchronous" << std::endl;
    }
    if (getBit(curStruct->CurrentSRAMType, 6)) {
        std::cout << "\t\tAsynchronous" << std::endl;
    }
}

void displayInformation(SMBIOSStructType8* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Port Connector Information (Type " << (int)curStruct->Type << std::endl;

    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tInternal Reference Designator: " << strings[curStruct->InternalReferenceDesignator] << std::endl;
    std::cout << "\tInternal Connector Type: " << getConnectorType(curStruct->InternalConnectorType) << std::endl;
    std::cout << "\tExternal Reference Designator: " << strings[curStruct->ExternalReferenceDesignator] << std::endl;
    std::cout << "\tExternal Connector Type: " << getConnectorType(curStruct->ExternalConnectorType) << std::endl;
    std::cout << "\tPort Type: " << getPortType(curStruct) << std::endl;
}

std::string getConnectorType(BYTE connector) {
    switch (connector) {
    case 0:
        return "None";
    case 1:
        return "Centronics";
    case 2:
        return "Mini Centronics";
    case 3:
        return "Proprietary";
    case 4:
        return "DB-25 pin male";
    case 5:
        return "DB-25 pin female";
    case 6:
        return "DB-15 pin male";
    case 7:
        return "DB-15 pin female";
    case 8:
        return "DB-9 pin male";
    case 9:
        return "DB-9 pin female";
    case 10:
        return "RJ-11";
    case 11:
        return "RJ-45";
    case 12:
        return "50-pin MiniSCSI";
    case 13:
        return "Mini-DIN";
    case 14:
        return "Micro-DIN";
    case 15:
        return "PS/2";
    case 16:
        return "Infrared";
    case 17:
        return "HP-HIL";
    case 18:
        return "Access Bus (USB)";
    case 19:
        return "SSA SCSI";
    case 20:
        return "Circular DIN-8 Male";
    case 21:
        return "Circular DIN-8 Female";
    case 22:
        return "On Board IDE";
    case 23:
        return "On Board Floppy";
    case 24:
        return "9-pin Dual Inline (pin 10 cut)";
    case 25:
        return "25-pin Dual Inline (pin 26 cut)";
    case 26:
        return "50-pin Dual Inline";
    case 27:
        return "68-pin Dual Inline";
    case 28:
        return "On Board Sound Input from CD-Rom";
    case 29:
        return "Mini-Centronics Type-14";
    case 30:
        return "Mini-Centronics Type-26";
    case 31:
        return "Mini-jack (headphones)";
    case 32:
        return "BNC";
    case 33:
        return "1394";
    case 34:
        return "SAS/SATA Plug Receptable";
    case 160:
        return "PC-98";
    case 161:
        return "PC-98Hireso";
    case 162:
        return "PC-H98";
    case 163:
        return "PC-98Note";
    case 164:
        return "PC-98Full";
    default:
        return "Other";
    }
}

std::string getPortType(SMBIOSStructType8* curStruct) {
    switch (curStruct->PortType) {
    case 0:
        return "None";
    case 1:
        return "Parallel Port XT/AT Compatible";
    case 2:
        return "Parallel Port PS/2";
    case 3:
        return "Parallel Port ECP";
    case 4:
        return "Parallel Port EPP";
    case 5:
        return "Parallel Port ECP/EPP";
    case 6:
        return "Serial Port XT/AT Compatible";
    case 7:
        return "Serial Port 16450 Compatible";
    case 8:
        return "Serial Port 16550 Compatible";
    case 9:
        return "Serial Port 16550A Compatible";
    case 10:
        return "SCSI Port";
    case 11:
        return "MIDI Port";
    case 12:
        return "Joy Stick Port";
    case 13:
        return "Keyboard Port";
    case 14:
        return "Mouse Port";
    case 15:
        return "SSA SCSI";
    case 16:
        return "USB";
    case 17:
        return "FireWire (IEEE 1394)";
    case 18:
        return "PCMCIA Type I2";
    case 19:
        return "PCMCIA Type II";
    case 20:
        return "PCMCIA Type III";
    case 21:
        return "Cardbus";
    case 22:
        return "Access Bus Port";
    case 23:
        return "SCSI II";
    case 24:
        return "SCSI Wide";
    case 25:
        return "PC-98";
    case 26:
        return "PC-98-Hireso";
    case 27:
        return "PC-H98";
    case 28:
        return "Video Port";
    case 29:
        return "Audio Port";
    case 30:
        return "Modem Port";
    case 31:
        return "Network Port";
    case 32:
        return "SATA";
    case 33:
        return "SAS";
    case 160:
        return "8251 Compatible";
    case 161:
        return "8251 FIFO Compatible";
    default:
        return "Other";
    }
}

void displayInformation(SMBIOSStructType9* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "System Slots Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tSlot Designation: " << strings[curStruct->SlotDesignation] << std::endl;

    std::cout << "\tSlot Type: " << getSlotTypeField(curStruct) << std::endl;
    std::cout << "\tSlot Data Bus Width: " << getSlotDataBusWidth(curStruct) << std::endl;
    std::cout << "\tCurrent Usage: " << getCurrentUsage(curStruct) << std::endl;
    std::cout << "\tSlot Length: " << getSlotLength(curStruct) << std::endl;
    std::cout << "\tSlot ID: " << (int)curStruct->SlotID << std::endl;

    displaySlotCharacteristics1(curStruct);
    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1) {
        std::cout << std::endl;
        return;
    }

    displaySlotCharacteristics2(curStruct);
    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 6) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tSegment Group Number: " << (int)curStruct->SegmentGroupNumber << std::endl;
    std::cout << "\tBus Number: " << (int)curStruct->BusNumber << std::endl;
    std::cout << "\tDevice/Function Number: " << (int)curStruct->DeviceNumber << std::endl;

    std::cout << std::endl;
}

std::string getSlotTypeField(SMBIOSStructType9* curStruct) {
    switch (curStruct->SlotType) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "ISA";
    case 4:
        return "MCA";
    case 5:
        return "EISA";
    case 6:
        return "PCI";
    case 7:
        return "PC Card (PCMCIA)";
    case 8:
        return "VL-VESA";
    case 9:
        return "Proprietary";
    case 10:
        return "Processor Card Slot";
    case 11:
        return "Proprietary Memory Card Slot";
    case 12:
        return "I/O Riser Card Slot";
    case 13:
        return "NuBus";
    case 14:
        return "PCI - 66MHz Capable";
    case 15:
        return "AGP";
    case 16:
        return "AGP 2X";
    case 17:
        return "AGP 4X";
    case 18:
        return "PCI-X";
    case 19:
        return "AGP 8X";
    case 20:
        return "M.2 Socket 1-DP (Mechanical Key A)";
    case 21:
        return "M.2 Socket 1-SD (Mechanical Key E)";
    case 22:
        return "M.2 Socket 2 (Mechanical Key B)";
    case 23:
        return "M.2 Socket 3 (Mechanical Key M)";
    case 24:
        return "MXM Type I";
    case 25:
        return "MXM Type II";
    case 26:
        return "MXM Type III (Standard Connector)";
    case 27:
        return "MXM Type III (HE Connector)";
    case 28:
        return "MXM Type IV";
    case 29:
        return "MXM 3.0 Type A";
    case 30:
        return "MXM 3.0 Type B";
    case 31:
        return "PCI Express Gen 2 SFF-8639";
    case 32:
        return "PCI Express Gen 3 SFF-8639";
    case 160:
        return "PC-98/C20";
    case 161:
        return "PC-98/C24";
    case 162:
        return "PC-98/E";
    case 163:
        return "PC-98/LocalBus";
    case 164:
        return "PC-98/Card";
    case 165:
        return "PCI Express";
    case 166:
        return "PCI Express x1";
    case 167:
        return "PCI Express x2";
    case 168:
        return "PCI Express x4";
    case 169:
        return "PCI Express x8";
    case 170:
        return "PCI Express x16";
    case 171:
        return "PCI Experss Gen 2";
    case 172:
        return "PCI Express Gen 2 x1";
    case 173:
        return "PCI Express Gen 2 x2";
    case 174:
        return "PCI Express Gen 2 x4";
    case 175:
        return "PCI Express Gen 2 x8";
    case 176:
        return "PCI Express Gen 2 x16";
    case 177:
        return "PCI Express Gen 3";
    case 178:
        return "PCI Express Gen 3 x1";
    case 179:
        return "PCI Express Gen 3 x2";
    case 180:
        return "PCI Express Gen 3 x4";
    case 181:
        return "PCI Express Gen 3 x8";
    case 182:
        return "PCI Express Gen 3 x16";
    default:
        return "Other";
    }
}

std::string getSlotDataBusWidth(SMBIOSStructType9* curStruct) {
    switch (curStruct->SlotDataBusWidth) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "8 bit";
    case 4:
        return "16 bit";
    case 5:
        return "32 bit";
    case 6:
        return "64 bit";
    case 7:
        return "128 bit";
    case 8:
        return "1x or x1";
    case 9:
        return "2x or x2";
    case 10:
        return "4x or x4";
    case 11:
        return "8x or x8";
    case 12:
        return "12x or x12";
    case 13:
        return "16x or x16";
    case 14:
        return "32x or x23";
    default:
        return "Other";
    }
}

std::string getCurrentUsage(SMBIOSStructType9* curStruct) {
    switch (curStruct->CurrentUsage) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "Available";
    case 4:
        return "In Use";
    default:
        return "Other";
    }
}

std::string getSlotLength(SMBIOSStructType9* curStruct) {
    switch (curStruct->SlotLength) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "Short Length";
    case 4:
        return "Long Length";
    case 5:
        return "2.5\" drive form factor";
    case 6:
        return "3.5\" drive form factor";
    default:
        return "Other";
    }
}

void displaySlotCharacteristics1(SMBIOSStructType9* curStruct) {
    std::cout << "\tSlot Characteristics:" << std::endl;
    if (getBit(curStruct->SlotCharacteristics1, 1)) {
        std::cout << "\t\tProvides 5.0 Volts" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics1, 2)) {
        std::cout << "\t\tProvides 3.3 Volts" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics1, 3)) {
        std::cout << "\t\tSlot's opening is shared with another slot" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics1, 4)) {
        std::cout << "\t\tPC Card slot supports PC Card-16" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics1, 5)) {
        std::cout << "\t\tPC Card slot supports CardBus" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics1, 6)) {
        std::cout << "\t\tPC Card slot supports Zoom Video" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics1, 7)) {
        std::cout << "\t\tPC Card slot supports Modem Ring Resume" << std::endl;
    }
}

void displaySlotCharacteristics2(SMBIOSStructType9* curStruct) {
    if (getBit(curStruct->SlotCharacteristics2, 0)) {
        std::cout << "\t\tPCI Slot supports Power Management Event (PME#) Signal" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics2, 1)) {
        std::cout << "\t\tSlot supports hot-plug devices" << std::endl;
    }
    if (getBit(curStruct->SlotCharacteristics2, 2)) {
        std::cout << "\t\tPCI slot supports SMBus Signal" << std::endl;
    }
}

void displayInformation(SMBIOSStructType10* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "On Board Devices Information (Type " << (int)curStruct->Type << ")" << std::endl;

    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tDevice Type: " << getDeviceType(curStruct) << std::endl;
}

std::string getDeviceType(SMBIOSStructType10* curStruct) {
    std::string res = "";

    if (getBit(curStruct->DeviceType, 7)) {
        res += "Enabled ";
    }
    else {
        res += "Disabled ";
    }

    switch (getBits(curStruct->DeviceType, 6, 0)) {
    case 1:
        res += "Other";
        break;
    case 2:
        res += "Unknown";
        break;
    case 3:
        res += "Video";
        break;
    case 4:
        res += "SCSI Controller";
        break;
    case 5:
        res += "Ethernet";
        break;
    case 6:
        res += "Token Ring";
        break;
    case 7:
        res += "Sound";
        break;
    case 8:
        res += "PATA Controler";
        break;
    case 9:
        res += "SATA Controller";
        break;
    case 10:
        res += "SAS Controler";
        break;
    default:
        res += "Other";
        break;
    }

    return res;
}

void displayInformation(SMBIOSStructType11* curStruct, RawSMBIOSData* rawData) {
    std::cout << "OEM Strings (Type " << (int)curStruct->Type << ")" << std::endl;
    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tCount: " << (int)curStruct->Count << std::endl;
}

void displayInformation(SMBIOSStructType12* curStruct, RawSMBIOSData* rawData) {
    std::cout << "System Configuration Options (Type" << (int)curStruct->Type << ")" << std::endl;
    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tCount: " << (int)curStruct->Count << std::endl;
}

void displayInformation(SMBIOSStructType13* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "BIOS Language (Type " << (int)curStruct->Type << ")" << std::endl;
    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tNumber of Installed Languages: " << (int)curStruct->InstalledLanguages << std::endl;
    std::cout << "\tCurrent Language: " << strings[curStruct->CurrentLanguage] << std::endl;
}

void displayInformation(SMBIOSStructType14* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Group Associations (Type " << (int)curStruct->Type << ")" << std::endl;
    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tGroup Name: " << strings[curStruct->GroupName] << std::endl;
    std::cout << "\tItem (Structure) Type: " << (int)curStruct->ItemType << std::endl;
    std::cout << "\tItem (Structure) Handle: " << (int)curStruct->Handle << std::endl;
}

void displayInformation(SMBIOSStructType15* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "System Events Log (Type " << (int)curStruct->Type << ")" << std::endl;
    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tAccess Method: " << getAccessMethod(curStruct->AccessMethod) << std::endl;

    if (getBit(curStruct->LogStatus, 1)) {
        std::cout << "\tLog area full" << std::endl;
    }
    if (getBit(curStruct->LogStatus, 0)) {
        std::cout << "\tLog area valid" << std::endl;
    }

    std::cout << "\tLog Change Token: " << curStruct->LogChangeToken << std::endl;

    std::cout << std::endl;
}

std::string getAccessMethod(BYTE accessMethod) {
    switch (accessMethod) {
    case 0:
        return "Indexed I/O: 1 8-bit index port, 1 8-bit data port";
    case 1:
        return "Indexed I/O: 2 8-bit index ports, 1 8-bit data port";
    case 2:
        return "Indexed I/O: 1 16-bit index port, 1 8-bit data port";
    case 3:
        return "Memory-mapped physical 32-bit address";
    case 4:
        return "Available through general purpose non-volatile data functions";
    default:
        return "Other";
    }
}

void displayInformation(SMBIOSStructType16* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Physics Memory Array Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2 || (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1)) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tLocation: " << getLocation(curStruct) << std::endl;
    std::cout << "\tUse: " << getUse(curStruct) << std::endl;
    std::cout << "\tMemory Error Correction Type: " << getErrorCorrectionType(curStruct) << std::endl;

    std::cout << "\tMaximum Capacity: " << (int)curStruct->MaximumCapacity << "K" << std::endl;
    std::cout << "\tMemory Error Information Handle: " << (int)curStruct->MemoryErrorInformationHandle << std::endl;
    std::cout << "\tNumber of Memory Devices: " << (int)curStruct->NumberOfMemoryDevices << std::endl;
    
    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 7) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tExtended Maximum Capacity: " << (int)curStruct->ExtendedMaximumCapacity << std::endl;

    std::cout << std::endl;
}

std::string getLocation(SMBIOSStructType16* curStruct) {
    switch (curStruct->Location) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "System Board or Motherboard";
    case 4:
        return "ISA add-on card";
    case 5:
        return "EISA add-on card";
    case 6:
        return "PCI add-on card";
    case 7:
        return "MCA add-on card";
    case 8:
        return "PCMCIA add-on card";
    case 9:
        return "Proprietary add-on card";
    case 10:
        return "NuBus";
    case 160:
        return "PC-98/C20 Add-on Card";
    case 161:
        return "PC-98/C24 Add-on Card";
    case 162:
        return "PC-98/E Add-on Card";
    case 163:
        return "PC-98/Local Bus Add-on Card";
    default:
        return "Other";
    }
}

std::string getUse(SMBIOSStructType16* curStruct) {
    switch (curStruct->Use) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "System Memory";
    case 4:
        return "Video Memory";
    case 5:
        return "Flash Memory";
    case 6:
        return "Non-volatile RAM";
    case 7:
        return "Cache Memory";
    default:
        return "Other";
    }
}

std::string getErrorCorrectionType(SMBIOSStructType16* curStruct) {
    switch (curStruct->MemoryErrorCorrection) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "None";
    case 4:
        return "Parity";
    case 5:
        return "Single-bit ECC";
    case 6:
        return "Multi-bit ECC";
    case 7:
        return "CRC";
    default:
        return "Other";
    }
}

void displayInformation(SMBIOSStructType17* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Physics Memory Array Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2 || (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1)) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tPhysical Memory Array Handle: " << curStruct->PhysicalMemoryArrayHandle << std::endl;
    
    if (curStruct->MemoryErrorInformationHandle == 0xFFFE) {
        std::cout << "\tThere is no memory error information handle" << std::endl;
    }
    else if (curStruct->MemoryErrorInformationHandle == 0xFFFF) {
        std::cout << "\tThere is no memory error found" << std::endl;
    }
    else {
        std::cout << "\tMemory Error Information Handle: " << curStruct->MemoryErrorInformationHandle;
    }

    std::cout << "\tTotal Width: " << (int)curStruct->TotalWidth << std::endl;
    std::cout << "\tData Width: " << (int)curStruct->DataWidth << std::endl;
    std::cout << "\tSize: " << (int)curStruct->Size << std::endl;
    std::cout << "\tForm Factor: " << getFormFactor(curStruct) << std::endl;
    std::cout << "\tDevice Set: " << (int)curStruct->DeviceSet << std::endl;
    
    std::cout << "\tDevice Locator: " << strings[curStruct->DeviceLocator] << std::endl;

    std::cout << "\tBank Locator: " << strings[curStruct->BankLocator] << std::endl;

    std::cout << "\tMemory Device Type: " << getMemoryDeviceType(curStruct) << std::endl;

    displayTypeDetail(curStruct);

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 3) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tMaximum Capable Speed: " << (int)curStruct->Speed << "MHz" << std::endl;
    std::cout << "\tManufacturer: " << strings[curStruct->Manufacturer] << std::endl;

    std::cout << "\tSerial Number: " << strings[curStruct->SerialNumber] << std::endl;
    std::cout << "\tAsset Tag: " << strings[curStruct->AssetTag] << std::endl;
    std::cout << "\tPart Number: " << strings[curStruct->PartNumber] << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 6) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tAttributes: " << curStruct->Attributes % 16 << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 7) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tExtended Size: " << (int)curStruct->ExtendedSize << std::endl;
    std::cout << "\tConfigured Memory Clock Speed: " << (int)curStruct->ConfiguredMemoryClockSpeed << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 8) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tMinimum Voltage: " << (int)curStruct->MinimumVoltage << " milliVolts" << std::endl;
    std::cout << "\tMaximumVoltage: " << (int)curStruct->MaximumVoltage << " milliVolts" << std::endl;
    std::cout << "\tConfigured Voltage: " << (int)curStruct->ConfiguredVoltage << " milliVolts" << std::endl;

    std::cout << std::endl;
}

std::string getFormFactor(SMBIOSStructType17* curStruct) {
    switch (curStruct->FormFactor) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "SIMM";
    case 4:
        return "SIP";
    case 5:
        return "Chip";
    case 6:
        return "DIP";
    case 7:
        return "ZIP";
    case 8:
        return "Proprietary Card";
    case 9:
        return "DIMM";
    case 10:
        return "TSOP";
    case 11:
        return "Row of chips";
    case 12:
        return "RIMM";
    case 13:
        return "SODIMM";
    case 14:
        return "SRIMM";
    case 15:
        return "FB-DIMM";
    default:
        return "Other";
    }
}

std::string getMemoryDeviceType(SMBIOSStructType17* curStruct) {
    switch (curStruct->MemoryType) {
    case 1:
        return "Other";
    case 2:
        return "Unknown";
    case 3:
        return "DRAM";
    case 4:
        return "EDRAM";
    case 5:
        return "VRAM";
    case 6:
        return "SRAM";
    case 7:
        return "RAM";
    case 8:
        return "ROM";
    case 9:
        return "FLASH";
    case 10:
        return "EEPROM";
    case 11:
        return "FEPROM";
    case 12:
        return "EPROM";
    case 13:
        return "CDRAM";
    case 14:
        return "3DRAM";
    case 15:
        return "SDRAM";
    case 16:
        return "SGRAM";
    case 17:
        return "RDRAM";
    case 18:
        return "DDR";
    case 19:
        return "DDR2";
    case 20:
        return "DDR2 FB-DIMM";
    case 24:
        return "DDR3";
    case 25:
        return "FBD2";
    case 26:
        return "DDR4";
    case 27:
        return "LPDDR";
    case 28:
        return "LPDDR2";
    case 29:
        return "LPDDR3";
    case 30:
        return "LPDDR4";
    default:
        return "Other";
    }
}

void displayTypeDetail(SMBIOSStructType17* curStruct) {
    std::cout << "\tType Details:" << std::endl;
    if (getBit(curStruct->TypeDetail, 3)) {
        std::cout << "\t\tFast-paged" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 4)) {
        std::cout << "\t\tStatic column" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 5)) {
        std::cout << "\t\tPseudo-static" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 6)) {
        std::cout << "\t\tRAMBUS" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 7)) {
        std::cout << "\t\tSynchronous" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 8)) {
        std::cout << "\t\tCMOS" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 9)) {
        std::cout << "\t\tEDO" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 10)) {
        std::cout << "\t\tWindow DRAM" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 11)) {
        std::cout << "\t\tCache DRAM" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 12)) {
        std::cout << "\t\tNon-volatile" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 13)) {
        std::cout << "\t\tRegistered (buffered)" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 14)) {
        std::cout << "\t\tUnbuffered (unregistered)" << std::endl;
    }
    if (getBit(curStruct->TypeDetail, 15)) {
        std::cout << "\t\tLRDIMM" << std::endl;
    }
}

void displayInformation(SMBIOSStructType19* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Memory Array Mapped Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2 || (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1)) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tHandle: " << (int)curStruct->Handle << std::endl;
    std::cout << "\tStarting Address: " << (int)curStruct->StartingAddress << std::endl;
    std::cout << "\tEnding Address: " << (int)curStruct->EndingAddress << std::endl;
    std::cout << "\tMemory Array Handle: " << (int)curStruct->MemoryArrayHandle << std::endl;
    std::cout << "\tPartition Width: " << (int)curStruct->PartitionWidth << std::endl;

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 7) {
        std::cout << std::endl;
        return;
    }

    std::cout << "\tExtended Starting Address: " << (int)curStruct->ExtendedStartingAddress << std::endl;
    std::cout << "\tExtended Ending Address: " << (int)curStruct->ExtendedEndingAddress << std::endl;

    std::cout << std::endl;
}

void displayInformation(SMBIOSStructType32* curStruct, RawSMBIOSData* rawData) {
    std::cout << "System Boot Information (Type " << (int)curStruct->Type << ")" << std::endl;
    std::cout << "\tHandle: " << curStruct->Handle << std::endl;
    std::cout << "\tBoot Status: " << getBootStatus(curStruct) << std::endl;
    std::cout << std::endl;
}

std::string getBootStatus(SMBIOSStructType32* curStruct) {
    switch ((int)curStruct->BootStatus) {
    case 0:
        return "No errors detected";
    case 1:
        return "No bootable media";
    case 2:
        return "\"normal\" operating system failed to load";
    case 3:
        return "Firmware-detected hardware failure, including \"unknown\" failure types";
    case 4:
        return "Operating system-detected hardware failure";
    case 5:
        return "User-requested boot, usually through a keystroke";
    case 6:
        return "System Security violation";
    case 7:
        return "Previous-requested image";
    case 8:
        return "System watchdog timer expired, causing the system to reboot";
    default:
        return "Other";
    }
}