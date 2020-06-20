#include <Windows.h>

/** The entire SMBIOS table with metadata */
struct RawSMBIOSData {
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
    DWORD   Length;
    BYTE    SMBIOSTableData[];
};

/** Generic structure */
struct SMBIOS_struct {
    BYTE    Type;
    BYTE    Length;
    WORD    Handle;
};

/** Non-necessary structure */
struct SMBIOS_struct_non_required : SMBIOS_struct {

};

/** Necessary structure of type 0 */
struct SMBIOS_struct_type_0 : SMBIOS_struct {
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

/** Necessary structure of type 1 */
struct SMBIOS_struct_type_1 : SMBIOS_struct {
    BYTE    Manufacturer;
    BYTE    ProductName;
    BYTE    Version;
    BYTE    SerialNumber;
    BYTE    UUID[16];
    BYTE    WakeUpType;
    BYTE    SKUNumber;
    BYTE    Family;
};

/** Structure of type 2 */
struct SMBIOS_struct_type_2 : SMBIOS_struct {
    BYTE    Manufacturer;
    BYTE    Product;
    BYTE    Version;
    BYTE    SerialNumber;
    BYTE    AssetTag;
    BYTE    FeatureFlags;
    BYTE    LocationInChassis;
    WORD    ChassisHandle;
    BYTE    BoardType;
    BYTE    NumberOfContainedObjectHandles;
    BYTE    ContainedObjectHandles[256];
};

/** Necessary structure of type 3 */
struct SMBIOS_struct_type_3 : SMBIOS_struct {
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

/** Necessary structure of type 4 */
struct SMBIOS_struct_type_4 : SMBIOS_struct {
    BYTE    SocketDesignation;
    BYTE    ProcessorType;
    BYTE    ProcessorFamily;
    BYTE    ProcessorManufacturer;
    BYTE    ProcessorID[8];
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

/** Structure of type 5 */
struct SMBIOS_struct_type_5 : SMBIOS_struct {
    BYTE    ErrorDetectingMethod;
    BYTE    ErrorCorrectingCapability;
    BYTE    SupportedInterleave;
    BYTE    CurrentInterleave;
    BYTE    MaximumMemoryModuleSize;
    WORD    SupportedSpeeds;
    WORD    SupportedMemoryTypes;
    BYTE    MemoryModuleVoltage;
    BYTE    NumberOfAssociatedMemorySlots;
};

/** Structure of type 6 */
struct SMBIOS_struct_type_6 : SMBIOS_struct {
    BYTE    SocketDesignation;
    BYTE    BankConnections;
    BYTE    CurrentSpeed;
    WORD    CurrentMemoryType;
    BYTE    InstalledSize;
    BYTE    EnabledSize;
    BYTE    ErrorStatus;
};

/** Necessary structure of type 7 */
struct SMBIOS_struct_type_7 : SMBIOS_struct {
    BYTE    SocketDesignation;
    WORD    CacheConfiguration;
    WORD    MaximumCacheSize;
    WORD    InstalledSize;
    WORD    SupportedSRAMType;
    WORD    CurrentSRAMType;
    BYTE    CacheSpeed;
    BYTE    ErrorCorrectionType;
    BYTE    SystemCachetype;
    BYTE    Associativity;
};

/** Structure of type 8 */
struct SMBIOS_struct_type_8 : SMBIOS_struct {
    BYTE    InternalReferenceDesignator;
    BYTE    InternalConnectorType;
    BYTE    ExternalReferenceDesignator;
    BYTE    ExternalConnectorType;
    BYTE    PortType;
};

/** Necessary structure of type 9 */
struct SMBIOS_struct_type_9 : SMBIOS_struct {
    BYTE    SlotDesignation;
    BYTE    SlotType;
    BYTE    SlotDataBusWidth;
    BYTE    CurrentUsage;
    BYTE    SlotLength;
    WORD    SlotID;
    BYTE    SlotCharacteristics1;
    BYTE    SlotCharacteristics2;
    WORD    SegmentGroupNumber;
    BYTE    BusNumber;
    BYTE    DeviceNumber;
};

/** Structure of type 10 */
struct SMBIOS_struct_type_10 : SMBIOS_struct {
    BYTE    DeviceType;
    BYTE    DescriptionString;
};

/** Structure of type 11 */
struct SMBIOS_struct_type_11 : SMBIOS_struct {
    BYTE    Count;
};

struct SMBIOS_struct_type_12 : SMBIOS_struct {
    BYTE    Count;
};

/** Necessary structure of type 16 */
struct SMBIOS_struct_type_16 : SMBIOS_struct {
    BYTE    Location;
    BYTE    Use;
    BYTE    MemoryErrorCorrection;
    BYTE    MaximumCapacity[4];
    WORD    MemoryErrorInformationHandle;
    WORD    NumberOfMemoryDevices;
    BYTE    ExtendedMaximumCapacity[8];
};

/** Necessary structure of type 17 */
struct SMBIOS_struct_type_17 : SMBIOS_struct {
    WORD    PhysicalMemoryArrayHandle;
    WORD    MemoryErrorInformationHandle;
    WORD    TotalWidth;
    WORD    DataWidth;
    WORD    Size;
    BYTE    FormFactor;
    BYTE    DeviceSet;
    BYTE    DeviceLocator;
    BYTE    BankLocator;
    BYTE    MemoryType;
    WORD    TypeDetail;
    WORD    Speed;
    BYTE    Manufacturer;
    BYTE    SerialNumber;
    BYTE    AssetTag;
    BYTE    PartNumber;
    BYTE    Attributes;
    BYTE    ExtendedSize[4];
    WORD    ConfiguredMemoryClockSpeed;
    WORD    MinimumVoltage;
    WORD    MaximumVoltage;
    WORD    ConfiguredVoltage;
};

/** Necessary structure of type 19 */
struct SMBIOS_struct_type_19 : SMBIOS_struct {
    BYTE    StartingAddress[4];
    BYTE    EndingAddress[4];
    WORD    MemoryArrayHandle;
    BYTE    PartitionWidth;
    BYTE    ExtendedStartingAddress[8];
    BYTE    ExtendedEndingAddress[8];
};

/** Necessary structure of type 32 */
struct SMBIOS_struct_type_32 : SMBIOS_struct {
    BYTE    Reserved[6];
    BYTE    BootStatus[10];
};