#include "tm1621.h"

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < 626; i++)
    {
        for (j = 0; j < ms; j++)
        {

        }
    }
}

void delay_us(unsigned int us)
{
    unsigned int i;
    for (i = 0; i < us; i++)
    {

    }
}


void Enable_tm1621(void)
{
	HT_CS_LOW;
    HT_WR_HIGH;
	delay_us(10);
	HT_WR_LOW;
	delay_us(10);
}
/* 从高位写入 */
void Write_bit_to_tm1621_H(unsigned char nbit, unsigned char len)
{
	unsigned char i;
	for(i = 0; i < len; i++)
	{
		HT_WR_LOW;
		delay_us(10);
		if (nbit & 0x80)
        {
            HT_DATA_HIGH;
        }
        else
        {
            HT_DATA_LOW;
        }
		HT_WR_HIGH;
		delay_us(10);
		nbit <<= 1;
	}
}

/* 从地位写入 */
void Write_bit_to_tm1621_L(unsigned char nbit, unsigned char len)
{
	unsigned char i;
	for(i = 0; i < len; i++)
	{
		HT_WR_LOW;
		delay_us(10);
		if (nbit & 0x01)
        {
            HT_DATA_HIGH;
        }
        else
        {
            HT_DATA_LOW;
        }
		HT_WR_HIGH;
		delay_us(10);
		nbit >>= 1;
	}
}


void Write_com_to_tm1621(unsigned char com)
{
	Enable_tm1621();
	Write_bit_to_tm1621_H(0x80, 4);
	Write_bit_to_tm1621_H(com, 8);
	HT_WR_HIGH;
	delay_us(10);
	HT_CS_HIGH;
	delay_us(10);
	HT_DATA_HIGH;
}

void Reset_tm1621(void)
{
	 HT_WR_HIGH;
     delay_us(10);
     HT_CS_HIGH;
     delay_us(10);
     HT_DATA_HIGH;
}

void Setup_tm1621(void)
{
	Write_com_to_tm1621(BIAS);
	Write_com_to_tm1621(RC256K);
	Write_com_to_tm1621(WDTDIS);		 //禁止看门狗
	Write_com_to_tm1621(SYSEN);
	Write_com_to_tm1621(LCDON);
	
}

void Close_tm1621(void)
{
	Write_com_to_tm1621(SYSDIS);
	Write_com_to_tm1621(LCDOFF);
}

void Send_byte_to_tm1621(unsigned char addr, unsigned char byte)
{
	HT_CS_LOW;

	delay_us(10);
	Write_bit_to_tm1621_H(0xA0,3);
	Write_bit_to_tm1621_H(addr<<2,6);
	Write_bit_to_tm1621_L(byte,4);
	HT_CS_HIGH;
	delay_us(10);
}

void Send_string_to_tm1621(unsigned char addr, unsigned char *buf, unsigned char len)
{
	unsigned char i;
	HT_CS_LOW;
	Write_bit_to_tm1621_H(0xA0,3);
	Write_bit_to_tm1621_H(addr<<2,6);
	for(i = 0; i < len; i++)
	{
		Write_bit_to_tm1621_L(*buf,8);
		buf++;
	}
	HT_CS_HIGH;
}

