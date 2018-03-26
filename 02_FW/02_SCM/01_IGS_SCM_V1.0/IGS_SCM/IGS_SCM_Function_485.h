/*
 * SCM_Function_485.h
 *
 * Created: 2012-12-07 오후 10:03:48
 *  Author: MinyoungEom
 */ 


#ifndef SCM_FUNCTION_485_H_
#define SCM_FUNCTION_485_H_

void SCM485F_USART0Init()
{
	uint32_t ubrr = MYUBRR;
	UBRR0H = (uint8_t)(ubrr >>8);
	UBRR0L = (uint8_t)(ubrr);

	UCSR0C=(0<<UMSEL0)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B=(1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);
}



void SCM485F_RxCompleteTimerInit()
{
	TCCR0 = (0<<CS02)|(0<<CS01)|(0<<CS00);
	TIMSK |= (1<<TOIE0);
	TCNT0 = 0;
}

//initialize buffer
void SCM485F_BufferInit(volatile u8buf *buf)
{
	buf->index = 0;
	buf->length = 0;
}

uint8_t SCM485F_OneByteWrite_485(volatile u8buf *buf, uint8_t u8data)
{
	
	if(buf->index < MAX_BUF_SIZE)
	{
		buf->buffer[buf->index] = u8data;
		buf->index++;
		return WRITE_OK;
	}
	else 
		return WRITE_FAIL;
}

uint8_t SCM485F_OneByteRead_485(volatile u8buf *buf, volatile uint8_t *u8data)
{

	if(buf->index < buf->length )
	{
		*u8data=buf->buffer[buf->index];
		buf->index++;
	}

	if(buf->index == buf->length)
		return 1;
	else return 0;
}

void SCM485F_packetBufInit()
{
	uint16_t i;
	G_485Packet.stx = 0;
	G_485Packet.scm_id = 0;
	G_485Packet.data_type = 0;
	for(i=0; i<MAX_BUF_SIZE; i++)
		G_485Packet.data[i] = 0;
	G_485Packet.crc16 = 0;
}

uint16_t SCM485F_checkCRC16(volatile uint8_t *crcMessage, uint16_t length)
{
	uint16_t crc;

	crc = crcsum(crcMessage, length,  CRC_INIT);
	return crc;
}

uint8_t SCM485F_getRxPacket()
{
	uint16_t i;
	uint16_t crc16;
	SCM485F_packetBufInit();
	
	G_485Packet.stx = (uint32_t)G_rxBuf485.buffer[0];
	G_485Packet.stx = (G_485Packet.stx << 8) | (uint32_t)G_rxBuf485.buffer[1];
	G_485Packet.stx = (G_485Packet.stx << 16) | (uint32_t)G_rxBuf485.buffer[2];
	
	G_485Packet.scm_id = G_rxBuf485.buffer[3];
	G_485Packet.data_type = G_rxBuf485.buffer[4];
	G_485Packet.data_length = (uint16_t)G_rxBuf485.buffer[5];
	G_485Packet.data_length = (G_485Packet.data_length << 8) | (uint16_t)G_rxBuf485.buffer[6];
	
	if (G_485Packet.data_length > MAX_BUF_SIZE)
	{
		G_485Packet.data_length = MAX_BUF_SIZE;
	}
	for(i=0; i<G_485Packet.data_length; i++)
	G_485Packet.data[i] = G_rxBuf485.buffer[7+i];
	
	G_485Packet.crc16 = (uint16_t)G_rxBuf485.buffer[7+G_485Packet.data_length];
	G_485Packet.crc16 = (G_485Packet.crc16 << 8) | (uint16_t)G_rxBuf485.buffer[7+G_485Packet.data_length +1];
	
	crc16 = crcsum(G_rxBuf485.buffer+3, G_485Packet.data_length+4,  CRC_INIT);
	if(G_485Packet.stx != 0x000000)
		return RS485_RX_STX_ERROR;
		
		if(G_485Packet.crc16 != crc16)
		return RS485_RX_CRC_ERROR;
	
	if(G_485Packet.scm_id != G_idDipValue)
		return RS485_RX_INVALID_ID;
	


	return RS485_RX_OK;
}

void SCM485F_makeTxPacket(uint8_t data_type, uint16_t data_length, volatile uint8_t *data)
{
	G_txBuf485.buffer[0] = 0x00;
	G_txBuf485.buffer[1] = 0x00;
	G_txBuf485.buffer[2] = 0x00;
	
	G_txBuf485.buffer[3] = G_idDipValue;
	G_txBuf485.buffer[4] = data_type;
	
	G_txBuf485.buffer[5] = (uint8_t)(data_length>>8);
	G_txBuf485.buffer[6] = (uint8_t)(data_length & 0x00FF);
	
	if (data_length >= MAX_BUF_SIZE){
		data_length = MAX_BUF_SIZE;
	}
	if(data_length >0){
		for(uint16_t i = 0; i<data_length; i++)
			G_txBuf485.buffer[7+i] = data[i];
	}


	G_txBuf485.length = 7 + data_length+4;
	uint16_t crcLength = data_length + 4;
	uint16_t crc = crcsum(G_txBuf485.buffer+3, crcLength,  CRC_INIT);
	
	G_txBuf485.buffer[data_length + 7] = (uint8_t)(crc >> 8);
	G_txBuf485.buffer[data_length + 8] = (uint8_t)(crc & 0x00ff);
	G_txBuf485.buffer[data_length + 9] = 0;
	G_txBuf485.buffer[data_length + 10] = 0;
	
	
	//TIMSK &= ~(1<<TOIE2);
	UCSR0B &= ~(1<<RXCIE0);
	PORTE &= ~(1<<PE2);//PORTE = (0<<PE7)|(0<<PE6)|(0<<PE5)|(0<<PE4)|(0<<PE3)|(0<<PE2)|(0<<PE1)|(0<<PE0); // Tx : PE2 low / Rx : PE2 hi
	UCSR0B |=  (1<<UDRIE0);
}
#endif /*SCM_FUNCTION_485_H_ */