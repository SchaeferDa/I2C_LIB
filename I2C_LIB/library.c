/*
 * library.c
 *
 * Created: 14.02.2019 14:14:36
 * Author:	Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define SCL_DDR DDRD
#define SCL_PORT PORTD
#define SCL_PIN PIND
#define SCL_MASK 3

#define SCL_HIGH() (SCL_DDR = (SCL_DDR & ~(1 << SCL_MASK)))
#define SCL_LOW() (SCL_DDR = (SCL_DDR | (1 << SCL_MASK)))

#define SDA_DDR DDRD
#define SDA_PORT PORTD
#define SDA_PIN PIND
#define SDA_MASK 2

#define SDA_HIGH() (SDA_DDR = (SDA_DDR & ~(1 << SDA_MASK)))
#define SDA_LOW() (SDA_DDR = (SDA_DDR | (1 << SDA_MASK)))
#define SDA_READ() ((SDA_PIN & (1 << SDA_MASK)) == (1 << SDA_MASK))

double delaytime = 5;
char delayunit = 'u';

typedef enum{FALSE, TRUE} boolean;
	
void sendBit(char bit);

/************************************************************************/
/* unit: u for µs, m for ms                                             */
/************************************************************************/
void initI2C(double time, char unit)
{
	delaytime = time;
	delayunit = unit;
	
	SCL_HIGH();
	SDA_HIGH();
}	

void delay_I2C()
{
	switch(delayunit)
	{
		case 'u':
			_delay_us(delaytime);
			break;
			
		case 'm':
			_delay_ms(delaytime);
			break;
	}
}

void sendStartCondition()
{
	SCL_HIGH();
	SDA_HIGH();
	
	delay_I2C();
	
	SDA_LOW();
	
	delay_I2C();
	
	SCL_LOW();
}

void sendStopCondition()
{
	SCL_LOW();
	SDA_LOW();
	
	delay_I2C();
	
	SCL_HIGH();
	
	delay_I2C();
	
	SDA_HIGH();
}

boolean sendByte(char byte)
{
	SCL_LOW();
	
	for(int i = 0; i < 8; i++)
	{
		delay_I2C();
		
		sendBit((byte & 0b10000000) >> 7);
		
		byte = byte << 1;
		
		delay_I2C();
		
		SCL_HIGH();
		
		delay_I2C();
		
		SCL_LOW();
		SDA_LOW();
	}
	
	SDA_HIGH();
		 
	delay_I2C();
		 
	SCL_HIGH();
		 
	delay_I2C();
		 
	boolean ack = FALSE;
		 
	if(SDA_READ() == FALSE)
		ack = TRUE;
		 
	SCL_LOW();
		 
	delay_I2C();

	return ack;
}

char readByte(char slaveAddress)
{
	char byte = 0b00000000;
	
	//force read mode
	slaveAddress |= 0b00000001;
	
	SCL_LOW();
	
	// write address to slave
	if(sendByte(slaveAddress))
	{
		SCL_LOW();
		SDA_HIGH();
		
		// read byte from slave
		for(int i = 7; i >= 0; i--)
		{
			delay_I2C();
			
			SCL_HIGH();
			
			delay_I2C();
			
			byte |= (SDA_READ() << i);
			
			SCL_LOW();
		}
	}
	
	return byte;
}

void sendBit(char bit)
{
	if(bit == 0)
	{
		SDA_LOW();
	}
	else if (bit == 1)
	{
		SDA_HIGH();
	}
}