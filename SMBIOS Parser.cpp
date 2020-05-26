// SMBIOS Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <string>
#include "Functions.h"

void displayCommands() {
    std::cout << "cmds: Display available commands" << std::endl;
    std::cout << "all: Display all structures" << std::endl;
    std::cout << "table: Display structure table" << std::endl;
    std::cout << "hex: Display the SMBIOS table bytes in hex" << std::endl;
    std::cout << "<id>: Display the structure with the given ID" << std::endl;
    std::cout << "quit: Exit the program" << std::endl;
}

int main() {
    RawSMBIOSData* rawData = getRawData();

    std::cout << "> ";
    std::string input;
    while (std::cin >> input) {
        if (input.compare("quit") == 0) {
            return 0;
        }
        else if (input.compare("hex") == 0) {
            displayHexContents(rawData);
        }
        else if (input.compare("all") == 0) {
            displayAllStructures(rawData);
        }
        else if (input.compare("table") == 0) {
            displayStructureTable(rawData);
        }
        else if (input.compare("cmds") == 0) {
            displayCommands();
        }
        else {
            try {
                int index = std::stoi(input);
                if (index < 0 || index >= getStructureTable(rawData).size()) {
                    std::cout << "ERROR: Out of bounds" << std::endl;
                }
                else {
                    displayStructure(rawData, index);
                }
            }
            catch (std::exception& e) {
                std::cout << "ERROR: Invalid command" << std::endl;
            }
        }
        
        std::cout << "> ";
    }

    return 0;
}