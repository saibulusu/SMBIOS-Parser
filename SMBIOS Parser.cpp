// SMBIOS Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <string>
#include "Functions.h"

int main()
{
    RawSMBIOSData* smBiosData = get_raw_data();

    SMBIOS_struct_type_0* struct0 = (SMBIOS_struct_type_0*)smBiosData->SMBIOSTableData;
    displayInformation(struct0, smBiosData);
    SMBIOS_struct_type_1* struct1 = (SMBIOS_struct_type_1*)get_next_struct(struct0);
    displayInformation(struct1, smBiosData);
}