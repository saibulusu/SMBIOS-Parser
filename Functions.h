#include "Structures.h"

RawSMBIOSData* get_raw_data();
SMBIOS_struct* get_next_struct(SMBIOS_struct* cur_struct);