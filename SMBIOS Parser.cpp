// SMBIOS Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <string>
#include "Functions.h"

int main() {
    RawSMBIOSData* rawData = getRawData();

    displayStructureTable(rawData);
    std::cout << std::endl;
    displayAllStructures(rawData);

    return 0;
}