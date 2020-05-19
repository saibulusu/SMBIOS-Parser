#include "Functions.h"
#include <iostream>

// Get the raw SMBIOS table
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

// Display the entire SMBIOS table of data in hexadecimal by byte
void displayHexContents(RawSMBIOSData* raw_data) {
    for (int i = 0; i < raw_data->Length; ++i) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)raw_data->SMBIOSTableData[i] << " ";
        if (i % 32 == 31) {
            std::cout << std::endl;
        }
    }
    std::cout << std::dec << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

// Get a list of structures from the raw data
std::vector<SMBIOS_struct*> getStructureTable(RawSMBIOSData* raw_data) {
    std::vector<SMBIOS_struct*> structure_table;
    SMBIOS_struct* cur_struct = (SMBIOS_struct*)raw_data->SMBIOSTableData;
    while ((char*)cur_struct < (char*)raw_data + raw_data->Length) {
        structure_table.push_back(cur_struct);
        cur_struct = getNextStruct(cur_struct);
    }
    return structure_table;
}

// Display each structure in a list
void displayAllStructures(RawSMBIOSData* raw_data) {
    std::vector<SMBIOS_struct*> structure_table = getStructureTable(raw_data);
    for (int i = 0; i < structure_table.size(); ++i) {
        if (structure_table[i]->Type == 0) {
            displayInformation((SMBIOS_struct_type_0*)structure_table[i], raw_data);
        }
        else if (structure_table[i]->Type == 1) {
            displayInformation((SMBIOS_struct_type_1*)structure_table[i], raw_data);
        }
        else if (structure_table[i]->Type == 3) {
            displayInformation((SMBIOS_struct_type_3*)structure_table[i], raw_data);
        }
        else if (structure_table[i]->Type == 4) {
            displayInformation((SMBIOS_struct_type_4*)structure_table[i], raw_data);
        }
        else if (structure_table[i]->Type == 7) {
            displayInformation((SMBIOS_struct_type_7*)structure_table[i], raw_data);
        }
        else if (structure_table[i]->Type == 9) {
            displayInformation((SMBIOS_struct_type_9*)structure_table[i], raw_data);
        }
        else {
            displayInformation((SMBIOS_struct_non_required*)structure_table[i]);
        }
    }
}

// Get the next SMBIOS struct after the current one
SMBIOS_struct* getNextStruct(SMBIOS_struct* cur_struct) {
    char* strings_begin = (char*)cur_struct + cur_struct->Length;
    char* next_strings = strings_begin + 1;
    while (*strings_begin != NULL || *next_strings != NULL) {
        ++strings_begin;
        ++next_strings;
    }
    return (SMBIOS_struct*)(next_strings + 1);
}

// Gather the strings that belong to a structure
std::vector<std::string> getStrings(SMBIOS_struct* cur_struct) {
    std::vector<std::string> strings;
    std::string res = "";
    strings.push_back(res);
    char* cur_char = (char*)cur_struct + cur_struct->Length;
    SMBIOS_struct* next_struct = getNextStruct(cur_struct);

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

// Display the information of a non-required structure
void displayInformation(SMBIOS_struct_non_required* cur_struct) {
    std::cout << "Vendor-Specific SMBIOS structure (Type " << (int)cur_struct->Type << ")" << std::endl;
    std::cout << "Cannot display more information" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

// Get a specific bit from the characteristics bits
int getBit(BYTE bytes[], int bit_num, int num_bytes) {
    int whichBit = num_bytes - 1 - bit_num / 8;
    bit_num %= 8;
    return getBit(bytes[whichBit], bit_num);
}

int getBit(BYTE byte, int bit_num) {
    return (byte >> bit_num) % 2;
}

int getBit(WORD word, int bit_num) {
    return (word >> bit_num) % 2;
}

// Get consecutive bits
int getBits(BYTE byte, int startBit, int endBit) {
    return (byte >> endBit) % (1 << (startBit - endBit));
}

int getBits(WORD word, int startBit, int endBit) {
    return (word >> endBit) % (1 << (startBit - endBit));
}

// Display System BIOS Information (Type 0)
void displayInformation(SMBIOS_struct_type_0* cur_struct, RawSMBIOSData* raw_data) {
    std::vector<std::string> strings = getStrings(cur_struct);
    std::cout << "SMBIOS Information (Type " << (int)cur_struct->Type << ")" << std::endl;
    if ((int)raw_data->SMBIOSMajorVersion < 2) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    if (cur_struct->Vendor == 0) {
        std::cout << "There is no vendor information" << std::endl;
    }
    else {
        std::cout << "Vendor: " << strings[cur_struct->Vendor] << std::endl;
    }

    if (cur_struct->BIOS_Version == 0) {
        std::cout << "There is no BIOS version information" << std::endl;
    }
    else {
        std::cout << "BIOS Version: " << strings[cur_struct->BIOS_Version] << std::endl;
    }

    std::cout << "BIOS Starting Address Segment: " << std::hex << cur_struct->BIOS_Starting_Address_Segment << std::dec << std::endl;

    if (cur_struct->Bios_Release_Date == 0) {
        std::cout << "There is no BIOS release date information" << std::endl;
    }
    else {
        std::cout << "BIOS release Date: " << strings[cur_struct->Bios_Release_Date] << std::endl;
    }

    std::cout << "BIOS Rom Size: " << 64 + 64 * (int)cur_struct->BIOS_ROM_Size << "K" << std::endl;
    displayBIOSCharacteristics(cur_struct);
    if ((int)raw_data->SMBIOSMajorVersion == 2 && (int)raw_data->SMBIOSMinorVersion < 4) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }
    displayBIOSExtendedCharacteristics(cur_struct);
    std::cout << "Embedded Controller Firmware Major Release: " << (int)cur_struct->EC_Firmware_Major_Release << std::endl;
    std::cout << "Embedded Controller Firmware Minor Release: " << (int)cur_struct->EC_Firmware_Minor_Release << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

// Display BIOS Characteristics
void displayBIOSCharacteristics(SMBIOS_struct_type_0* cur_struct) {
    if (getBit(cur_struct->BIOS_Characteristics, 3, 8)) {
        std::cout << "BIOS Characteristics are not supported" << std::endl;
    }
    else {
        std::cout << "BIOS Characteristics are supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 4, 8)) {
        std::cout << "ISA is supported" << std::endl;
    }
    else {
        std::cout << "ISA is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 5, 8)) {
        std::cout << "MCA is supported" << std::endl;
    }
    else {
        std::cout << "MCA is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 6, 8)) {
        std::cout << "EISA is supported" << std::endl;
    }
    else {
        std::cout << "EISA is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 7, 8)) {
        std::cout << "PCI is supported" << std::endl;
    }
    else {
        std::cout << "PCI is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 8, 8)) {
        std::cout << "PC card (PCMCIA) is supported" << std::endl;
    }
    else {
        std::cout << "PC card (PCMCIA) is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 9, 8)) {
        std::cout << "Plug and Play is supported" << std::endl;
    }
    else {
        std::cout << "Plug and Play is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 10, 8)) {
        std::cout << "ACM is supported" << std::endl;
    }
    else {
        std::cout << "ACM is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 11, 8)) {
        std::cout << "BIOS is upgradeable" << std::endl;
    }
    else {
        std::cout << "BIOS is not upgradeable" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 12, 8)) {
        std::cout << "BIOS shadowing is allwoed" << std::endl;
    }
    else {
        std::cout << "BIOS shadowing is not allowed" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 13, 8)) {
        std::cout << "VL-VESA is supported" << std::endl;
    }
    else {
        std::cout << "VL-VESA is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 14, 8)) {
        std::cout << "ESCD support is available" << std::endl;
    }
    else {
        std::cout << "ESCD support is not available" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 15, 8)) {
        std::cout << "Boot from CD is supported" << std::endl;
    }
    else {
        std::cout << "Boot from CD is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 16, 8)) {
        std::cout << "Selectable boot is supported" << std::endl;
    }
    else {
        std::cout << "Selectable boot is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 17, 8)) {
        std::cout << "BIOS ROM is socketed" << std::endl;
    }
    else {
        std::cout << "BIOS ROM is not socketed" << std::endl;
    }
    
    if (getBit(cur_struct->BIOS_Characteristics, 18, 8)) {
        std::cout << "Boot from PC card (PCMCIA) is supported" << std::endl;
    }
    else {
        std::cout << "Boot from PC card (PCMCIA) is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics, 19, 8)) {
        std::cout << "EDD specification is supported" << std::endl;
    }
    else {
        std::cout << "EDD specification is not supported" << std::endl;
    }
}

// Display BIOS Extended characteristics
void displayBIOSExtendedCharacteristics(SMBIOS_struct_type_0* cur_struct) {
    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 7)) {
        std::cout << "ACPI is supported" << std::endl;
    }
    else {
        std::cout << "ACPI is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 6)) {
        std::cout << "USB Legacy is supported" << std::endl;
    }
    else {
        std::cout << "USB Legacy is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 5)) {
        std::cout << "AGP is supported" << std::endl;
    }
    else {
        std::cout << "AGP is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 4)) {
        std::cout << "I2O Boot is supported" << std::endl;
    }
    else {
        std::cout << "I2O Boot is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 3)) {
        std::cout << "LS-120 SuperDisk boot is supported" << std::endl;
    }
    else {
        std::cout << "LS-120 SuperDisk boot is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 2)) {
        std::cout << "ATAPI ZIP drive boot is supported" << std::endl;
    }
    else {
        std::cout << "ATAPI ZIP drive boot is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 1)) {
        std::cout << "1394 boot is supported" << std::endl;
    }
    else {
        std::cout << "1394 boot is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[0], 0)) {
        std::cout << "Smart battery is supported" << std::endl;
    }
    else {
        std::cout << "Smart battery is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[1], 0)) {
        std::cout << "BIOS Boot specification is supported" << std::endl;
    }
    else {
        std::cout << "BIOS Boot specification is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[1], 1)) {
        std::cout << "Function key-initiated network service is supported" << std::endl;
    }
    else {
        std::cout << "Function key-initiated network service is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[1], 2)) {
        std::cout << "Enabled targeted content distribution" << std::endl;
    }
    else {
        std::cout << "Disabled targeted content distribution" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[1], 3)) {
        std::cout << "UEFI Specification is supported" << std::endl;
    }
    else {
        std::cout << "UEFI Specification is not supported" << std::endl;
    }

    if (getBit(cur_struct->BIOS_Characteristics_Extensions[1], 4)) {
        std::cout << "SMBIOS Table describes a virtual machine" << std::endl;
    }
}

// Display System Information (Type 1)
void displayInformation(SMBIOS_struct_type_1* cur_struct, RawSMBIOSData* raw_data) {
    std::vector<std::string> strings = getStrings(cur_struct);
    std::cout << "System Information (Type " << (int)cur_struct->Type << ")" << std::endl;

    if ((int)raw_data->SMBIOSMajorVersion < 2) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    if (cur_struct->Manufacturer == 0) {
        std::cout << "There is no manufacturer information" << std::endl;
    }
    else {
        std::cout << "Manufacturer: " << strings[cur_struct->Manufacturer] << std::endl;
    }

    if (cur_struct->ProductName == 0) {
        std::cout << "There is no product name information" << std::endl;
    }
    else {
        std::cout << "Product Name: " << strings[cur_struct->ProductName] << std::endl;
    }

    if (cur_struct->Version == 0) {
        std::cout << "There is no version information" << std::endl;
    }
    else {
        std::cout << "Version: " << strings[cur_struct->Version] << std::endl;
    }

    if (cur_struct->SerialNumber == 0) {
        std::cout << "There is no serial number information" << std::endl;
    }
    else {
        std::cout << "Serial Number: " << strings[cur_struct->SerialNumber] << std::endl;
    }

    if ((int)raw_data->SMBIOSMajorVersion == 2 && (int)raw_data->SMBIOSMinorVersion < 1) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "UUID: " << std::hex << (int)cur_struct->UUID << std::dec<< std::endl;
    std::cout << "Wake-up Type: " << getWakeUpType(cur_struct) << std::endl;
    
    if ((int)raw_data->SMBIOSMajorVersion == 2 && (int)raw_data->SMBIOSMinorVersion < 4) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    if (cur_struct->SKUNumber == 0) {
        std::cout << "There is no SKU Number information" << std::endl;
    }
    else {
        std::cout << "SKU Number: " << strings[cur_struct->SKUNumber] << std::endl;
    }

    if (cur_struct->Family == 0) {
        std::cout << "Family: " << strings[cur_struct->Family] << std::endl;
    }

    std::cout << "--------------------------------------------------------" << std::endl;
}

// Get the wake-up type field associated with the structure
std::string getWakeUpType(SMBIOS_struct_type_1* cur_struct) {
    switch (cur_struct->WakeUpType) {
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

// Display Chassis Information (Type 3)
void displayInformation(SMBIOS_struct_type_3* cur_struct, RawSMBIOSData* raw_data) {
    std::vector<std::string> strings = getStrings(cur_struct);
    std::cout << "Chassis Information (Type " << (int)cur_struct->Type << ")" << std::endl;

    if (raw_data->SMBIOSMajorVersion < 2) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    if (cur_struct->Manufacturer == NULL) {
        std::cout << "There is no manufacturer information" << std::endl;
    }
    else {
        std::cout << "Manufacturer: " << strings[cur_struct->Manufacturer] << std::endl;
    }

    displayChassisType(cur_struct);
    
    if (cur_struct->Version == 0) {
        std::cout << "There is no version information" << std::endl;
    }
    else {
        std::cout << "Version: " << strings[cur_struct->Version] << std::endl;
    }

    if (cur_struct->SerialNumber == 0) {
        std::cout << "There is no serial number information" << std::endl;
    }
    else {
        std::cout << "Serial Number: " << strings[cur_struct->SerialNumber] << std::endl;
    }

    if (cur_struct->AssetTagNumber == 0) {
        std::cout << "There is no asset tag number information" << std::endl;
    }
    else {
        std::cout << "Asset Tag Number: " << strings[cur_struct->AssetTagNumber] << std::endl;
    }

    if (raw_data->SMBIOSMajorVersion == 2 && raw_data->SMBIOSMinorVersion < 1) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "Boot-up State: " << getChassisState(cur_struct->BootUpState) << std::endl;
    std::cout << "Power Supply State: " << getChassisState(cur_struct->PowerSupplyState) << std::endl;
    std::cout << "Thermal State: " << getChassisState(cur_struct->ThermalState) << std::endl;

    std::cout << "Security State: " << getChassisSecurityState(cur_struct->SecurityStatus) << std::endl;

    if (raw_data->SMBIOSMajorVersion == 2 && raw_data->SMBIOSMinorVersion < 3) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    if (cur_struct->NumberOfPowerCords == 0) {
        std::cout << "Unspecified number of power chords" << std::endl;
    }
    else {
        std::cout << "Number of Power Chords: " << (int)cur_struct->NumberOfPowerCords << std::endl;
    }

    std::cout << "--------------------------------------------------------" << std::endl;
}

// Display the chassis type
void displayChassisType(SMBIOS_struct_type_3* cur_struct) {
    BYTE characteristics[100];
    characteristics[0] = cur_struct->ChassisType;
    if (getBit(characteristics, 7, 1) == 1) {
        std::cout << "Chassis locked" << std::endl;
        characteristics[0] %= 128;
    }
    else {
        std::cout << "Unsure whether chassis is locked" << std::endl;
    }

    std::cout << "Chassis Type: ";
    switch (characteristics[0]) {
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

// Get the boot up state information
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

// Get the Chassis security state
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

// Display Processor Information (Type 4)
void displayInformation(SMBIOS_struct_type_4* cur_struct, RawSMBIOSData* raw_data) {
    std::vector<std::string> strings = getStrings(cur_struct);
    std::cout << "Processor Information (Type " << (int)cur_struct->Type << ")" << std::endl;

    if (raw_data->SMBIOSMajorVersion < 2) {
        return;
    }

    if (cur_struct->SocketDesignation == 0) {
        std::cout << "There is no socket designation information" << std::endl;
    }
    else {
        std::cout << "Socket Designation: " << strings[cur_struct->SocketDesignation] << std::endl;
    }

    std::cout << "Processor Type: " << getProcessorType(cur_struct) << std::endl;
    std::cout << "Processor Family: " << getProcessorFamily(cur_struct) << std::endl;

    if (cur_struct->ProcessorManufacturer == 0) {
        std::cout << "There is no processor manufacturer information" << std::endl;
    }
    else {
        std::cout << "Processor Manufacturer: " << strings[cur_struct->ProcessorManufacturer] << std::endl;
    }

    std::cout << "Processor ID: " << (int)cur_struct->ProcessorID << std::endl;
    
    if (cur_struct->ProcessorVersion == 0) {
        std::cout << "There is no processor version information" << std::endl;
    } 
    else {
        std::cout << "Processor Version: " << strings[cur_struct->ProcessorVersion] << std::endl;
    }

    std::cout << "Voltage: " << getVoltage(cur_struct) << std::endl;
    std::cout << "External Clock: " << (int)cur_struct->ExternalClock << "MHz" << std::endl;
    std::cout << "Max Processor Speed: " << (int)cur_struct->MaxSpeed << "MHz" << std::endl;
    std::cout << "Current Processor Speed: " << (int)cur_struct->CurrentSpeed << "MHz" << std::endl;
    std::cout << "Processor Status: " << getProcessorStatus(cur_struct) << std::endl;
    std::cout << "Processor Upgrade: " << getProcessorUpgrade(cur_struct) << std::endl;

    if (raw_data->SMBIOSMajorVersion == 2 && raw_data->SMBIOSMinorVersion < 1) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "L1 Cache Handle: " << (int)cur_struct->L1CacheHandle << std::endl;
    std::cout << "L2 Cache Handle: " << (int)cur_struct->L2CacheHandle << std::endl;
    std::cout << "L3 Cache Handle: " << (int)cur_struct->L3CacheHandle << std::endl;

    if (raw_data->SMBIOSMajorVersion == 2 && raw_data->SMBIOSMinorVersion < 3) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    if (cur_struct->SerialNumber == 0) {
        std::cout << "There is no serial number information" << std::endl;
    }
    else {
        std::cout << "Serial Number: " << strings[cur_struct->SerialNumber] << std::endl;
    }

    if (cur_struct->AssetTag == 0) {
        std::cout << "There is no asset tag information" << std::endl;
    }
    else {
        std::cout << "Asset Tag: " << strings[cur_struct->AssetTag] << std::endl;
    }

    if (cur_struct->PartNumber == 0) {
        std::cout << "There is no part number information" << std::endl;
    }
    else {
        std::cout << "Part Number: " << strings[cur_struct->PartNumber] << std::endl;
    }

    if (raw_data->SMBIOSMajorVersion == 2 && raw_data->SMBIOSMinorVersion < 5) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "Core Count: " << (int)cur_struct->CoreCount << std::endl;
    std::cout << "Core Enabled: " << (int)cur_struct->CoreEnabled << std::endl;
    std::cout << "Thread Count: " << (int)cur_struct->ThreadCount << std::endl;

    displayProcessorCharacteristics(cur_struct);
    std::cout << "Processor Family 2: " << getProcessorFamily2(cur_struct) << std::endl;
    if (cur_struct->CoreCount2 == 0) {
        std::cout << "Core Count 2: Unkown" << std::endl;
    }
    else {
        std::cout << "Core Count 2: " << (int)cur_struct->CoreCount2 << std::endl;
    }

    if (cur_struct->CoreEnabled2 == 0) {
        std::cout << "Core Enabled 2: Unknown" << std::endl;
    }
    else {
        std::cout << "Core Enabled 2: " << (int)cur_struct->CoreEnabled2 << std::endl;
    }

    if (cur_struct->ThreadCount2 == 0) {
        std::cout << "Thread Count 2: Unknown" << std::endl;
    }
    else {
        std::cout << "Thread Count 2: " << (int)cur_struct->ThreadCount2 << std::endl;
    }

    std::cout << "--------------------------------------------------------" << std::endl;
}

// Parse the processor type
std::string getProcessorType(SMBIOS_struct_type_4* cur_struct) {
    switch (cur_struct->ProcessorType) {
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

// Parse the processor family
std::string getProcessorFamily(SMBIOS_struct_type_4* cur_struct) {
    switch (cur_struct->ProcessorFamily) {
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

// Parse the voltage of the processor
std::string getVoltage(SMBIOS_struct_type_4* cur_struct) {
    BYTE volts[100];
    volts[0] = cur_struct->Voltage;
    
    if (getBit(volts, 0, 1) == 1) {
        return "5V";
    }
    else if (getBit(volts, 1, 1) == 1) {
        return "3.3V";
    }
    else if (getBit(volts, 2, 1) == 1) {
        return "2.9V";
    }
    return "Other";
}

// Get the status of the processor
std::string getProcessorStatus(SMBIOS_struct_type_4* cur_struct) {
    BYTE stats[100];
    stats[0] = cur_struct->Status;
    
    std::string res = "";

    if (getBit(stats, 6, 1) == 1) {
        res += "CPU Socket Population";
    }
    else {
        res += "CPU Socket Unpopulated";
    }

    res += ", ";

    int lowerBits = cur_struct->Status >> 5;
    switch (lowerBits) {
    case 0:
        res += "Unknown";
        break;
    case 1:
        res += "CPU Enabled";
        break;
    case 2:
        res += "CPU Disabled by User Through BIOS Setup";
        break;
    case 3:
        res += "CPU Disabled by BIOS (POST Error)";
        break;
    case 4:
        res += "CPU is Idle, Waiting to be Enabled";
        break;
    default:
        res += "Other";
        break;
    }
    return res;
}

// Get processor upgrade information
std::string getProcessorUpgrade(SMBIOS_struct_type_4* cur_struct) {
    switch (cur_struct->ProcessorUpgrade) {
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

// Display what the processor is capable of
void displayProcessorCharacteristics(SMBIOS_struct_type_4* cur_struct) {
    BYTE characteristics[100];
    characteristics[0] = cur_struct->ProcessorCharacteristics;
    std::cout << "Capabilities: ";
    if (getBit(characteristics, 2, 1) == 1) {
        std::cout << "64-bit Capable ";
    }
    if (getBit(characteristics, 3, 1) == 1) {
        std::cout << "Multi-Core ";
    }
    if (getBit(characteristics, 4, 1) == 1) {
        std::cout << "Hardware Thread ";
    }
    if (getBit(characteristics, 5, 1) == 1) {
        std::cout << "Execute Protection ";
    }
    if (getBit(characteristics, 6, 1) == 1) {
        std::cout << "Enhanced Virtualization ";
    }
    if (getBit(characteristics, 7, 1) == 1) {
        std::cout << "Power/Performance Control ";
    }
    std::cout << std::endl;
}

// Get the processor's second family
std::string getProcessorFamily2(SMBIOS_struct_type_4* cur_struct) {
    switch (cur_struct->ProcessorFamily2) {
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

// Display Cache Information (Type 7)
void displayInformation(SMBIOS_struct_type_7* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "Cache Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "Handle: " << (int)curStruct->Handle << std::endl;
    
    if (curStruct->SocketDesignation == 0) {
        std::cout << "No socket designation information" << std::endl;
    }
    else {
        std::cout << "Socket Designation: " << strings[curStruct->SocketDesignation] << std::endl;
    }

    displayCacheConfiguration(curStruct);
    std::cout << "Maximum ";
    displayCacheSize(curStruct->MaximumCacheSize);
    std::cout << "Installed ";
    displayCacheSize(curStruct->InstalledSize);
    displaySRAMType(curStruct);

    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    if (curStruct->CacheSpeed == 0) {
        std::cout << "Unknown Speed" << std::endl;
    }
    else {
        std::cout << "Cache Module Speed: " << (int)curStruct->CacheSpeed << " ns" << std::endl;
    }

    std::cout << "Error Correction Type: " << getErrorCorrectionTypeField(curStruct) << std::endl;
    std::cout << "System Cache Type: " << getSystemCachetypeField(curStruct) << std::endl;
    std::cout << "Associativity: " << getAssociativity(curStruct) << std::endl;

    std::cout << "--------------------------------------------------------" << std::endl;
}

// Get the error correction enumeration
std::string getErrorCorrectionTypeField(SMBIOS_struct_type_7* curStruct) {
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

// Get the cache type information
std::string getSystemCachetypeField(SMBIOS_struct_type_7* curStruct) {
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

// Get the associativity of the cache
std::string getAssociativity(SMBIOS_struct_type_7* curStruct) {
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

// Display the cache's configuration
void displayCacheConfiguration(SMBIOS_struct_type_7* curStruct) {
    int operationalMode = getBits(curStruct->CacheConfiguration, 9, 8);
    switch (operationalMode) {
    case 0:
        std::cout << "Write Through" << std::endl;
        break;
    case 1:
        std::cout << "Write Back" << std::endl;
        break;
    }

    int enabledDisabled = getBit(curStruct->CacheConfiguration, 7);
    switch (enabledDisabled) {
    case 0:
        std::cout << "Disabled at boot time" << std::endl;
        break;
    case 1:
        std::cout << "Enabled at boot time" << std::endl;
        break;
    }

    int location = getBits(curStruct->CacheConfiguration, 6, 5);
    switch (location) {
    case 0:
        std::cout << "Internal to the CPU Module" << std::endl;
        break;
    case 1:
        std::cout << "External to the CPU Module" << std::endl;
        break;
    default:
        std::cout << "Location unknown" << std::endl;
        break;
    }

    int socketed = getBit(curStruct->CacheConfiguration, 3);
    switch (socketed) {
    case 0:
        std::cout << "Socketed" << std::endl;
        break;
    case 1:
        std::cout << "Not Socketed" << std::endl;
        break;
    }

    int level = getBits(curStruct->CacheConfiguration, 2, 0);
    std::cout << "Level: " << level + 1 << std::endl;
}

// Display the maximum or installed cache size
void displayCacheSize(WORD CacheSize) {
    int size = (getBit(CacheSize, 15)) ? 64 : 1;
    size *= getBits(CacheSize, 14, 0);
    std::cout << "Size: " << size << "K" << std::endl;
}

// Display information about the SRAM
void displaySRAMType(SMBIOS_struct_type_7* curStruct) {
    std::cout << "SRAM: ";
    if (getBit(curStruct->CurrentSRAMType, 13)) {
        std::cout << "Non-Burst ";
    }
    if (getBit(curStruct->CurrentSRAMType, 12)) {
        std::cout << "Burst ";
    }
    if (getBit(curStruct->CurrentSRAMType, 11)) {
        std::cout << "Pipeline Burst ";
    }
    if (getBit(curStruct->CurrentSRAMType, 10)) {
        std::cout << "Synchronous ";
    }
    if (getBit(curStruct->CurrentSRAMType, 9)) {
        std::cout << "Asynchronous ";
    }
    std::cout << std::endl;
}

// Display Sytem Slots Information (Type 9)
void displayInformation(SMBIOS_struct_type_9* curStruct, RawSMBIOSData* rawData) {
    std::vector<std::string> strings = getStrings(curStruct);
    std::cout << "System Slots Information (Type " << (int)curStruct->Type << ")" << std::endl;

    if (rawData->SMBIOSMajorVersion < 2) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "Handle: " << curStruct->Handle << std::endl;
    
    if (curStruct->SlotDesignation == 0) {
        std::cout << "There is no slot designation information" << std::endl;
    }
    else {
        std::cout << "Slot Designation: " << strings[curStruct->SlotDesignation] << std::endl;
    }

    std::cout << "Slot Type: " << getSlotTypeField(curStruct) << std::endl;
    std::cout << "Slot Data Bus Width: " << getSlotDataBusWidth(curStruct) << std::endl;
    std::cout << "Current Usage: " << getCurrentUsage(curStruct) << std::endl;
    std::cout << "Slot Length: " << getSlotLength(curStruct) << std::endl;
    std::cout << "Slot ID: " << (int)curStruct->SlotID << std::endl;

    displaySlotCharacteristics1(curStruct);
    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 1) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    displaySlotCharacteristics2(curStruct);
    if (rawData->SMBIOSMajorVersion == 2 && rawData->SMBIOSMinorVersion < 6) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "Segment Group Number: " << (int)curStruct->SegmentGroupNumber << std::endl;
    std::cout << "Bus Number: " << (int)curStruct->BusNumber << std::endl;
    std::cout << "Device/Function Number: " << (int)curStruct->DeviceNumber << std::endl;

    std::cout << "--------------------------------------------------------" << std::endl;
}

std::string getSlotTypeField(SMBIOS_struct_type_9* curStruct) {
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

std::string getSlotDataBusWidth(SMBIOS_struct_type_9* curStruct) {
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

std::string getCurrentUsage(SMBIOS_struct_type_9* curStruct) {
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

std::string getSlotLength(SMBIOS_struct_type_9* curStruct) {
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

void displaySlotCharacteristics1(SMBIOS_struct_type_9* curStruct) {
    std::cout << "Slot Characteristics 1: ";
    if (getBit(curStruct->SlotCharacteristics1, 6)) {
        std::cout << "Provides 5.0 Volts ";
    }
    if (getBit(curStruct->SlotCharacteristics1, 5)) {
        std::cout << "Provides 3.3 Volts ";
    }
    if (getBit(curStruct->SlotCharacteristics1, 4)) {
        std::cout << "Slot's opening is shared with another slot ";
    }
    if (getBit(curStruct->SlotCharacteristics1, 3)) {
        std::cout << "PC Card slot supports PC Card-16 ";
    }
    if (getBit(curStruct->SlotCharacteristics1, 2)) {
        std::cout << "PC Card slot supports CardBus ";
    }
    if (getBit(curStruct->SlotCharacteristics1, 1)) {
        std::cout << "PC Card slot supports Zoom Video ";
    }
    if (getBit(curStruct->SlotCharacteristics1, 0)) {
        std::cout << "PC Card slot supports Modem Ring Resume ";
    }
    std::cout << std::endl;
}

void displaySlotCharacteristics2(SMBIOS_struct_type_9* curStruct) {
    std::cout << "Slot Characteristics 2: ";
    if (getBit(curStruct->SlotCharacteristics2, 7)) {
        std::cout << "PCI Slot supports Power Management Event (PME#) Signal ";
    }
    if (getBit(curStruct->SlotCharacteristics2, 6)) {
        std::cout << "Slot supports hot-plug devices ";
    }
    if (getBit(curStruct->SlotCharacteristics2, 5)) {
        std::cout << "PCI slot supports SMBus Signal ";
    }
    std::cout << std::endl;
}

void displayInformation(SMBIOS_struct_type_16* curStruct, RawSMBIOSData* rawData) {

}

void displayInformation(SMBIOS_struct_type_17* curStruct, RawSMBIOSData* rawData) {

}

void displayInformation(SMBIOS_struct_type_19* curStruct, RawSMBIOSData* rawData) {

}

void displayInformation(SMBIOS_struct_type_32* curStruct, RawSMBIOSData* rawData) {

}