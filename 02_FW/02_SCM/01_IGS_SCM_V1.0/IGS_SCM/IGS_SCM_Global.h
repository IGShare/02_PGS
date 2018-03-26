/*
 * SCM_Global.h
 *
 * Created: 2012-12-07 오후 10:02:53
 *  Author: MinyoungEom
 */ 


#ifndef SCM_GLOBAL_H_
#define SCM_GLOBAL_H_
#include <avr/io.h>



// common
volatile uint8_t G_idDipValue;
volatile uint8_t G_cntlmodeDipValue;
volatile uint8_t G_testmodeDipValue;
uint8_t G_dipSwitchTable[16] = {
	15,7,11,3,13,5,9,1,
	14,6,10,2,12,4,8,0 
};

uint8_t G_totalUSMCnt=0;
uint8_t G_totalLGMCnt=0;
uint8_t G_invalidIDF=0;

//RS 485
typedef struct{   
	uint8_t  buffer[MAX_BUF_SIZE]; 
	uint16_t length;
 	uint16_t index; 
}u8buf;

//[STX(3)] +[SCM ID(1)] +[Data Type(1)] +[Data Length(2)] +[Data(V)] +[CRC16(2)]
//[Data Length(2)] : Length of [Data(V)]
//[CRC16(2)]       : [SCM ID(1)] 부터 [Data(V)] 까지
typedef struct{
	uint32_t stx;
	uint8_t scm_id;
	uint8_t data_type;
	uint16_t data_length;
	uint8_t data[MAX_BUF_SIZE];
	uint16_t crc16;	
}RS485Packet;

volatile u8buf	G_rxBuf485, G_txBuf485;
 RS485Packet G_485Packet;
volatile uint8_t G_485TimerOverFlowCnt		= 0;
uint8_t	iterNum = 0;
uint16_t G_RSCOMR = 0;


//Operation Mode
#define RSCOMRL0						0	  //RS 485 Command Register Low bit : REQ_USM_STAT
#define RSCOMRL1						1	  //RS 485 Command Register Low bit : REQ_LGM_STAT
#define RSCOMRL2						2     //RS 485 Command Register Low bit : SENSING_ON
#define RSCOMRL3						3     //RS 485 Command Register Low bit : SENSING_OFF
#define RSCOMRL4						4	  //RS 485 Command Register Low bit :
#define RSCOMRL5						5	  //RS 485 Command Register Low bit :
#define RSCOMRL6						6	  //RS 485 Command Register Low bit :
#define RSCOMRL7						7	  //RS 485 Command Register Low bit :Default

//Setting Mode
#define RSCOMRH0						0     //RS 485 Command Register High bit : SET_USM_ADDRESS
#define RSCOMRH1						1     //RS 485 Command Register High bit : SET_LGM_ADDRESS
#define RSCOMRH2						2     //RS 485 Command Register High bit : SET_USM_OP_MODE
#define RSCOMRH3						3	  //RS 485 Command Register High bit : SET_LGM_OP_MODE
#define RSCOMRH4						4	  //RS 485 Command Register High bit : SET_USM_PARAM
#define RSCOMRH5						5	  //RS 485 Command Register High bit : 
#define RSCOMRH6						6	  //RS 485 Command Register High bit :
#define RSCOMRH7						7	  //RS 485 Command Register High bit :

#define RSCOMKL0						(1<<RSCOMRL0)	//REQ_USM_STAT  Mask Register
#define RSCOMKL1						(1<<RSCOMRL1)	//REQ_LGM_STAT  Mask Register
#define RSCOMKL2						(1<<RSCOMRL2)	//SENSING_ON		Mask Register
#define RSCOMKL3						(1<<RSCOMRL3)	//SENSING_OFF		Mask Register
#define RSCOMKL4						(1<<RSCOMRL4)	//
#define RSCOMKL5						(1<<RSCOMRL5)	//
#define RSCOMKL6						(1<<RSCOMRL6)	//
#define RSCOMKL7						(1<<RSCOMRL7)	//Default			Mask Register

#define RSCOMKH0						(1<<RSCOMRH0)	//SET_USM_ADDRESS Mask Register
#define RSCOMKH1						(1<<RSCOMRH1)	//SET_LGM_ADDRESS Mask Register
#define RSCOMKH2						(1<<RSCOMRH2)	//SET_USM_OP_MODE Mask Register
#define RSCOMKH3						(1<<RSCOMRH3)	//SET_LGM_OP_MODE Mask Register
#define RSCOMKH4						(1<<RSCOMRH4)	//SET_USM_PARAM   Mask Register
#define RSCOMKH5						(1<<RSCOMRH5)	//SET_USM_TO_LGM  Mask Register
#define RSCOMKH6						(1<<RSCOMRH6)	//SET_USM_OP_MODE_OFF Mask Register
#define RSCOMKH7						(1<<RSCOMRH7)	//SET_LGM_OP_MODE_OFF Mask Register


//PLC

typedef struct{
	uint8_t		type;
	uint8_t		SerialNumber[3];
	uint8_t		controlID;
}PLCTxAddPacket;

typedef struct{
	uint8_t		type;
	uint8_t		controlID;
	uint8_t		OperationMode;
	uint8_t		data;
}PLCTxCntlPacket;

typedef struct{
	uint8_t mode;
	uint8_t sensor_status;
}PLCRxPacket;

volatile PLCTxAddPacket		G_txAddBufPLC;
volatile PLCTxCntlPacket		G_txCntlBufPLC;
volatile PLCRxPacket			G_rxBufPLC;


#define SULCR0						0   //USM Initial Complete bit
#define SULCR1						1   //LGM Initial Complete bit
#define SULCR2						2   //USM Address Change bit
#define SULCR3						3	//LGM Address Change bit
#define SULCR4						4	//USM Param Change bit
#define SULCR5						5	//USM OP Mode Change bit
#define SULCR6						6	//LGM OP Mode Change bit
#define SULCR7						7	//USM to LGM Change bit

#define UICF0						(1<<SULCR0)   //USM Initial Complete Flag
#define LICF1						(1<<SULCR1)   //LGM Initial Complete Flag
#define UACF2						(1<<SULCR2)   //USM Address Change Flag
#define LACF3						(1<<SULCR3)	  //LGM Address Change Flag
#define UPCF4						(1<<SULCR4)   //USM Param Change Flag
#define UOCF5						(1<<SULCR5)   //USM OP Mode Change Flag
#define LOCF6						(1<<SULCR6)	  //LGM OP Mode Change Flag
#define ULCF7						(1<<SULCR7)   //USM to LGM Change Flag

volatile uint8_t G_plcTimerOverFlowCnt		= 0;
volatile uint8_t G_plcUSMCurrentIndex		= 0;
volatile uint8_t G_plcLGMCurrentIndex		= 0;

volatile uint8_t G_usmSensingF				= 0;
volatile uint8_t G_usmStatusReqF			= 0;
volatile uint8_t G_usmOPModeOnF				= 0;
volatile uint8_t G_lgmOPModeOnF				= 0;


volatile uint8_t G_SULCR					= 0; //SCM to USM and LGM Control Register
volatile uint8_t G_SULCR_V					= 0; //SCM to USM and LGM Control Register value



volatile uint8_t u8data;
volatile uint8_t initialUSMF, initialLGMF, uaddCF, laddCF, uopmodeCF, lopmodeCF, paramCF;
volatile uint8_t ParamCnt = 0, ParamLoopCnt = 0;


// USM and LGM Status Memory
volatile uint8_t G_StatusBufUSMtoSCM[MAX_USM_SIZE];
volatile uint8_t G_StatusBufLGMtoSCM[MAX_LGM_SIZE];
volatile uint8_t G_usmStatusBuffer[MAX_USM_SIZE];
//volatile uint8_t G_preusmStatusBuffer[MAX_USM_SIZE];
volatile uint8_t G_lgmTotalCnt[MAX_LGM_SIZE];
volatile uint8_t G_lgmStatusCnt[MAX_LGM_SIZE];
volatile uint8_t G_lgmStatusBuf[MAX_LGM_SIZE];
volatile uint8_t G_usmPLCInterruptF[MAX_USM_SIZE];


volatile uint8_t G_usmCurrentCntlID;

volatile uint32_t G_usmAdd[MAX_USM_SIZE]={0,};
volatile uint32_t G_lgmAdd[MAX_LGM_SIZE]={0,};
volatile uint8_t G_usmTolgm[MAX_USM_SIZE]={0,};
volatile uint8_t G_usmOPMode[MAX_USM_SIZE]={0,};
volatile uint8_t G_lgmOPMode[MAX_LGM_SIZE]={0,};
volatile uint8_t G_usmParam[MAX_USM_SIZE*4] = {0,};
	
uint8_t G_LedOffFlag = 0;




#endif /* SCM_GLOBAL_H_ */