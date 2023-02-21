#ifndef _TM1621_H
#define _TM1621_H
#include "h\SC92F837X_C.h"

//***************************HT1621常数定义*****************************
#define    RAMSIZE     16             //RAM区16字节
#define    BIAS        0x52           //1/3偏压,4个公共口
#define    RC256K      0x30           //片内RC振荡器
#define    SYSEN       0x02           //打开系统振荡器
#define    SYSDIS      0x00           //关闭系统振荡器河LCD偏压发生器
#define    LCDON       0x06           //打开LCD偏压发生器
#define    LCDOFF      0x04           //关闭LCD偏压发生器 
#define 	WDTDIS   0x0a     //禁止看门狗

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