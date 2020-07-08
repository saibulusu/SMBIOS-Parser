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
struct SMBIOSStruct {
    BYTE    Type;
    BYTE    Length;
    WORD    Handle;
};

/** Non-necessary structure */
struct SMBIOSStructNonRequired : SMBIOSStruct {

};

/** Necessary structure of type 0 */
struct SMBIOSStructType0 : SMBIOSStruct {
    BYTE    Vendor;
    BYTE    BIOSVersion;
    WORD    BIOSStartingAddressSegment;
    BYTE    BIOSReleaseDate;
    BYTE    BIOSROMSize;
    BYTE    BIOSCharacteristics[8];
    BYTE    BIOSCharacteristicsExtensions[2];
    BYTE    SystemBIOSMajorRelease;
    BYTE    SystemBIOSMinorRelease;
    BYTE    ECFirmwareMajorRelease;
    BYTE    ECFirmwareMinorRelease;
};

/** Necessary structure of type 1 */
struct SMBIOSStructType1 : SMBIOSStruct {
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
struct SMBIOSStructType2 : SMBIOSStruct {
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
struct SMBIOSStructType3 : SMBIOSStruct {
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
struct SMBIOSStructType4 : SMBIOSStruct {
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
struct SMBIOSStructType5 : SMBIOSStruct {
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
struct SMBIOSStructType6 : SMBIOSStruct {
    BYTE    SocketDesignation;
    BYTE    BankConnections;
    BYTE    CurrentSpeed;
    WORD    CurrentMemoryType;
    BYTE    InstalledSize;
    BYTE    EnabledSize;
    BYTE    ErrorStatus;
};

/** Necessary structure of type 7 */
struct SMBIOSStructType7 : SMBIOSStruct {
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
struct SMBIOSStructType8 : SMBIOSStruct {
    BYTE    InternalReferenceDesignator;
    BYTE    InternalConnectorType;
    BYTE    ExternalReferenceDesignator;
    BYTE    ExternalConnectorType;
    BYTE    PortType;
};

/** Necessary structure of type 9 */
struct SMBIOSStructType9 : SMBIOSStruct {
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
struct SMBIOSStructType10 : SMBIOSStruct {
    BYTE    DeviceType;
    BYTE    DescriptionString;
};

/** Structure of type 11 */
struct SMBIOSStructType11 : SMBIOSStruct {
    BYTE    Count;
};

/** Structure of type 12 */
struct SMBIOSStructType12 : SMBIOSStruct {
    BYTE    Count;
};

/** Structure of type 13 */
struct SMBIOSStructType13 : SMBIOSStruct {
    BYTE    InstalledLanguages;
    BYTE    Flags;
    BYTE    Reserved[15];
    BYTE    CurrentLanguage;
};

/** Structure of type 14 */
struct SMBIOSStructType14 : SMBIOSStruct {
    BYTE    GroupName;
    BYTE    ItemType;
    WORD    ItemHandle;
};

/** Structure of type 15 */
struct SMBIOSStructType15 : SMBIOSStruct {
    WORD    LogAreaLength;
    WORD    LogHeaderStartOffset;
    WORD    LogDataStartOffset;
    BYTE    AccessMethod;
    BYTE    LogStatus;
    WORD    LogChangeToken[2];
    WORD    AccessMethodAddress[2];
    BYTE    LogHeaderFormat;
    BYTE    NumberOfSupportedLogTypeDescriptors;
    BYTE    LengthOfEachLogTypeDescriptor;
};

/** Necessary structure of type 16 */
struct SMBIOSStructType16 : SMBIOSStruct {
    BYTE    Location;
    BYTE    Use;
    BYTE    MemoryErrorCorrection;
    BYTE    MaximumCapacity[4];
    WORD    MemoryErrorInformationHandle;
    WORD    NumberOfMemoryDevices;
    BYTE    ExtendedMaximumCapacity[8];
};

/** Necessary structure of type 17 */
struct SMBIOSStructType17 : SMBIOSStruct {
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
struct SMBIOSStructType19 : SMBIOSStruct {
    BYTE    StartingAddress[4];
    BYTE    EndingAddress[4];
    WORD    MemoryArrayHandle;
    BYTE    PartitionWidth;
    BYTE    ExtendedStartingAddress[8];
    BYTE    ExtendedEndingAddress[8];
};

/** Necessary structure of type 32 */
struct SMBIOSStructType32 : SMBIOSStruct {
    BYTE    Reserved[6];
    BYTE    BootStatus[10];
};