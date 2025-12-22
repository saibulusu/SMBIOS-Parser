#include "SMBIOSPlatform.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

SMBIOSData* loadSMBIOSFromLinux() {
  const char* path = "/sys/firmware/dmi/tables/DMI";

  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    throw std::runtime_error("Failed to open SMBIOS raw data");
  }

  struct stat st;
  if (fstat(fd, &st) != 0) {
    close(fd);
    throw std::runtime_error("fstat failed");
  }

  size_t tableLen = st.st_size;

  RawSMBIOSData* raw = (RawSMBIOSData*)malloc(sizeof(RawSMBIOSData) + tableLen);
  if (!raw) {
    close(fd);
    throw std::runtime_error("malloc failed");
  }

  raw->Length = tableLen;
  ssize_t n = read(fd, raw->SMBIOSTableData, tableLen);
  close(fd);

  if (n != (ssize_t)tableLen) {
    free(raw);
    throw std::runtime_error("Short read of SMBIOS raw data");
  }

  return new SMBIOSData(raw);
}
