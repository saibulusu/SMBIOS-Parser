#pragma once
#include <cstdint>

struct SMBIOSStruct {
  uint8_t Type;
  uint8_t Length;
  uint16_t Handle;
};

class SMBIOSStructure {
public:
  explicit SMBIOSStructure(const SMBIOSStruct* h)
    : header(h) {}
  virtual ~SMBIOSStructure() = default;

  uint8_t  type()   const { return header->Type; }
  uint16_t handle() const { return header->Handle; }

protected:
  const SMBIOSStruct* header;
};
