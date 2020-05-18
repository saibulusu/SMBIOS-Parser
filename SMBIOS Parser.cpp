// SMBIOS Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <string>
#include "Functions.h"

int main()
{
    RawSMBIOSData* smBiosData = getRawData();

    displayAllStructures(smBiosData);

    //display_hex_contents(smBiosData);

    //SMBIOS_struct_type_0* struct0 = (SMBIOS_struct_type_0*)smBiosData->SMBIOSTableData;
    //displayInformation(struct0, smBiosData);
    //SMBIOS_struct_type_1* struct1 = (SMBIOS_struct_type_1*)get_next_struct(struct0);
    //displayInformation(struct1, smBiosData);
    //SMBIOS_struct_type_2* struct2 = (SMBIOS_struct_type_2*)get_next_struct(struct1);
    //displayInformation(struct2, smBiosData);
}