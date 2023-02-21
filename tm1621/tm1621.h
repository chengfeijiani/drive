#ifndef _TM1621_H
#define _TM1621_H
#include "h\SC92F837X_C.h"

//***************************HT1621��������*****************************
#define    RAMSIZE     16             //RAM��16�ֽ�
#define    BIAS        0x52           //1/3ƫѹ,4��������
#define    RC256K      0x30           //Ƭ��RC����
#define    SYSEN       0x02           //��ϵͳ����
#define    SYSDIS      0x00           //�ر�ϵͳ������LCDƫѹ������
#define    LCDON       0x06           //��LCDƫѹ������
#define    LCDOFF      0x04           //�ر�LCDƫѹ������ 
#define 	WDTDIS   0x0a     //��ֹ���Ź�

//P11
#define HT_DATA_HIGH    P14 = 1		     
#define HT_DATA_LOW		P14 = 0			  
//P12
#define HT_WR_HIGH		P15 = 1			
#define HT_WR_LOW		P15 = 0				   
//P13
#define HT_CS_HIGH		P27 = 1	
#define HT_CS_LOW		P27 = 0		

void Setup_tm1621(void);
void Send_byte_to_tm1621(unsigned char addr, unsigned char byte);
void Send_string_to_tm1621(unsigned char addr, unsigned char *buf, unsigned char len);
#endif