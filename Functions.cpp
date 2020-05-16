#include "Functions.h"

// Get the raw SMBIOS table
RawSMBIOSData* get_raw_data() {
    DWORD error = ERROR_SUCCESS;
    DWORD smBiosDataSize = 0;
    RawSMBIOSData* smBiosData = NULL;
    DWORD bytesWritten = 0;

    // Make sure that there is enough space in the heap for this table
    smBiosDataSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
    smBiosData = (RawSMBIOSData*)HeapAlloc(GetProcessHeap(), 0, smBiosDataSize);
    if (!smBiosData) {
        error = ERROR_OUTOFMEMORY;
        exit(1);
    }

    // Make sure that the data used is valid (by checking the amount of data received)
    bytesWritten = GetSystemFirmwareTable('RSMB', 0, smBiosData, smBiosDataSize);
    if (bytesWritten != smBiosDataSize) {
        error = ERROR_INVALID_DATA;
        exit(1);
    }

    return smBiosData;
}

// Get the next SMBIOS struct after the current one
SMBIOS_struct* get_next_struct(SMBIOS_struct* cur_struct) {
	char* strings_begin = (char*)cur_struct + cur_struct->Length;
	char* next_strings = strings_begin + 1;
	while (*strings_begin != NULL || *next_strings != NULL) {
		++strings_begin;
		++next_strings;
	}
	return (SMBIOS_struct*)(next_strings + 1);
}