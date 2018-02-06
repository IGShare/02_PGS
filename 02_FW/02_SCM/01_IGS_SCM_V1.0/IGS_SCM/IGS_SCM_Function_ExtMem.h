/*
 * SCM_Function_ExtMem.h
 *
 * Created: 2012-12-11 오전 12:58:07
 *  Author: MinyoungEom
 */ 


#ifndef SCM_FUNCTION_EXTMEM_H_
#define SCM_FUNCTION_EXTMEM_H_



// External Memory 
/**************************************************************************************************
                                        Memory Structure
  
  USM Total Count (1byte) | PGM Total Count |                                         (Total Count 2byte)

  Serial Number(3byte) | Control ID(1byte) | LGM ID(1byte) | Operation Mode(1byte) | 
  Parameter1 (1ybyte) | Parameter2 (1byte) | Parameter3(1byte) | Parameter 4(1byte)|  (USM1 14byte)
     :
  Serial Number(3byte) | Control ID(1byte) | Operation Mode(1byte) |                  (LGM1 5byte)
     :
	
  *************************************************************************************************/  
  
#define WRITE_XMEM_ADDR(x)			(*(unsigned char *)(x))
#define READ_XMEM_ADDR(x)			(*(unsigned char *)(x))
#define XMEM_BASE_ADDR_USM			0x1102 //External Memory : 0x1100 ~ 0xFFFF

#define USM_OFFSET					0x0A
#define USM_CNTLID_OFFSET			0x03
#define USM_LGMID_OFFSET			0x04
#define USM_MODE_OFFSET				0x05

#define USM_PARAM1_OFFSET			0x06
#define USM_PARAM2_OFFSET			0x07
#define USM_PARAM3_OFFSET			0x08
#define USM_PARAM4_OFFSET			0x09

#define XMEM_BASE_ADDR_LGM			0x1775
#define LGM_OFFSET					0x05
#define LGM_CNTLID_OFFSET			0x03
#define LGM_MODE_OFFSET				0x04

#define	 MAX_USM_CNT				127
#define  MAX_LGM_CNT				64
#define  MAX_USM_PARAM_CNT			4
#define  MAX_SN_BYTE				3
#define  MAX_CNTLID_BYTE			1
#define  MAX_OPMODE_BYTE            1
#define  MAX_USM_TO_LCM_CNT         1


void SCM485F_ExtMemInit()
{
	MCUCR |=(1<<SRE)|(0<<SRW10);

	XMCRA = (0<<SRL2)|(1<<SRL1)|(0<<SRL0)|(1<<SRW01)|(1<<SRW10)|(0<<SRW11);
	XMCRB = (1<<XMBK)|(0<<XMM2)|(1<<XMM1)|(0<<XMM0);
}

void SCMEMF_ReadExtMemTest(uint16_t addr, uint8_t val)
{
	uint8_t ch;
	ch = READ_XMEM_ADDR(addr);
	if(ch == val) PORTB &= ~(1<<PB4);
}

void SCMEMF_WriteExtMemUSMAddr( uint8_t *data, uint8_t totalCnt)
{
	uint16_t i;
	
	for(i = 0; i<totalCnt; i++)
	{
		//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_CNTLID_OFFSET) = data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE)]; //Control ID
		//for(j=MAX_CNTLID_BYTE; j<MAX_SN_BYTE+MAX_CNTLID_BYTE; j++)
		//{
			//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i+j-1) = data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + j];
		//}
		G_usmAdd[i] = ((uint32_t)data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + 1] <<16 ) | (data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + 2] << 8) | (data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + 3]);
		G_usmOPMode[i] = 0;

		//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_MODE_OFFSET) = 0; // Operation mode init
		//
		//for(j=MAX_CNTLID_BYTE; j<MAX_USM_PARAM_CNT+MAX_CNTLID_BYTE; j++) // Parameter init
		//{
			//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_PARAM1_OFFSET+j-1) = 0;
		//}
		//
		//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_LGMID_OFFSET) = 0; //USM to LGM ID init
	}

	G_SULCR |= UACF2;
}

void SCMEMF_WriteExtMemLGMAddr(volatile uint8_t *data, uint8_t totalCnt)
{
	uint16_t i;	
	for(i = 0; i<totalCnt; i++)
	{
		//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_LGM + LGM_OFFSET*i + LGM_CNTLID_OFFSET) = data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE)]-128; //Control ID
		//for(j=MAX_CNTLID_BYTE; j<MAX_SN_BYTE+MAX_CNTLID_BYTE; j++)
		//{
			//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_LGM + LGM_OFFSET*i+j-1) = data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + j];
		//}
		G_lgmAdd[i] = ((uint32_t)data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + 1] <<16 ) | (data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + 2] << 8) | (data[i*(MAX_SN_BYTE+MAX_CNTLID_BYTE) + 3]);
		G_lgmOPMode[i] = 0;
		//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_LGM + LGM_OFFSET*i + LGM_MODE_OFFSET) = 0; // Operation mode init
	}
	
	G_SULCR |= LACF3;
}

void SCMEMF_WriteExtMemUSMCntlID(uint8_t totalCnt)
{
	uint16_t i;
	for(i = 0; i<totalCnt; i++)
	{
		WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_CNTLID_OFFSET) = i+1; //Control ID
	}		
}

void SCMEMF_WriteExtMemUSMOPMode(volatile uint8_t *data, uint8_t totalCnt)
{
	uint16_t i, m=0;
	for(i = 0; i<totalCnt; i++)
	{
		//if(READ_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_CNTLID_OFFSET + USM_OFFSET*i) == data[m])
		//{
		//	WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_MODE_OFFSET) = data[m + MAX_CNTLID_BYTE];
			G_usmOPMode[i] = data[m + MAX_CNTLID_BYTE];
			m=m+MAX_CNTLID_BYTE+MAX_OPMODE_BYTE;

		//}
	}
	G_SULCR |= UOCF5;
}

void SCMEMF_WriteExtMemLGMOPMode(volatile uint8_t *data, uint8_t totalCnt)
{
		uint16_t i, m=0;
	for(i = 0; i<totalCnt; i++)
	{
		//if(READ_XMEM_ADDR(XMEM_BASE_ADDR_LGM + LGM_CNTLID_OFFSET + LGM_OFFSET*i) == data[m]-128)
		//{
			//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_LGM +LGM_OFFSET*i+ LGM_MODE_OFFSET) = data[m + MAX_CNTLID_BYTE];
			G_lgmOPMode[i] = data[m + MAX_CNTLID_BYTE];
			m=m+MAX_CNTLID_BYTE+MAX_OPMODE_BYTE;
			
//		}
	}
	
	G_SULCR |= LOCF6;
}

void SCMEMF_WriteExtMemUSMParam(volatile uint8_t *data, uint8_t totalCnt)
{
	uint16_t i, j, m=0;
	for(i = 0; i<totalCnt; i++)
	{
		//if(READ_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_CNTLID_OFFSET + USM_OFFSET*i) == data[m])
		//{
			for(j=MAX_CNTLID_BYTE; j<MAX_USM_PARAM_CNT+MAX_CNTLID_BYTE; j++)
			{
				//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_PARAM1_OFFSET+j-1) = data[m + j];
				G_usmParam[i*4+j-1] = data[m + j];
			}
			
			m=m+MAX_USM_PARAM_CNT+MAX_CNTLID_BYTE;
//		}
	}
	
	G_SULCR |= UPCF4;
}

void SCMEMF_WriteExtMemUSMtoLGM(volatile uint8_t *data, uint8_t totalCnt)
{
	uint16_t i, m=0;
	uint16_t tmpData;
	
	SCMPLCF_lgmTotalCntBuffInit();
	for(i = 0; i<totalCnt; i++)
	{
		//if(READ_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_CNTLID_OFFSET + USM_OFFSET*i) == data[m])
		//{
			//WRITE_XMEM_ADDR(XMEM_BASE_ADDR_USM + USM_OFFSET*i + USM_LGMID_OFFSET) = data[m + MAX_CNTLID_BYTE]-128;
			G_usmTolgm[i] = data[m + MAX_CNTLID_BYTE]-128;

			tmpData = data[m + MAX_CNTLID_BYTE] -128;
			G_lgmTotalCnt[tmpData] ++;

			m=m+MAX_USM_TO_LCM_CNT+MAX_CNTLID_BYTE;
//		}
	}
	G_SULCR |= ULCF7;
}
#endif /* SCM_FUNCTION_EXTMEM_H_ */