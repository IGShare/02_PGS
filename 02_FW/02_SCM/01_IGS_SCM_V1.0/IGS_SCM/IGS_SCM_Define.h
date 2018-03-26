/*
 * SCM_Define.h
 *
 * Created: 2012-12-07 오후 10:03:11
 *  Author: MinyoungEom
 */ 


#ifndef SCM_DEFINE_H_
#define SCM_DEFINE_H_

//Common
#define WRITE_OK						1
#define WRITE_FAIL						0

//Task Function
#define LOW								0
#define HIGH							1

#define TRUE							1
#define FALSE							0

#define ON								1
#define OFF								0


//RS 485 Function
//#define F_CPU							8000000
#define BAUD							38400
#define MYUBRR							F_CPU/16/BAUD-1

#define MAX_USM_SIZE					120
#define MAX_LGM_SIZE					40
#define MAX_BUF_SIZE					MAX_USM_SIZE * 4


//#define IDX_DT_REQ_USM_LGM_STAT			0x01
#define IDX_DT_REQ_USM_STAT				0x01
#define IDX_DT_REQ_LGM_STAT				0x02

//#define IDX_DT_RES_USM_LGM_STAT			0x11
#define IDX_DT_RES_USM_STAT				0x11
#define IDX_DT_RES_LGM_STAT				0x12

#define	IDX_DT_SET_USM_ADDRESS			0x21
#define	IDX_DT_SET_LGM_ADDRESS			0x22
#define	IDX_DT_SET_USM_OP_MODE			0x23
#define	IDX_DT_SET_LGM_OP_MODE			0x24
#define	IDX_DT_SET_USM_PARAM			0x25
#define	IDX_DT_SET_USM_TO_LGM			0x26
#define	IDX_DT_SET_USM_OP_MODE_OFF		0x27
#define	IDX_DT_SET_LGM_OP_MODE_OFF		0x28

#define	IDX_DT_ACK						0x31

#define	IDX_DT_NACK						0x41
#define	IDX_DT_INIT						0x42

#define	IDX_DT_SENSING_OFF				0x61
#define IDX_DT_SENSING_ON				0x62


#define RS485_RX_STX_ERROR				0x00
#define RS485_RX_CRC_ERROR				0x01
#define RS485_RX_INVALID_ID				0x02
#define RS485_RX_OK						0x03

//PLC
#define PLC_TX_DELAY  277
#define PLC_RX_DELAY  (2000)//(500*8)//
#define PLC_RX_DELAY_INIT  (3000)//(750*8)//

#define PLC_TX_BIT(a,b,name,bitvalue) \
		bitvalue = (name >> a) & mask;\
		PORTE  = (bitvalue<<PE7)| (1<<PE2);\
		_delay_us(b)
		
#define PLC_RX_ONE_BIT(a,b,name,bitvalue)	\
		bitvalue = PINE;\
		bitvalue = bitvalue & (1<<PE6);\
		bitvalue = bitvalue >> PE6;\
		name = name + (bitvalue << a);\
		_delay_us(b)

//Operation Mode
#define  IDX_OPM_SENSING_ON				0x08
#define  IDX_OPM_SENS_LED_OFF			0x00
#define  IDX_OPM_SENS_LED_ON_GREEN		0x01
#define  IDX_OPM_SENS_LED_ON_RED		0x02
#define  IDX_OPM_FORC_LED_OFF			0x03
#define  IDX_OPM_FORC_LED_ON_GREEN		0x04
#define  IDX_OPM_FORC_LED_ON_RED		0x05
#define  IDX_OPM_FORC_LED_BLINKING		0x06
#define  IDX_OPM_PARAM_SETTING			0x10
#define  IDX_OPM_PARAM_SETTING_PARAM1	0x0C
#define  IDX_OPM_PARAM_SETTING_PARAM2	0x0D
#define  IDX_OPM_PARAM_SETTING_PARAM3	0x0E
#define  IDX_OPM_PARAM_SETTING_PARAM4	0x0F


//PLC Packet Type
#define  IDX_PCLTYPE_CCM_USM_ADDR		0x0
#define  IDX_PCLTYPE_CCM_USM_CNTL		0x1
#define  IDX_PCLTYPE_CCM_LGM_ADDR		0x2
#define  IDX_PCLTYPE_CCM_LGM_CNTL		0x3
#define  IDX_PCLTYPE_SCM_USM_ADDR		0x5
#define  IDX_PCLTYPE_SCM_USM_CNTL		0x4
#define  IDX_PCLTYPE_SCM_LGM_ADDR		0x6
//#define  IDX_PCLTYPE_SCM_LGM_CNTL		0x7
#define  IDX_PCLTYPE_ADDR_SET_START     0x7
#endif /* SCM_DEFINE_H_ */

	