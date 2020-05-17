#include "Functions.h"
#include <iostream>

// Get the raw SMBIOS table
RawSMBIOSData* get_raw_data() {
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
void display_hex_contents(RawSMBIOSData* raw_data) {
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
std::vector<SMBIOS_struct*> get_structure_table(RawSMBIOSData* raw_data) {
    std::vector<SMBIOS_struct*> structure_table;
    SMBIOS_struct* cur_struct = (SMBIOS_struct*)raw_data->SMBIOSTableData;
    while ((char*)cur_struct < (char*)raw_data + raw_data->Length) {
        structure_table.push_back(cur_struct);
        cur_struct = get_next_struct(cur_struct);
    }
    return structure_table;
}

void displayStructureTable(RawSMBIOSData* raw_data) {
    std::vector<SMBIOS_struct*> structure_table = get_structure_table(raw_data);
    for (int i = 0; i < structure_table.size(); ++i) {
        if (structure_table[i]->Type == 0) {
            displayInformation((SMBIOS_struct_type_0*)structure_table[i], raw_data);
        }
        else if (structure_table[i]->Type == 1) {
            displayInformation((SMBIOS_struct_type_1*)structure_table[i], raw_data);
        }
        else if (structure_table[i]->Type == 2) {
            displayInformation((SMBIOS_struct_type_2*)structure_table[i], raw_data);
        }
        else {
            displayInformation((SMBIOS_struct_non_required*)structure_table[i]);
        }
    }
}

// Get the next SMBIOS struct after the current one
SMBIOS_struct* get_next_struct(SMBIOS_struct* cur_struct) {
    char* strings_begin = (char*)cur_struct + cur_struct->Length;
    char* next_strings = strings_begin + 1;
    while (*strings_begin != NULL || *next_strings != NULL) {
        ++strings_begin;
        ++next_strings;
    }
    return (SMBIOS_struct*)(next_strings + 1);
}

// Gather the strings that belong to a structure
std::vector<std::string> get_strings(SMBIOS_struct* cur_struct) {
    std::vector<std::string> strings;
    std::string res = "";
    strings.push_back(res);
    char* cur_char = (char*)cur_struct + cur_struct->Length;
    SMBIOS_struct* next_struct = get_next_struct(cur_struct);

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
}

// Display System BIOS Information (Type 0)
void displayInformation(SMBIOS_struct_type_0* cur_struct, RawSMBIOSData* raw_data) {
    std::vector<std::string> strings = get_strings(cur_struct);
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

// Get a specific bit from the characteristics bits
int get_bit(BYTE characteristics[], int bit_num, int num_bytes){
    int index = 0;
    index += (bit_num / 8);
    bit_num %= 8;
    bit_num = 7 - bit_num;
    return characteristics[index] & (1 << bit_num);
}

// Display BIOS Characteristics
void displayBIOSCharacteristics(SMBIOS_struct_type_0* cur_struct) {
    //BYTE characteristics[8] = cur_struct->BIOS_Characteristics;
    if (get_bit(cur_struct->BIOS_Characteristics, 3, 8)) {
        std::cout << "BIOS Characteristics are not supported" << std::endl;
    }
    else {
        std::cout << "BIOS Characteristics are supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 4, 8)) {
        std::cout << "ISA is supported" << std::endl;
    }
    else {
        std::cout << "ISA is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 5, 8)) {
        std::cout << "MCA is supported" << std::endl;
    }
    else {
        std::cout << "MCA is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 6, 8)) {
        std::cout << "EISA is supported" << std::endl;
    }
    else {
        std::cout << "EISA is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 7, 8)) {
        std::cout << "PCI is supported" << std::endl;
    }
    else {
        std::cout << "PCI is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 8, 8)) {
        std::cout << "PC card (PCMCIA) is supported" << std::endl;
    }
    else {
        std::cout << "PC card (PCMCIA) is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 9, 8)) {
        std::cout << "Plug and Play is supported" << std::endl;
    }
    else {
        std::cout << "Plug and Play is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 10, 8)) {
        std::cout << "ACM is supported" << std::endl;
    }
    else {
        std::cout << "ACM is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 11, 8)) {
        std::cout << "BIOS is upgradeable" << std::endl;
    }
    else {
        std::cout << "BIOS is not upgradeable" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 12, 8)) {
        std::cout << "BIOS shadowing is allwoed" << std::endl;
    }
    else {
        std::cout << "BIOS shadowing is not allowed" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 13, 8)) {
        std::cout << "VL-VESA is supported" << std::endl;
    }
    else {
        std::cout << "VL-VESA is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 14, 8)) {
        std::cout << "ESCD support is available" << std::endl;
    }
    else {
        std::cout << "ESCD support is not available" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 15, 8)) {
        std::cout << "Boot from CD is supported" << std::endl;
    }
    else {
        std::cout << "Boot from CD is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 16, 8)) {
        std::cout << "Selectable boot is supported" << std::endl;
    }
    else {
        std::cout << "Selectable boot is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 17, 8)) {
        std::cout << "BIOS ROM is socketed" << std::endl;
    }
    else {
        std::cout << "BIOS ROM is not socketed" << std::endl;
    }
    
    if (get_bit(cur_struct->BIOS_Characteristics, 18, 8)) {
        std::cout << "Boot from PC card (PCMCIA) is supported" << std::endl;
    }
    else {
        std::cout << "Boot from PC card (PCMCIA) is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics, 19, 8)) {
        std::cout << "EDD specification is supported" << std::endl;
    }
    else {
        std::cout << "EDD specification is not supported" << std::endl;
    }
}

// Display BIOS Extended characteristics
void displayBIOSExtendedCharacteristics(SMBIOS_struct_type_0* cur_struct) {
    //char* characteristics = (char*)cur_struct->BIOS_Characteristics_Extensions;
    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 0, 2)) {
        std::cout << "ACPI is supported" << std::endl;
    }
    else {
        std::cout << "ACPI is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 1, 2)) {
        std::cout << "USB Legacy is supported" << std::endl;
    }
    else {
        std::cout << "USB Legacy is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 2, 2)) {
        std::cout << "AGP is supported" << std::endl;
    }
    else {
        std::cout << "AGP is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 3, 2)) {
        std::cout << "I2O Boot is supported" << std::endl;
    }
    else {
        std::cout << "I2O Boot is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 4, 2)) {
        std::cout << "LS-120 SuperDisk boot is supported" << std::endl;
    }
    else {
        std::cout << "LS-120 SuperDisk boot is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 5, 2)) {
        std::cout << "ATAPI ZIP drive boot is supported" << std::endl;
    }
    else {
        std::cout << "ATAPI ZIP drive boot is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 6, 2)) {
        std::cout << "1394 boot is supported" << std::endl;
    }
    else {
        std::cout << "1394 boot is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 7, 2)) {
        std::cout << "Smart battery is supported" << std::endl;
    }
    else {
        std::cout << "Smart battery is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 8, 2)) {
        std::cout << "BIOS Boot specification is supported" << std::endl;
    }
    else {
        std::cout << "BIOS Boot specification is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 9, 2)) {
        std::cout << "Function key-initiated network service is supported" << std::endl;
    }
    else {
        std::cout << "Function key-initiated network service is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 10, 2)) {
        std::cout << "Enabled targeted content distribution" << std::endl;
    }
    else {
        std::cout << "Disabled targeted content distribution" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 11, 2)) {
        std::cout << "UEFI Specification is supported" << std::endl;
    }
    else {
        std::cout << "UEFI Specification is not supported" << std::endl;
    }

    if (get_bit(cur_struct->BIOS_Characteristics_Extensions, 12, 2)) {
        std::cout << "SMBIOS Table describes a virtual machine" << std::endl;
    }
}

// Display System Information (Type 1)
void displayInformation(SMBIOS_struct_type_1* cur_struct, RawSMBIOSData* raw_data) {
    std::vector<std::string> strings = get_strings(cur_struct);
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
    std::cout << "Wake-up Type: " << get_wakeUp_Type(cur_struct) << std::endl;
    
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
std::string get_wakeUp_Type(SMBIOS_struct_type_1* cur_struct) {
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

// Display Baseboard Information (Type 2)
void displayInformation(SMBIOS_struct_type_2* cur_struct, RawSMBIOSData* raw_data) {
    std::vector<std::string> strings = get_strings(cur_struct);
    std::cout << "Baseboard (Type " << (int)cur_struct->Type << ")" << std::endl;

    if (cur_struct->Manufacturer == 0) {
        std::cout << "There is no manufacturer information" << std::endl;
    }
    else {
        std::cout << "Manufacturer: " << strings[cur_struct->Manufacturer] << std::endl;
    }

    if (cur_struct->Product == 0) {
        std::cout << "There is no product information" << std::endl;
    }
    else {
        std::cout << "Product: " << strings[cur_struct->Product] << std::endl;
    }

    if (cur_struct->Version == 0) {
        std::cout << "There is no version information" << std::endl;
    }
    else {
        std::cout << "Version: " << strings[cur_struct->Version] << std::endl;
    }

    if (cur_struct->AssetTag == 0) {
        std::cout << "There is no asset tag information" << std::endl;
    }
    else {
        std::cout << "Asset Tag: " << strings[cur_struct->AssetTag] << std::endl;
    }

    displayFeatureFlags(cur_struct);
    
    if (cur_struct->LocationInChasis == 0) {
        std::cout << "There is no location in chasis information" << std::endl;
    }
    else {
        std::cout << "Location in chasis: " << strings[cur_struct->LocationInChasis] << std::endl;
    }

    std::cout << "Chasis Handle: " << (int)cur_struct->ChassisHandle << std::endl;
    std::cout << "Board Type: " << get_board_type(cur_struct) << std::endl;

    if ((int)cur_struct->NumberOfContainedObjects == 0) {
        std::cout << "--------------------------------------------------------" << std::endl;
        return;
    }

    std::cout << "Contained Objects: " << std::endl;
    char* cur_char = (char*)cur_struct + 15;
    for (int i = 0; i < (int)cur_struct->NumberOfContainedObjects * 4; ++i) {
        std::cout << *cur_char;
        if (i % 4 == 3) {
            std::cout << " ";
        }
        ++cur_char;
    }

    std::cout << "--------------------------------------------------------" << std::endl;
}

// Get the board type value for the struct
std::string get_board_type(SMBIOS_struct_type_2* cur_struct) {
    switch (cur_struct->BoardType) {
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
    }
    return "Other";
}

// Display information about the feature flags
void displayFeatureFlags(SMBIOS_struct_type_2* cur_struct) {
    BYTE flags[100];
    flags[1] = cur_struct->FeatureFlags;
    if (get_bit(flags, 4, 1)) {
        std::cout << "The board is hot swappable" << std::endl;
    }
    else {
        std::cout << "The board is not hot swappable" << std::endl;
    }

    if (get_bit(flags, 3, 1)) {
        std::cout << "The board is replaceable" << std::endl;
    }
    else {
        std::cout << "The board is not replaceable" << std::endl;
    }

    if (get_bit(flags, 2, 1)) {
        std::cout << "The board is removeable" << std::endl;
    }
    else {
        std::cout << "The board is not removeable" << std::endl;
    }

    if (get_bit(flags, 1, 1)) {
        std::cout << "The board requires at least 1 daughter board to function properly" << std::endl;
    }

    if (get_bit(flags, 0, 1)) {
        std::cout << "The board is a hosting baord" << std::endl;
    }
}