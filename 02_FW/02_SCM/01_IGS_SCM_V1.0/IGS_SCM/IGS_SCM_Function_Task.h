/*
 * SCM_Function_Task.h
 *
 * Created: 2012-12-07 오후 10:04:39
 *  Author: MinyoungEom
 */ 


#ifndef SCM_FUNCTION_TASK_H_
#define SCM_FUNCTION_TASK_H_

void SCMTF_SetClock()
{
	//FUSE : CLKOPT Setting 과 함께 사용해야 함.
	XDIV &= ~(1<<XDIVEN);
	XDIV |=(1<<XDIV6)|(1<<XDIV5)|(1<<XDIV4)|(1<<XDIV3)|(1<<XDIV2)|(1<<XDIV1)|(1<<XDIV0);
	XDIV |= (1<<XDIVEN);
} 

void SCMTF_PortInit()
{
	// Port Direction
	
	DDRB = (0<<DDB7)|(1<<DDB6)|(1<<DDB5)|(1<<DDB4)|(0<<DDB3)|(0<<DDB2)|(0<<DDB1)|(0<<DDB0);
	DDRD = (0<<DDD7)|(0<<DDD6)|(0<<DDD5)|(1<<DDD4)|(1<<DDD3)|(0<<DDD2)|(0<<DDD1)|(0<<DDD0);
	DDRE = (1<<DDE7)|(0<<DDE6)|(0<<DDE5)|(1<<DDE4)|(0<<DDE3)|(1<<DDE2)|(1<<DDE1)|(0<<DDE0);
	DDRF = (0<<DDF7)|(0<<DDF6)|(0<<DDF5)|(0<<DDF4)|(0<<DDF3)|(0<<DDF2)|(0<<DDF1)|(0<<DDF0);
	DDRG |=(1<<DDG0)|(1<<DDG1); 
	
	PORTD = 0;
	PORTB = (0<<PB7)|(1<<PB6)|(1<<PB5)|(1<<PB4)|(0<<PB3)|(0<<PB2)|(0<<PB1)|(0<<PB0);
	PORTE = (0<<PE7)|(0<<PE6)|(0<<PE5)|(0<<PE4)|(0<<PE3)|(1<<PE2)|(0<<PE1)|(0<<PE0);
	PORTF = (0<<PF7)|(0<<PF6)|(0<<PF5)|(0<<PF4)|(0<<PF3)|(0<<PF2)|(0<<PF1)|(0<<PF0);
	
}

void SCMTF_ExIntInit()
{
	EICRB = (1<<ISC61)|(0<<ISC60); // External Interrupt 6 / falling Edge
}

uint8_t SCMTF_ReadDipSwitchValueMYID()
{
	uint8_t dv;
	
	dv = (PINF & 0xF0);
	dv = (dv >> 4);
			
	return G_dipSwitchTable[dv];
}

uint8_t SCMTF_ReadDipSwitchValueMode() // SCM Mode ON/OFF
{
	uint8_t dv;
	
	dv = (PINF & 0x4);
	dv = (dv >> 2);
	
	if(dv == 0)		
		return ON;
	else
		return OFF;
}

uint8_t SCMTF_ReadDipSwitchValueTest()
{
	uint8_t dv;
	
	dv = (PINF & 0x2);
	dv = (dv >> 1);
	
	if(dv == 0)		
		return ON;
	else
		return OFF;
}

uint8_t SCMTF_CheckOverCurrent()
{
	uint8_t mask, pinvalue;
	
	mask = (1<<PE5); //Current Sensing Port is PF5
	pinvalue = PINE & mask; //Normal : PE5 high / Abnormal PE5 low  
	
	if(pinvalue == mask)
		return HIGH;
	else
		return LOW;
}





#endif /* SCM_FUNCTION_TASK_H_ */