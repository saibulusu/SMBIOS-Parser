#include "SMBIOSData.h"
using namespace std;

#ifdef __linux__
SMBIOSData SMBIOSData::fromLinux() {
  SMBIOSData result;

  const char* path = "/sys/firmware/dmi/tables/DMI";

  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    throw std::runtime_error("Failed to open SMBIOS table");
  }

  struct stat st;
  if (fstat(fd, &st)) {
    close(fd);
    throw std::runtime_error("fstat failed");
  }

  result.length = st.st_size;
  result.table.resize(result.length);

  ssize_t n = read(fd, result.table.data(), result.length);
  close(fd);

  if (n != (ssize_t)result.length) {
    throw std::runtime_error("Short read of SMBIOS table");
  }

  return result;
}
#endif

uint32_t SMBIOSData::getLength() const {
  return length;
}

const uint8_t* SMBIOSData::data() const {
  return table.data();
}
