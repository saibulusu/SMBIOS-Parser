#include "Functions.h"

// Type 9 - System Slots 
void displaySystemSlotsInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t SlotDesignation;
  uint8_t SlotType;
  uint8_t SlotDataBusWidth;
  uint8_t CurrentUsage;
  uint8_t SlotLength;
  uint16_t SlotID;
  uint8_t SlotCharacteristics1;

  std::memcpy(&SlotDesignation, bytes + 0x04, sizeof(SlotDesignation));
  std::memcpy(&SlotType, bytes + 0x05, sizeof(SlotType));
  std::memcpy(&SlotDataBusWidth, bytes + 0x06, sizeof(SlotDataBusWidth));
  std::memcpy(&CurrentUsage, bytes + 0x07, sizeof(CurrentUsage));
  std::memcpy(&SlotLength, bytes + 0x08, sizeof(SlotLength));
  std::memcpy(&SlotID, bytes + 0x09, sizeof(SlotID));
  std::memcpy(&SlotCharacteristics1, bytes + 0x0B, sizeof(SlotCharacteristics1));

  std::cout << "\tSlot Designation: " << strings[SlotDesignation] << std::endl;
  std::cout << "\tSlot Type: " << getSlotTypeField(SlotType) << std::endl;
  std::cout << "\tSlot Data Bus Width: " << getSlotDataBusWidth(SlotDataBusWidth) << std::endl;
  std::cout << "\tCurrent Usage: " << getCurrentUsage(CurrentUsage) << std::endl;
  std::cout << "\tSlot Length: " << getSlotLength(SlotLength) << std::endl;
  std::cout << "\tSlot ID: " << (int)SlotID << std::endl;

  displaySlotCharacteristics1(SlotCharacteristics1);

  if (curStruct->Length < 0x0D) return;

  uint8_t SlotCharacteristics2;

  std::memcpy(&SlotCharacteristics2, bytes + 0x0C, sizeof(SlotCharacteristics2)); 
  
  displaySlotCharacteristics2(SlotCharacteristics2);

  if (curStruct->Length < 0x11) return;

  uint16_t SegmentGroupNumber;
  uint8_t BusNumber;
  uint8_t DeviceFunctionNumber;

  std::memcpy(&SegmentGroupNumber, bytes + 0x0D, sizeof(SegmentGroupNumber));
  std::memcpy(&BusNumber, bytes + 0x0F, sizeof(BusNumber));
  std::memcpy(&DeviceFunctionNumber, bytes + 0x10, sizeof(DeviceFunctionNumber));

  std::cout << "\tSegment Group Number: " << (int)SegmentGroupNumber << std::endl;
  std::cout << "\tBus Number: " << (int)BusNumber << std::endl;
  std::cout << "\tDevice/Function Number: " << (int)DeviceFunctionNumber << std::endl;
}

std::string getSlotTypeField(uint8_t SlotType) {
  switch (SlotType) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "ISA";
    case 4: return "MCA";
    case 5: return "EISA";
    case 6: return "PCI";
    case 7: return "PC Card (PCMCIA)";
    case 8: return "VL-VESA";
    case 9: return "Proprietary";
    case 10: return "Processor Card Slot";
    case 11: return "Proprietary Memory Card Slot";
    case 12: return "I/O Riser Card Slot";
    case 13: return "NuBus";
    case 14: return "PCI - 66MHz Capable";
    case 15: return "AGP";
    case 16: return "AGP 2X";
    case 17: return "AGP 4X";
    case 18: return "PCI-X";
    case 19: return "AGP 8X";
    case 20: return "M.2 Socket 1-DP (Mechanical Key A)";
    case 21: return "M.2 Socket 1-SD (Mechanical Key E)";
    case 22: return "M.2 Socket 2 (Mechanical Key B)";
    case 23: return "M.2 Socket 3 (Mechanical Key M)";
    case 24: return "MXM Type I";
    case 25: return "MXM Type II";
    case 26: return "MXM Type III (Standard Connector)";
    case 27: return "MXM Type III (HE Connector)";
    case 28: return "MXM Type IV";
    case 29: return "MXM 3.0 Type A";
    case 30: return "MXM 3.0 Type B";
    case 31: return "PCI Express Gen 2 SFF-8639";
    case 32: return "PCI Express Gen 3 SFF-8639";
    case 160: return "PC-98/C20";
    case 161: return "PC-98/C24";
    case 162: return "PC-98/E";
    case 163: return "PC-98/LocalBus";
    case 164: return "PC-98/Card";
    case 165: return "PCI Express";
    case 166: return "PCI Express x1";
    case 167: return "PCI Express x2";
    case 168: return "PCI Express x4";
    case 169: return "PCI Express x8";
    case 170: return "PCI Express x16";
    case 171: return "PCI Experss Gen 2";
    case 172: return "PCI Express Gen 2 x1";
    case 173: return "PCI Express Gen 2 x2";
    case 174: return "PCI Express Gen 2 x4";
    case 175: return "PCI Express Gen 2 x8";
    case 176: return "PCI Express Gen 2 x16";
    case 177: return "PCI Express Gen 3";
    case 178: return "PCI Express Gen 3 x1";
    case 179: return "PCI Express Gen 3 x2";
    case 180: return "PCI Express Gen 3 x4";
    case 181: return "PCI Express Gen 3 x8";
    case 182: return "PCI Express Gen 3 x16";
    default: return "Other";
  }
}

std::string getSlotDataBusWidth(uint8_t SlotDataBusWidth) {
  switch (SlotDataBusWidth) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "8 bit";
    case 4: return "16 bit";
    case 5: return "32 bit";
    case 6: return "64 bit";
    case 7: return "128 bit";
    case 8: return "1x or x1";
    case 9: return "2x or x2";
    case 10: return "4x or x4";
    case 11: return "8x or x8";
    case 12: return "12x or x12";
    case 13: return "16x or x16";
    case 14: return "32x or x23";
    default: return "Other";
  }
}

std::string getCurrentUsage(uint8_t CurrentUsage) {
  switch (CurrentUsage) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "Available";
    case 4: return "In Use";
    default: return "Other";
  }
}

std::string getSlotLength(uint8_t SlotLength) {
  switch (SlotLength) {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "Short Length";
    case 4: return "Long Length";
    case 5: return "2.5\" drive form factor";
    case 6: return "3.5\" drive form factor";
    default: return "Other";
  }
}

void displaySlotCharacteristics1(uint8_t SlotCharacteristics1) {
  std::cout << "\tSlot Characteristics:" << std::endl;
  if (getBit(SlotCharacteristics1, 1)) {
    std::cout << "\t\tProvides 5.0 Volts" << std::endl;
  }
  if (getBit(SlotCharacteristics1, 2)) {
    std::cout << "\t\tProvides 3.3 Volts" << std::endl;
  }
  if (getBit(SlotCharacteristics1, 3)) {
    std::cout << "\t\tSlot's opening is shared with another slot" << std::endl;
  }
  if (getBit(SlotCharacteristics1, 4)) {
    std::cout << "\t\tPC Card slot supports PC Card-16" << std::endl;
  }
  if (getBit(SlotCharacteristics1, 5)) {
    std::cout << "\t\tPC Card slot supports CardBus" << std::endl;
  }
  if (getBit(SlotCharacteristics1, 6)) {
    std::cout << "\t\tPC Card slot supports Zoom Video" << std::endl;
  }
  if (getBit(SlotCharacteristics1, 7)) {
    std::cout << "\t\tPC Card slot supports Modem Ring Resume" << std::endl;
  }
}

void displaySlotCharacteristics2(uint8_t SlotCharacteristics2) {
  if (getBit(SlotCharacteristics2, 0)) {
    std::cout << "\t\tPCI Slot supports Power Management Event (PME#) Signal" << std::endl;
  }
  if (getBit(SlotCharacteristics2, 1)) {
    std::cout << "\t\tSlot supports hot-plug devices" << std::endl;
  }
  if (getBit(SlotCharacteristics2, 2)) {
    std::cout << "\t\tPCI slot supports SMBus Signal" << std::endl;
  }
}
