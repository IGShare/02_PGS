#define AVR_STUDIO_INSTALL_PATH     L"C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\"
#define AVR_ATPROGRAM_FILE_PATH		L"atbackend"
#define AVR_ATPROGRAM_FILE_NAME		L"atprogram.exe"

#define AVR_PROGRAMMER_NAME0		L"avrispmk2"
#define AVR_PROGRAMMER_NAME1		L"STK500"
#define AVR_PROGRAMMING_INTERFACE0  L"isp"

#define AVR_DEVICE_NAME0			L"Atmega48"
#define AVR_DEVICE_NAME1			L"Atmega128"
#define AVR_DEVICE_NAME2			L"Atmega48PA"
#define AVR_DEVICE_NAME3			L"Atmega88PA"

#define AVR_PROG_OPTION_DEFAULT		L"program -f"
#define AVR_PROG_OPTION_ERASE		L"program -c -fl -f"
#define AVR_PROG_OPTION_VERIFY		L"program --verify -f"
#define AVR_PROG_OPTION_ERASE_VERIFY		L"program -c -fl --verify -f"

#define AVR_PROG_OPTION_EEPROM_READ		L"read -ee"
#define AVR_PROG_OPTION_EEPROM_WRITE	L"write -ee"

#define AVR_PROG_OPTION_FUSES_READ		L"read -fs"
#define AVR_PROG_OPTION_FUSES_WRITE		L"write -fs --values"