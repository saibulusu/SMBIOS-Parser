// SMBIOS Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Functions.h"

int main()
{
    RawSMBIOSData* smBiosData = get_raw_data();

    for (int i = 0; i < smBiosData->Length; ++i) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)smBiosData->SMBIOSTableData[i] << " ";
        if (i % 32 == 31) {
            std::cout << std::endl;
         }
    }
    std::cout << std::dec << std::endl;

    SMBIOS_struct_type_0* struct0 = (SMBIOS_struct_type_0*)smBiosData->SMBIOSTableData;
    std::cout << "Type: " << (int)struct0->Type << std::endl;
    std::cout << "Length: " << (int)struct0->Length << std::endl;
    std::cout << "Handle: " << (int)struct0->Handle << std::endl;
    std::cout << "Vendor: " << struct0->Vendor << std::endl;
    std::cout << "BIOS Version: " << struct0->BIOS_Version << std::endl;

    SMBIOS_struct* struct1 = get_next_struct(struct0);
    //std::cout << "Type: " << (int)struct1->Type << std::endl;
    //std::cout << "Length: " << (int)struct1->Length << std::endl;

    while ((char*)struct1 < (char*)smBiosData->SMBIOSTableData + smBiosData->Length) {
        std::cout << "Type: " << (int)struct1->Type << std::endl;
        std::cout << "Length: " << (int)struct1->Length << std::endl;
        struct1 = get_next_struct(struct1);
    }
}