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

// Generic structure
struct SMBIOS_struct {
    BYTE    Type;
    BYTE    Length;
};

// Non-necessary structure
struct SMBIOS_struct_non_required : SMBIOS_struct {

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

// Necessary structure of type 1
struct SMBIOS_struct_type_1 : SMBIOS_struct {
    WORD    Handle;
    BYTE    Manufacturer;
    BYTE    ProductName;
    BYTE    Version;
    BYTE    SerialNumber;
    BYTE    UUID[16];
    BYTE    WakeUpType;
    BYTE    SKUNumber;
    BYTE    Family;
};

// Necessary structure of type 2
struct SMBIOS_struct_type_2 {
    WORD    Handle;
    BYTE    Manufacturer;
    BYTE    Product;
    BYTE    Version;
    BYTE    SerialNumber;
    BYTE    AssetTag;
    BYTE    FeatureFlags;
    BYTE    LocationInChasis;
    WORD    ChassisHandle;
    BYTE    BoardType;
    BYTE    NumberOfContainedObjects;
    BYTE    ContainedObjectHandles;
};