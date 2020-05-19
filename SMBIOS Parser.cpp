// SMBIOS Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <string>
#include "Functions.h"

int main() {
    RawSMBIOSData* smBiosData = getRawData();

    std::string input;
    displayCommands();
    while (std::cin >> input) {
        if (input.compare("show") == 0) {
            std::cin >> input;
            if (input.compare("all") == 0) {
                displayAllStructures(smBiosData);
            }
            else if (input.compare("table") == 0) {
                displayStructureTable(smBiosData);
            }
            else if (input.compare("structure") == 0) {
                int index;
                std::cin >> index;
                std::vector<SMBIOS_struct*> structureTable = getStructureTable(smBiosData);
                if (index >= structureTable.size()) {
                    std::cout << "structure table size is " << structureTable.size() << std::endl;
                    error();
                }
                else {
                    displayStructure(smBiosData, index);
                }
            }
            else if (input.compare("commands") == 0) {
                displayCommands();
            }
            else {
                error();
            }
        }
        else if (input.compare("hex") == 0) {
            std::cin >> input;
            if (input.compare("contents") == 0) {
                displayHexContents(smBiosData);
            }
            else {
                error();
            }
        }
        else if (input.compare("quit") == 0) {
            return 0;
        }
        else {
            error();
        }
    }
    return 0;
}

void error() {
    std::cout << "Please enter a valid command" << std::endl;
}

void displayCommands() {
    std::cout << "show commands - display all legal commands" << std::endl;
    std::cout << "show all - display all structures" << std::endl;
    std::cout << "show table - display the structure table" << std::endl;
    std::cout << "show structure <id> - display a specific structure" << std::endl;
    std::cout << "hex contents - display raw table as hex bytes" << std::endl;
    std::cout << "quit - exit the program" << std::endl;
}