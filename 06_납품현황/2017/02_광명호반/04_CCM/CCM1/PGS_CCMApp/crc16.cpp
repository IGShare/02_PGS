#include "stdafx.h"
#include "crc16.h"

unsigned short CRC16_GenCode (const unsigned char* message, unsigned long length)
{
	unsigned long i;
	unsigned short crc = CRC_INIT;

	for(i = 0; i < length; i++)
	{
		CRC16(crc, message[i]);
	}

	return crc;
}
