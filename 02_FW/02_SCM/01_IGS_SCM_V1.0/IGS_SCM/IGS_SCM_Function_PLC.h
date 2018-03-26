/*
 * SCM_Function_PLC.h
 *
 * Created: 2012-12-07 오후 10:04:10
 *  Author: MinyoungEom
 */ 


#ifndef SCM_FUNCTION_PLC_H_
#define SCM_FUNCTION_PLC_H_

void SCMPLCF_PLCTxTimerInit()
{
	TCCR2 = (0<<CS22)|(0<<CS21)|(0<<CS20);
	TIMSK |= (1<<TOIE2);
	TCNT2 = 0;
}

void SCMPLCF_StatusUSMBuffInit()
{
	uint16_t i;
	for(i=0; i<MAX_USM_SIZE; i++)
	{
		G_StatusBufUSMtoSCM[i] = 0;
		G_usmStatusBuffer[i] = 0;
		//G_preusmStatusBuffer[i] = 0;
		G_usmPLCInterruptF[i] = 0;
	}
	G_StatusBufUSMtoSCM[0]= G_totalUSMCnt;
}
void SCMPLCF_StatusLGMBuffInit()
{
	uint16_t i;
	for(i=0; i<MAX_LGM_SIZE; i++)
	{
		G_StatusBufLGMtoSCM[i] = 0;
		G_lgmStatusBuf[i] = 0;
	}
	G_StatusBufLGMtoSCM[0]= G_totalLGMCnt;
}

void SCMPLCF_lgmStatusBuffInit()
{
	uint16_t i;
	for(i=0; i<MAX_LGM_SIZE; i++)
	{
		G_lgmStatusCnt[i] = 0;
	}
}

void SCMPLCF_lgmTotalCntBuffInit()
{
	uint16_t i;
	for(i=0; i<MAX_LGM_SIZE; i++)
	{
		G_lgmTotalCnt[i] = 0;
	}
}

void SCMPLCF_SendMessageAddPacket(PLCTxAddPacket message)
{
	uint8_t mask = 0x01;
	uint8_t bitvalue;
	
	PLC_TX_BIT(0,PLC_TX_DELAY,mask,bitvalue);
	
	PLC_TX_BIT(0,PLC_TX_DELAY,message.type,bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.type,bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.type,bitvalue);

	PLC_TX_BIT(0,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	PLC_TX_BIT(3,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	PLC_TX_BIT(4,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	PLC_TX_BIT(5,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	PLC_TX_BIT(6,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	PLC_TX_BIT(7,PLC_TX_DELAY,message.SerialNumber[0],bitvalue);
	
	PLC_TX_BIT(0,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	PLC_TX_BIT(3,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	PLC_TX_BIT(4,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	PLC_TX_BIT(5,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	PLC_TX_BIT(6,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	PLC_TX_BIT(7,PLC_TX_DELAY,message.SerialNumber[1],bitvalue);
	
	PLC_TX_BIT(0,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);
	PLC_TX_BIT(3,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);
	PLC_TX_BIT(4,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);
	PLC_TX_BIT(5,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);
	PLC_TX_BIT(6,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);
	PLC_TX_BIT(7,PLC_TX_DELAY,message.SerialNumber[2],bitvalue);


	PLC_TX_BIT(0,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(3,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(4,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(5,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(6,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(7,PLC_TX_DELAY,message.controlID,bitvalue);
	
	PORTE = (0<<PE7)|(0<<PE6)|(0<<PE5)|(0<<PE4)|(0<<PE3)|(1<<PE2)|(0<<PE1)|(0<<PE0);  // 485 Rx On

}

void SCMPLCF_SendMessageCntlPacket(PLCTxCntlPacket message)
{
	uint8_t mask = 0x01;
	uint8_t bitvalue;

	PLC_TX_BIT(0,PLC_TX_DELAY,mask,bitvalue);
	
	PLC_TX_BIT(0,PLC_TX_DELAY,message.type,bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.type,bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.type,bitvalue);

	PLC_TX_BIT(0,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(3,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(4,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(5,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(6,PLC_TX_DELAY,message.controlID,bitvalue);
	PLC_TX_BIT(7,PLC_TX_DELAY,message.controlID,bitvalue);
	
	PLC_TX_BIT(0,PLC_TX_DELAY,message.OperationMode,bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.OperationMode,bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.OperationMode,bitvalue);
	PLC_TX_BIT(3,PLC_TX_DELAY,message.OperationMode,bitvalue);
	
	PLC_TX_BIT(0,PLC_TX_DELAY,message.data,bitvalue);
	PLC_TX_BIT(1,PLC_TX_DELAY,message.data,bitvalue);
	PLC_TX_BIT(2,PLC_TX_DELAY,message.data,bitvalue);
	PLC_TX_BIT(3,PLC_TX_DELAY,message.data,bitvalue);
	PLC_TX_BIT(4,PLC_TX_DELAY,message.data,bitvalue);
	PLC_TX_BIT(5,PLC_TX_DELAY,message.data,bitvalue);
	PLC_TX_BIT(6,PLC_TX_DELAY,message.data,bitvalue);
	PLC_TX_BIT(7,PLC_TX_DELAY,message.data,bitvalue);
	
	PORTE = (0<<PE7)|(0<<PE6)|(0<<PE5)|(0<<PE4)|(0<<PE3)|(1<<PE2)|(0<<PE1)|(0<<PE0); // 485 Rx On
}
//
#endif /* SCM_FUNCTION_PLC_H_ */