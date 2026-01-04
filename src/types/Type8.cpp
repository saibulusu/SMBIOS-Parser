#include "Functions.h"

// Type 8 - Port Connector 
void displayPortConnectorInformation(const SMBIOSStruct* curStruct) {
  std::cout << getTypeName(curStruct->Type) << " Information (Type " << (int)curStruct->Type << ")" << std::endl;
  std::cout << "\tHandle: " << curStruct->Handle << std::endl;

  std::vector<std::string> strings = getStrings(curStruct);
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(curStruct);

  uint8_t InternalReferenceDesignator;
  uint8_t InternalConnectorType;
  uint8_t ExternalReferenceDesignator;
  uint8_t ExternalConnectorType;
  uint8_t PortType;

  std::memcpy(&InternalReferenceDesignator, bytes + 0x04, sizeof(InternalReferenceDesignator));
  std::memcpy(&InternalConnectorType, bytes + 0x05, sizeof(InternalConnectorType));
  std::memcpy(&ExternalReferenceDesignator, bytes + 0x06, sizeof(ExternalReferenceDesignator));
  std::memcpy(&ExternalConnectorType, bytes + 0x07, sizeof(ExternalConnectorType));
  std::memcpy(&PortType, bytes + 0x08, sizeof(PortType));

  std::cout << "\tInternal Reference Designator: " << strings[InternalReferenceDesignator] << std::endl;
  std::cout << "\tInternal Connector Type: " << getConnectorType(InternalConnectorType) << std::endl;
  std::cout << "\tExternal Reference Designator: " << strings[ExternalReferenceDesignator] << std::endl;
  std::cout << "\tExternal Connector Type: " << getConnectorType(ExternalConnectorType) << std::endl;
  std::cout << "\tPort Type: " << getPortType(PortType) << std::endl;
}

std::string getConnectorType(uint8_t connector) {
  switch (connector) {
    case 0: return "None";
    case 1: return "Centronics";
    case 2: return "Mini Centronics";
    case 3: return "Proprietary";
    case 4: return "DB-25 pin male";
    case 5: return "DB-25 pin female";
    case 6: return "DB-15 pin male";
    case 7: return "DB-15 pin female";
    case 8: return "DB-9 pin male";
    case 9: return "DB-9 pin female";
    case 10: return "RJ-11";
    case 11: return "RJ-45";
    case 12: return "50-pin MiniSCSI";
    case 13: return "Mini-DIN";
    case 14: return "Micro-DIN";
    case 15: return "PS/2";
    case 16: return "Infrared";
    case 17: return "HP-HIL";
    case 18: return "Access Bus (USB)";
    case 19: return "SSA SCSI";
    case 20: return "Circular DIN-8 Male";
    case 21: return "Circular DIN-8 Female";
    case 22: return "On Board IDE";
    case 23: return "On Board Floppy";
    case 24: return "9-pin Dual Inline (pin 10 cut)";
    case 25: return "25-pin Dual Inline (pin 26 cut)";
    case 26: return "50-pin Dual Inline";
    case 27: return "68-pin Dual Inline";
    case 28: return "On Board Sound Input from CD-Rom";
    case 29: return "Mini-Centronics Type-14";
    case 30: return "Mini-Centronics Type-26";
    case 31: return "Mini-jack (headphones)";
    case 32: return "BNC";
    case 33: return "1394";
    case 34: return "SAS/SATA Plug Receptable";
    case 160: return "PC-98";
    case 161: return "PC-98Hireso";
    case 162: return "PC-H98";
    case 163: return "PC-98Note";
    case 164: return "PC-98Full";
    default: return "Other";
  }
}

std::string getPortType(uint8_t PortType) {
  switch (PortType) {
    case 0: return "None";
    case 1: return "Parallel Port XT/AT Compatible";
    case 2: return "Parallel Port PS/2";
    case 3: return "Parallel Port ECP";
    case 4: return "Parallel Port EPP";
    case 5: return "Parallel Port ECP/EPP";
    case 6: return "Serial Port XT/AT Compatible";
    case 7: return "Serial Port 16450 Compatible";
    case 8: return "Serial Port 16550 Compatible";
    case 9: return "Serial Port 16550A Compatible";
    case 10: return "SCSI Port";
    case 11: return "MIDI Port";
    case 12: return "Joy Stick Port";
    case 13: return "Keyboard Port";
    case 14: return "Mouse Port";
    case 15: return "SSA SCSI";
    case 16: return "USB";
    case 17: return "FireWire (IEEE 1394)";
    case 18: return "PCMCIA Type I2";
    case 19: return "PCMCIA Type II";
    case 20: return "PCMCIA Type III";
    case 21: return "Cardbus";
    case 22: return "Access Bus Port";
    case 23: return "SCSI II";
    case 24: return "SCSI Wide";
    case 25: return "PC-98";
    case 26: return "PC-98-Hireso";
    case 27: return "PC-H98";
    case 28: return "Video Port";
    case 29: return "Audio Port";
    case 30: return "Modem Port";
    case 31: return "Network Port";
    case 32: return "SATA";
    case 33: return "SAS";
    case 160: return "8251 Compatible";
    case 161: return "8251 FIFO Compatible";
    default: return "Other";
  }
}  
