#include <Windows.h>

// The entire SMBIOS table
struct RawSMBIOSData {
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
    DWORD   Length;
    BYTE    SMBIOSTableData[];
};

// Non-necessary structure
struct SMBIOS_struct {
    BYTE    Type;
    BYTE    Length;
};

// Necessary structure of type 0
struct SMBIOS_struct_type_0 : SMBIOS_struct {
    WORD    Handle;
    BYTE    Vendor;
    BYTE    BIOS_Version;
    WORD    BIOS_Starting_Address_Segment;
    BYTE    Bios_Release_Date;
    BYTE    BIOS_ROM_Size;
    BYTE    BIOS_Characteristics[8];
    BYTE    BIOS_Characteristics_Extensions[2];
    BYTE    System_BIOS_Major_Release;
    BYTE    System_BIOS_Minor_Release;
    BYTE    EC_Firmware_Major_Release;
    BYTE    EC_Firmware_Minor_Release;
};