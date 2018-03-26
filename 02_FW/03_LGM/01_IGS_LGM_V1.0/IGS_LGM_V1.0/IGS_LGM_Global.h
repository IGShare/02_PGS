/*
 * USM_Global.h
 *
 * Created: 2012-10-07 오후 10:26:49
 *  Author: minyoung eom
 */ 


#ifndef USM_GLOBAL_H_
#define USM_GLOBAL_H_

/************************************************************

	EEPROM Structure

Serial Number (56byte) | Control ID (1byte) |
PARAM1 (1byte) | PARAM2 (1byte) | PARAM3 (1byte) | PARAM4 (1byte)
*************************************************************/
int				ADCCNT					= 0;
uint8_t			ParkingFlag				= 0;


uint32_t		MaxSampleNum			= 290; // depth / 0.86 - 40
uint8_t			ADCLevelThreshold		= 67; //67 : 1V / 101 : 1.5V  / 134 : 2V
uint8_t			ADCCntThreshold			= 3;
uint8_t			BurstCnt				= 10;


uint8_t			LEDStatus				= 0;
uint8_t			LED_BLINK_CNT			= 0;

uint32_t		mySerialNumber			= 0;
uint32_t		rxSerialNumber			= 0;
uint8_t			SN_ReceiveSuccessRisingF	= 0;
uint8_t			SN_ReceiveSuccessFallingF   =0;
uint8_t			MY_ID					= 0;
uint8_t			EPR_ID					= 0;


struct TypeZeroPacket
{
	uint8_t	SerialNumber[3];
	uint8_t		controlID;
};
struct TypeOnePacket
{
	uint8_t		controlID;
	uint8_t		OperationMode;
	uint8_t		data;
};

struct TxPacket
{
	uint8_t		mode;
	uint8_t		sensor_status;
};

volatile uint8_t G_plcRxBuffer[6];
volatile uint8_t G_plcRxBitCnt=0;
volatile uint8_t G_RisingF = 0;
volatile uint8_t G_FallingF = 0;

volatile uint8_t G_preBitValue = 0;
volatile uint8_t LEDF = 0;

volatile uint8_t G_isSameValue = 0;


#endif /* USM_GLOBAL_H_ */