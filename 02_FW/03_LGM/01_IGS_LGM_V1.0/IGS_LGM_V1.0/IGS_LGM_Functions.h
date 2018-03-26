/*
 * USM_Functions.h
 *
 * Created: 2012-10-07 오후 10:24:30
 *  Author: minyoung eom
 */ 


#ifndef USM_FUNCTIONS_H_
#define USM_FUNCTIONS_H_

void USMF_InitialRegisterSetting()
{
	SMCR = (0<<SM2)|(1<<SM1)|(1<<SM0)|(1<<SE);
	PRR = (1<<PRTWI) | (1<<PRTIM2) | (0<<PRTIM0) | (1<<PRTIM1) | (1<<PRSPI) | (1<<PRUSART0) | (0<<PRADC);
		
}
void USMF_PortInit()
{
	DDRB = (0<<DDB7)|(0<<DDB6)|(0<<DDB5)|(0<<DDB4)|(0<<DDB3)|(0<<DDB2)|(1<<DDB1)|(1<<DDB0);
	DDRC = (1<<DDC3)|(1<<DDC2)|(0<<DDC0);
	DDRD = (1<<DDD5)|(0<<DDD3)|(0<<DDD2)|(1<<DDD4);
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTC = LED_GREEN_ON;
}

void USMF_ExternalInterruptInit()
{
    EICRA  = (0 << ISC00);
	EICRA |= (1 << ISC01);    // set INT0 to trigger on Falling EDge
	EICRA |= (1 << ISC10);
	EICRA |= (1 << ISC11);    // set INT1 to trigger on Rising Edge
	
    EIMSK = (1 << INT0) | (1 << INT1);   // Turns on INT0 and INT1
}

void USMF_TimerZeroInit()
{
	TCCR0A = (0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
	TCCR0B = (0<<FOC0A) | (0<<FOC0B) | (0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
	TIMSK0 = (1<<TOIE0);
	TIFR0 = (1<<TOV0);
	//TCNT0 = TIMER_INIT_VALUE;
}

void USMF_StatusInit()
{

	G_plcRxBitCnt		= 0;
	MYPPNSR				= 0;
	
	G_plcRxBuffer[0]	= 0;
	G_plcRxBuffer[1]	= 0;
	G_plcRxBuffer[2]	= 0;
	G_plcRxBuffer[3]	= 0;
	G_plcRxBuffer[4]	= 0;
	G_plcRxBuffer[5]	= 0;
}

uint32_t USMF_ReadSerialNumber()
{
	uint8_t serialtmp[3];
	uint32_t serial;
	
	//eeprom_write_byte((uint8_t *)8, 0);
	
	serialtmp[0] = eeprom_read_byte((uint8_t *)4);
	serialtmp[1] = eeprom_read_byte((uint8_t *)5);
	serialtmp[2] = eeprom_read_byte((uint8_t *)6);
	
	serial = ((uint32_t)serialtmp[0] << 16) + ((uint32_t)serialtmp[1] << 8) + ((uint32_t)serialtmp[2]);
	return serial;
}

void ReadDefaultParmaFromEEPROM()
{
	EPR_ID = eeprom_read_byte((uint8_t *)7);
	MaxSampleNum = eeprom_read_byte((uint8_t *)9);
	MaxSampleNum = ((MaxSampleNum * 10 + 150 ) * 74) >> 6; // 0.86 = 64/74 (근사값)
	ADCLevelThreshold = eeprom_read_byte((uint8_t *)10);
	ADCLevelThreshold = ADCLevelThreshold + 50;
	ADCCntThreshold = eeprom_read_byte((uint8_t *)11);
	ADCCntThreshold = ADCCntThreshold+1;
	BurstCnt = eeprom_read_byte((uint8_t *)12);
	BurstCnt = BurstCnt+1;
}
void USMF_ADCInit(void)
{
	ADCCNT	=	0;
	// Internal Vref turned off
	// ADC Left Adjust Result
	// ADC0 Channel Selection
	ADMUX	=	(0<<REFS1)|(0<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	
	// ADC Enable
	// ADC Start Conversion Wait
	// ADC  Prescaler Division Factor 2 ---> 1MHz /2 = 500kHz ---> 2us ---> Convert Time 2us * 25 adc clock = 50us
	ADCSRA	=	(1<<ADEN)|(0<<ADSC)|(0<<ADATE)|(0<<ADIF)|(0<<ADIE)|(0<<ADPS2)|(0<<ADPS1)|(1<<ADPS0);
}

void USMF_TxPulsing(uint8_t cnt) // Tx Freqency : 33.3kHz
{
	for(int i=0; i<cnt; i++){
		PORTD = PULSE_TX_HIGH;
		_delay_us(10); // 10 us
		PORTD = PULSE_TX_LOW;
		_delay_us(5); // 5 us	
	}
}

uint8_t USMF_StatusOfParkingLotFromCount(uint8_t cnt)
{
	if(cnt > ADCCntThreshold)
		return 1;
	else
		return 0;
}

void USMF_PLC_TX(struct TypeOnePacket rxmessage, struct TxPacket *txmessage)
{
	uint8_t bitvalue;
	uint8_t mask = 0x01;
	uint8_t plcTxData=0;
	
	if(txmessage->mode == 1) // Sensing mode
	{
		if(txmessage->sensor_status == 1)
			plcTxData = IDX_OPM_SENS_LED_ON_RED;
		else
			plcTxData = IDX_OPM_SENS_LED_ON_GREEN;	
	}
	else  // Sensor LED Control Mode
	{
		switch(rxmessage.OperationMode)
		{
			case IDX_OPM_FORC_LED_OFF : {
				PORTC = LED_GREEN_OFF;
				plcTxData = IDX_OPM_FORC_LED_OFF;
				break;
			}								
			case IDX_OPM_FORC_LED_ON_GREEN :{
				PORTC = LED_GREEN_ON;
				plcTxData = IDX_OPM_FORC_LED_ON_GREEN;
				break;
			}
			case IDX_OPM_FORC_LED_ON_RED :{
				PORTC = LED_RED_ON;
				plcTxData = IDX_OPM_FORC_LED_ON_RED;
				break;
			}
			case IDX_OPM_FORC_LED_BLINKING :{
				if(LEDStatus==0)
				{
					PORTC = LED_GREEN_ON;
					LEDStatus = 1;
				}
				else if(LEDStatus==1)
				{
					PORTC = LED_RED_ON;
					LEDStatus = 0;
				}
				plcTxData = IDX_OPM_FORC_LED_BLINKING;		
				break;
			}
		}
		_delay_ms(12);
	}
	
	_delay_ms(1);
	//Start Bit
	PLC_TX_ONE_BIT(0,PLC_TX_ONEBIT_TIME_US,mask);

	PLC_TX_ONE_BIT(0,PLC_TX_ONEBIT_TIME_US,plcTxData);
	PLC_TX_ONE_BIT(1,PLC_TX_ONEBIT_TIME_US,plcTxData);
	PLC_TX_ONE_BIT(2,PLC_TX_ONEBIT_TIME_US,plcTxData);
	
	PORTD = ONEBIT_ZERO;
}

uint8_t USMF_SensingFunction()
{
	uint32_t i;
	uint32_t ADCDATA;
	
	USMF_TxPulsing(BurstCnt);
	_delay_ms(2);
	
	for( i=0; i<MaxSampleNum; i++)
	{
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADSC)) == 1);
		ADCDATA = ADCH;
		{
			if(ADCDATA>ADCLevelThreshold)
				ADCCNT ++;
		}					
	}
	ParkingFlag = USMF_StatusOfParkingLotFromCount(ADCCNT);
	
		
	if(ParkingFlag == 1)
		PORTC = LED_RED_ON;
	else
		PORTC = LED_GREEN_ON;
		
	ADCCNT = 0;
	return ParkingFlag;
}


void USMF_SensorOPMControl(struct TypeOnePacket rxmessage, struct TxPacket *txmessage)
{

	switch(rxmessage.OperationMode)
	{
		case IDX_OPM_FORC_LED_OFF : {
			txmessage->mode = 0;
			USMF_PLC_TX(rxmessage, txmessage);
			break;
		}								
		case IDX_OPM_FORC_LED_ON_GREEN :{
			txmessage->mode = 0;
			USMF_PLC_TX(rxmessage, txmessage);
			break;
		}
		case IDX_OPM_FORC_LED_ON_RED :{
			txmessage->mode = 0;
			USMF_PLC_TX(rxmessage, txmessage);						
			break;	
		}
		case IDX_OPM_FORC_LED_BLINKING :{
			txmessage->mode = 0;
			USMF_PLC_TX(rxmessage, txmessage);						
			break;	
		}
		case IDX_OPM_SENSING_ON :{
	
			txmessage->mode = 1;
			txmessage->sensor_status=USMF_SensingFunction();
			
			USMF_PLC_TX(rxmessage, txmessage);
			break;
		}
		case IDX_OPM_PARAM_SETTING_PARAM1 :{
			MaxSampleNum = (uint32_t)rxmessage.data;
			MaxSampleNum = ((MaxSampleNum * 10 + 150 ) * 74) >> 6; // 0.86 = 64/74 (근사값)
			break;
		}
		case IDX_OPM_PARAM_SETTING_PARAM2 :{
			ADCLevelThreshold = rxmessage.data+50;
			break;
		}
		case IDX_OPM_PARAM_SETTING_PARAM3 :{
			ADCCntThreshold = rxmessage.data+1;
			break;
		}
		case IDX_OPM_PARAM_SETTING_PARAM4 :{
			BurstCnt = rxmessage.data+1;
			break;
					
		}
	}
}

void USMF_SetControlIDCompleteResponse()
{
	uint8_t bitvalue=0;
	uint8_t mask = 0x01;
	uint8_t plcTxData=IDX_OPM_SET_ID_COMPLETE;
	
	//Start Bit
	PLC_TX_ONE_BIT(0,PLC_TX_ONEBIT_TIME_US,mask);

	PLC_TX_ONE_BIT(0,PLC_TX_ONEBIT_TIME_US,plcTxData);
	PLC_TX_ONE_BIT(1,PLC_TX_ONEBIT_TIME_US,plcTxData);
	PLC_TX_ONE_BIT(2,PLC_TX_ONEBIT_TIME_US,plcTxData);
	
	PORTD = ONEBIT_ZERO;
}

#endif /* USM_FUNCTIONS_H_ */