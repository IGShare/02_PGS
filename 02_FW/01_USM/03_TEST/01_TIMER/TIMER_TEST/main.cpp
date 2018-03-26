/*
 * TIMER_TEST.cpp
 *
 * Created: 2017-02-19 오전 11:25:45
 * Author : myeom
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t G_plcRxBuffer[6];
volatile uint8_t G_plcRxBitCnt=0x0;
volatile uint8_t G_preBitValue = 0;
volatile uint8_t G_isSameValue = 0;
void timerInit()
{
	TCCR0A = (0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
	TCCR0B = (0<<CS02) | (0<<CS01) | (1<<CS00);
	TIMSK0 = (1<<TOIE0);
	TIFR0 = (1<<TOV0);
	TCNT0 = 162;

}
void USMF_PortInit()
{
	DDRB = (0<<DDB7)|(0<<DDB6)|(0<<DDB5)|(0<<DDB4)|(0<<DDB3)|(0<<DDB2)|(0<<DDB1)|(0<<DDB0);
	DDRC = (1<<DDC3)|(1<<DDC2)|(0<<DDC0);
	DDRD = (1<<DDD5)|(0<<DDD3)|(0<<DDD2)|(1<<DDD4);
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTC = 0;
}
int main(void)
{
    /* Replace with your application code */
	USMF_PortInit();
	timerInit();
	sei();
    while (1) 
    {
		if(G_isSameValue == 1){
			PORTC ^= (1<<PC2);
			G_plcRxBuffer[(G_plcRxBitCnt>>3)] |= G_preBitValue << (G_plcRxBitCnt - ((G_plcRxBitCnt>>3) << 3));
			G_plcRxBitCnt++;
			G_isSameValue = 0;
		}
		
    }
}

ISR(TIMER0_OVF_vect)
{
	G_isSameValue = 1;
	TCNT0 = 162;
}

