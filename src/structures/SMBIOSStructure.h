#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>

class SMBIOSStructure {
public:
  byte type;
  byte length;
  word handle;
};
