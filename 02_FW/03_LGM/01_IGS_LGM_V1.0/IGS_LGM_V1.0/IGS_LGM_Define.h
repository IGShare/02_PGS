/*
 * USM_Define.h
 *
 * Created: 2012-10-07 오후 7:37:02
 *  Author: minyoung eom
 */ 


#ifndef USM_DEFINE_H_
#define USM_DEFINE_H_



#define PLC_TX_ONEBIT_TIME_US 2000 // 2000 /// 500

#define TIMER_INIT_VALUE 0 //116us

#define PLC_TX_ONE_BIT(a,b,name) \
		bitvalue = (name >> a) & mask;\
		PORTD = bitvalue << PD4;\
		_delay_us(b)

#define LED_GREEN_ON		(1<<PC2)
#define LED_RED_ON			(1<<PC3)
#define LED_GREEN_OFF		(0<<PC2)
#define LED_RED_OFF			(0<<PC3)

//Sensor Parameters

#define PULSE_TX_HIGH		0x20
#define PULSE_TX_LOW		0x00

//PLC Parameter
#define ONEBIT_ONE			0x02
#define ONEBIT_ZERO			0x00
#define PLC_RX_MAXBIT		36


		
		
		
#define IDX_OPMD_SM_NO_PARAM	0x08
#define IDX_OPMD_SM_PARAM1		0x0C
#define IDX_OPMD_SM_PARAM2		0x0D
#define IDX_OPMD_SM_PARAM3		0x0E
#define IDX_OPMD_SM_PARAM4		0x0F

#define IDX_OPMD_NS_LED_OFF		0x03
#define IDX_OPMD_NS_LED_ON		0x01
#define IDX_OPMD_NS_LED_ON_OFF	0x02

#define	IDX_OPM_SENS_LED_OFF		0x00
#define	IDX_OPM_SENS_LED_ON_GREEN	0x01
#define	IDX_OPM_SENS_LED_ON_RED		0x02
#define	IDX_OPM_FORC_LED_OFF		0x03
#define	IDX_OPM_FORC_LED_ON_GREEN	0x04
#define	IDX_OPM_FORC_LED_ON_RED		0x05	
#define	IDX_OPM_FORC_LED_BLINKING	0x06
#define IDX_OPM_SET_ID_COMPLETE		0x07	

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



#define EEPROM_SERIAL_ADDR      0x00
#define EEPROM_CNTLID_ADDR	    0x10
#define EEPROM_PARAM1_ADDR      0x11
#define EEPROM_PARAM2_ADDR      0x12
#define EEPROM_PARAM3_ADDR      0x13
#define EEPROM_PARAM4_ADDR      0x14

#define  IDX_PCLTYPE_CCM_USM_ADDR		0x0
#define  IDX_PCLTYPE_CCM_USM_CNTL		0x1
#define  IDX_PCLTYPE_CCM_LGM_ADDR		0x2
#define  IDX_PCLTYPE_CCM_LGM_CNTL		0x3
#define  IDX_PCLTYPE_SCM_USM_CNTL		0x4
#define  IDX_PCLTYPE_ADDR_SET_START		0x7

volatile uint8_t MYPPNSR;			//PLC Positive or Negative Status Register
#define PPS						0   //PLC Positive Status 
#define PNS						1	//PLC Negative Status




#endif /* USM_DEFINE_H_ */