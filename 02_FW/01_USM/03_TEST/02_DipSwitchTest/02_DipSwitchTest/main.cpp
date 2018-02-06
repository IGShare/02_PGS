/*
 * 02_DipSwitchTest.cpp
 *
 * Created: 2017-04-11 오후 1:09:51
 * Author : myeom
 */ 

#include <avr/io.h>

#define LED_GREEN_ON		(1<<PC2)
#define LED_RED_ON			(1<<PC3)
#define LED_GREEN_OFF		(0<<PC2)
#define LED_RED_OFF			(0<<PC3)

void USMF_PortInit()
{
	DDRB = (0<<DDB7)|(0<<DDB6)|(0<<DDB5)|(0<<DDB4)|(0<<DDB3)|(0<<DDB2)|(0<<DDB1)|(0<<DDB0);
	DDRC = (1<<DDC3)|(1<<DDC2)|(0<<DDC1)|(0<<DDC0);
	DDRD = (1<<DDD5)|(0<<DDD3)|(0<<DDD2)|(1<<DDD4)|(0<<DDD1)|(0<<DDD0);
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
}void USMF_ADCInit(void)
{
	//ADCCNT	=	0;
	// Internal Vref turned off
	// ADC Left Adjust Result
	// ADC0 Channel Selection
	ADMUX	=	(0<<REFS1)|(0<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	
	// ADC Enable
	// ADC Start Conversion Wait
	// ADC  Prescaler Division Factor 2 ---> 1MHz /2 = 500kHz ---> 2us ---> Convert Time 2us * 25 adc clock = 50us
	ADCSRA	=	(1<<ADEN)|(0<<ADSC)|(0<<ADATE)|(0<<ADIF)|(0<<ADIE)|(0<<ADPS2)|(0<<ADPS1)|(1<<ADPS0);
}

/*
Dip Switch Number
PB0 : 0번
PB1 : 1
PD0 : 2
PD1 : 3
PB2 : 4
PC1 : 5
ADC6: 6
ADC7: 7

*/

int main(void)
{
    /* Replace with your application code */
	USMF_PortInit();
	USMF_ADCInit();
    while (1) 
    {
		uint8_t dipVal;
		//dipVal = PINC & (1<<PC1);
		//dipVal = dipVal>>1;
		
		uint32_t ADCDATA;
		
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADSC)) == 1);
		ADCDATA = ADCH;
		{
			if(ADCDATA>100)
			dipVal=1;
			else
			dipVal=0;
			
		}
		if(dipVal == 1)
		{
			PORTC |= (1<<PC2);
		}
		
		if(dipVal == 0)
		{
			PORTC &= ~(1<<PC2);
		}
		

		

    }
}

