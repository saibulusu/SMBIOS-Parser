#pragma once
#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>

class SMBIOSData {
public:
  static SMBIOSData fromLinux();
  static SMBIOSData fromWindows();

  const uint8_t* data() const;
  uint32_t getLength() const;

private:
  uint32_t length;
  std::vector<uint8_t> table;
};
