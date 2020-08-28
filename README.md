# SMBIOS Parser

In order to enable an Operating System to use its I/O Devices, the BIOS Firmware Code runs to connect these devices together. Information about the devices is stored in the System BIOS (SMBIOS) Table. This table can be accessed in Windows using the [GetSystemFirmwareTable()](https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemfirmwaretable) Function provided with the System Services API [sysinfoapi.h](https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/).   

The structures within the SMBIOS Table are defined in the [DMTF Specifications](<https://www.dmtf.org/sites/default/files/standards/documents/DSP0134_3.0.0.pdf>). Each type of structure refers to a different device (Processor, Cache, Chassis, etc.).

This command-line tool enables the user to view information about some structures in the SMBIOS Table based on the specifications. The user can also view the structure table, which contains a brief description of each structure. Many structures are either obsolete or they are specific to the computer, which disables their information from being viewed with this tool.

### Using the tool:  
cmds: Display all user commands.  
table: View the SMBIOS structure table.  
all: View all structures.  
[id]: View the structure with the given ID.  
quit: Exit the program.  
