// SMBIOS Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <string>
#include "Functions.h"

int main() {
    RawSMBIOSData* smBiosData = getRawData();
    displayAllStructures(smBiosData);
}