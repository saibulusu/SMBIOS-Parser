#include "Structures.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

RawSMBIOSData* get_raw_data();
SMBIOS_struct* get_next_struct(SMBIOS_struct* cur_struct);
std::vector<std::string> get_strings(SMBIOS_struct* cur_struct);
void displayBIOSCharacteristics(SMBIOS_struct_type_0* cur_struct);
void displayBIOSExtendedCharacteristics(SMBIOS_struct_type_0* cur_struct);
int get_bit(char* characteristics, int bit_num, int num_bits);
void displayInformation(SMBIOS_struct_non_required* cur_struct);
std::string get_wakeUp_Type(SMBIOS_struct_type_1* cur_struct);
void displayInformation(SMBIOS_struct_type_0* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_1* cur_struct, RawSMBIOSData* raw_data);