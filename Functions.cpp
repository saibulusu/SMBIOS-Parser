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
    char* cur_char = (char*)cur_struct + cur_struct->Length;
    SMBIOS_struct* next_struct = get_next_struct(cur_struct);

    std::vector<std::string> strings;
    std::string res = "";
    strings.push_back(res);
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

// Display the System BIOS Information (Type 0)
void displayInformation(SMBIOS_struct_type_0* cur_struct, RawSMBIOSData* raw_data) {
    if ((int)raw_data->SMBIOSMajorVersion < 2) {
        return;
    }
    std::vector<std::string> strings = get_strings(cur_struct);
    std::cout << "SMBIOS Information (Type " << (int)cur_struct->Type << ")" << std::endl;
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
        return;
    }
    displayBIOSExtendedCharacteristics(cur_struct);
    std::cout << "Embedded Controller Firmware Major Release: " << (int)cur_struct->EC_Firmware_Major_Release << std::endl;
    std::cout << "Embedded Controller Firmware Minor Release: " << (int)cur_struct->EC_Firmware_Minor_Release << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

// Get a specific bit from the characteristics bits
int get_bit(char* characteristics, int bit_num, int num_bytes){
    characteristics += (bit_num / num_bytes);
    bit_num = 7 - bit_num;
    return *characteristics & (1 << bit_num);
}

// Display BIOS Characteristics
void displayBIOSCharacteristics(SMBIOS_struct_type_0* cur_struct) {
    char* characteristics = (char*)cur_struct->BIOS_Characteristics;
    if (get_bit(characteristics, 3, 8)) {
        std::cout << "BIOS Characteristics are not supported" << std::endl;
    }
    else {
        std::cout << "BIOS Characteristics are supported" << std::endl;
    }

    if (get_bit(characteristics, 4, 8)) {
        std::cout << "ISA is supported" << std::endl;
    }
    else {
        std::cout << "ISA is not supported" << std::endl;
    }

    if (get_bit(characteristics, 5, 8)) {
        std::cout << "MCA is supported" << std::endl;
    }
    else {
        std::cout << "MCA is not supported" << std::endl;
    }

    if (get_bit(characteristics, 6, 8)) {
        std::cout << "EISA is supported" << std::endl;
    }
    else {
        std::cout << "EISA is not supported" << std::endl;
    }

    if (get_bit(characteristics, 7, 8)) {
        std::cout << "PCI is supported" << std::endl;
    }
    else {
        std::cout << "PCI is not supported" << std::endl;
    }

    if (get_bit(characteristics, 8, 8)) {
        std::cout << "PC card (PCMCIA) is supported" << std::endl;
    }
    else {
        std::cout << "PC card (PCMCIA) is not supported" << std::endl;
    }

    if (get_bit(characteristics, 9, 8)) {
        std::cout << "Plug and Play is supported" << std::endl;
    }
    else {
        std::cout << "Plug and Play is not supported" << std::endl;
    }

    if (get_bit(characteristics, 10, 8)) {
        std::cout << "ACM is supported" << std::endl;
    }
    else {
        std::cout << "ACM is not supported" << std::endl;
    }

    if (get_bit(characteristics, 11, 8)) {
        std::cout << "BIOS is upgradeable" << std::endl;
    }
    else {
        std::cout << "BIOS is not upgradeable" << std::endl;
    }

    if (get_bit(characteristics, 12, 8)) {
        std::cout << "BIOS shadowing is allwoed" << std::endl;
    }
    else {
        std::cout << "BIOS shadowing is not allowed" << std::endl;
    }

    if (get_bit(characteristics, 13, 8)) {
        std::cout << "VL-VESA is supported" << std::endl;
    }
    else {
        std::cout << "VL-VESA is not supported" << std::endl;
    }

    if (get_bit(characteristics, 14, 8)) {
        std::cout << "ESCD support is available" << std::endl;
    }
    else {
        std::cout << "ESCD support is not available" << std::endl;
    }

    if (get_bit(characteristics, 15, 8)) {
        std::cout << "Boot from CD is supported" << std::endl;
    }
    else {
        std::cout << "Boot from CD is not supported" << std::endl;
    }

    if (get_bit(characteristics, 16, 8)) {
        std::cout << "Selectable boot is supported" << std::endl;
    }
    else {
        std::cout << "Selectable boot is not supported" << std::endl;
    }

    if (get_bit(characteristics, 17, 8)) {
        std::cout << "BIOS ROM is socketed" << std::endl;
    }
    else {
        std::cout << "BIOS ROM is not socketed" << std::endl;
    }
    
    if (get_bit(characteristics, 18, 8)) {
        std::cout << "Boot from PC card (PCMCIA) is supported" << std::endl;
    }
    else {
        std::cout << "Boot from PC card (PCMCIA) is not supported" << std::endl;
    }

    if (get_bit(characteristics, 19, 8)) {
        std::cout << "EDD specification is supported" << std::endl;
    }
    else {
        std::cout << "EDD specification is not supported" << std::endl;
    }
}

// Display BIOS Extended characteristics
void displayBIOSExtendedCharacteristics(SMBIOS_struct_type_0* cur_struct) {
    char* characteristics = (char*)cur_struct->BIOS_Characteristics_Extensions;
    if (get_bit(characteristics, 0, 2)) {
        std::cout << "ACPI is supported" << std::endl;
    }
    else {
        std::cout << "ACPI is not supported" << std::endl;
    }

    if (get_bit(characteristics, 1, 2)) {
        std::cout << "USB Legacy is supported" << std::endl;
    }
    else {
        std::cout << "USB Legacy is not supported" << std::endl;
    }

    if (get_bit(characteristics, 2, 2)) {
        std::cout << "AGP is supported" << std::endl;
    }
    else {
        std::cout << "AGP is not supported" << std::endl;
    }

    if (get_bit(characteristics, 3, 2)) {
        std::cout << "I2O Boot is supported" << std::endl;
    }
    else {
        std::cout << "I2O Boot is not supported" << std::endl;
    }

    if (get_bit(characteristics, 4, 2)) {
        std::cout << "LS-120 SuperDisk boot is supported" << std::endl;
    }
    else {
        std::cout << "LS-120 SuperDisk boot is not supported" << std::endl;
    }

    if (get_bit(characteristics, 5, 2)) {
        std::cout << "ATAPI ZIP drive boot is supported" << std::endl;
    }
    else {
        std::cout << "ATAPI ZIP drive boot is not supported" << std::endl;
    }

    if (get_bit(characteristics, 6, 2)) {
        std::cout << "1394 boot is supported" << std::endl;
    }
    else {
        std::cout << "1394 boot is not supported" << std::endl;
    }

    if (get_bit(characteristics, 7, 2)) {
        std::cout << "Smart battery is supported" << std::endl;
    }
    else {
        std::cout << "Smart battery is not supported" << std::endl;
    }

    if (get_bit(characteristics, 8, 2)) {
        std::cout << "BIOS Boot specification is supported" << std::endl;
    }
    else {
        std::cout << "BIOS Boot specification is not supported" << std::endl;
    }

    if (get_bit(characteristics, 9, 2)) {
        std::cout << "Function key-initiated network service is supported" << std::endl;
    }
    else {
        std::cout << "Function key-initiated network service is not supported" << std::endl;
    }

    if (get_bit(characteristics, 10, 2)) {
        std::cout << "Enabled targeted content distribution" << std::endl;
    }
    else {
        std::cout << "Disabled targeted content distribution" << std::endl;
    }

    if (get_bit(characteristics, 11, 2)) {
        std::cout << "UEFI Specification is supported" << std::endl;
    }
    else {
        std::cout << "UEFI Specification is not supported" << std::endl;
    }

    if (get_bit(characteristics, 12, 2)) {
        std::cout << "SMBIOS Table describes a virtual machine" << std::endl;
    }
}