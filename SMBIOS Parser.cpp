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
    displayInformation(struct0, smBiosData);
}