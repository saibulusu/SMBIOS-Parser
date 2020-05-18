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
struct SMBIOS_struct_type_2 : SMBIOS_struct {
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
};

// Necessary structure of type 3
struct SMBIOS_struct_type_3 : SMBIOS_struct {
    WORD    Handle;
    BYTE    Manufacturer;
    BYTE    ChassisType;
    BYTE    Version;
    BYTE    SerialNumber;
    BYTE    AssetTagNumber;
    BYTE    BootUpState;
    BYTE    PowerSupplyState;
    BYTE    ThermalState;
    BYTE    SecurityStatus;
    BYTE    OEMDefined[4];
    BYTE    Height;
    BYTE    NumberOfPowerCords;
    BYTE    ContainedElementCount;
    BYTE    ContainedElementRecordLength;
    BYTE    ContainedElements[65537];
};

// Necessary structure of type 4
struct SMBIOS_struct_type_4 : SMBIOS_struct {
    WORD    Handle;
    BYTE    SocketDesignation;
    BYTE    ProcessorType;
    BYTE    ProcessorFamily;
    BYTE    ProcessorManufacturer;
    BYTE    ProcessorID;
    BYTE    ProcessorVersion;
    BYTE    Voltage;
    WORD    ExternalClock;
    WORD    MaxSpeed;
    WORD    CurrentSpeed;
    BYTE    Status;
    BYTE    ProcessorUpgrade;
    WORD    L1CacheHandle;
    WORD    L2CacheHandle;
    WORD    L3CacheHandle;
    BYTE    SerialNumber;
    BYTE    AssetTag;
    BYTE    PartNumber;
    BYTE    CoreCount;
    BYTE    CoreEnabled;
    BYTE    ThreadCount;
    WORD    ProcessorCharacteristics;
    WORD    ProcessorFamily2;
    WORD    CoreCount2;
    WORD    CoreEnabled2;
    WORD    ThreadCount2;
};