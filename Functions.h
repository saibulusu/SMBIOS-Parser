#include "Structures.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

RawSMBIOSData* get_raw_data();
void display_hex_contents(RawSMBIOSData* raw_data);
std::vector<SMBIOS_struct*> get_structure_table(RawSMBIOSData* raw_data);
void displayAllStructures(RawSMBIOSData* raw_data);
SMBIOS_struct* get_next_struct(SMBIOS_struct* cur_struct);
std::vector<std::string> get_strings(SMBIOS_struct* cur_struct);
void displayBIOSCharacteristics(SMBIOS_struct_type_0* cur_struct);
void displayBIOSExtendedCharacteristics(SMBIOS_struct_type_0* cur_struct);
int get_bit(BYTE characteristics[], int bit_num, int num_bits);
void displayInformation(SMBIOS_struct_non_required* cur_struct);
std::string get_wakeUp_Type(SMBIOS_struct_type_1* cur_struct);
void displayChassisType(SMBIOS_struct_type_3* cur_struct);
std::string get_Chassis_State(BYTE field);
std::string get_Chassis_Security_State(BYTE field);
std::string getProcessorType(SMBIOS_struct_type_4* cur_struct);
std::string getProcessorFamily(SMBIOS_struct_type_4* cur_struct);
std::string getVoltage(SMBIOS_struct_type_4* cur_struct);
std::string getProcessorStatus(SMBIOS_struct_type_4* cur_struct);
std::string getProcessorUpgrade(SMBIOS_struct_type_4* cur_struct);
void displayInformation(SMBIOS_struct_type_0* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_1* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_3* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_4* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_7* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_9* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_16* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_17* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_19* cur_struct, RawSMBIOSData* raw_data);
void displayInformation(SMBIOS_struct_type_32* cur_struct, RawSMBIOSData* raw_data);