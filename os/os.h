#ifndef _OS_H
#define _OS_H


extern void S_QueueEmpty(unsigned char **Head, unsigned char **Tail, unsigned char *HBuff);
extern void S_QueueDataIn(unsigned char **Head, unsigned char **Tail, unsigned char *HBuff, unsigned short Len, unsigned char *HData, unsigned short DataLen);
extern unsigned char S_QueueDataOut(unsigned char **Head, unsigned char **Tail, unsigned char *HBuff, unsigned short Len, unsigned char *Data);
extern unsigned short S_QueueDataLen(unsigned char **Head, unsigned char **Tail, unsigned short Len);
 
extern void F_QueueEmpty(float **Head, float **Tail, float *HBuff);
extern void F_QueueDataIn(float **Head, float **Tail, float *HBuff, unsigned short Len, float *HData, unsigned short DataLen);
extern unsigned char F_QueueDataOut(float **Head, float **Tail, float *HBuff, unsigned short Len, float *Data);
extern unsigned short F_QueueDataLen(float **Head, float **Tail, unsigned short Len);

#define QueueEmpty(x)	   S_QueueEmpty((unsigned char**)&(x).Head,(unsigned char**)&(x).Tail,(unsigned char*)(x).Buff) 
#define QueueDataIn(x,y,z) S_QueueDataIn((unsigned char**)&(x).Head,(unsigned char**)&(x).Tail,(unsigned char*)(x).Buff,sizeof((x).Buff),(y),(z))
#define QueueDataOut(x,y)  S_QueueDataOut((unsigned char**)&(x).Head,(unsigned char**)&(x).Tail,(unsigned char*)(x).Buff,sizeof((x).Buff),(y)) 
#define QueueDataLen(x)	   S_QueueDataLen((unsigned char**)&(x).Head,(unsigned char**)&(x).Tail,sizeof((x).Buff))  

#define QueueEmptyF(x)	   F_QueueEmpty((float**)&(x).Head,(float**)&(x).Tail,(float*)(x).Buff) 
#define QueueDataInF(x,y,z) F_QueueDataIn((float**)&(x).Head,(float**)&(x).Tail,(float*)(x).Buff,sizeof((x).Buff),(y),(z))
#define QueueDataOutF(x,y)  F_QueueDataOut((float**)&(x).Head,(float**)&(x).Tail,(float*)(x).Buff,sizeof((x).Buff),(y)) 
#define QueueDataLenF(x)	   F_QueueDataLen((float**)&(x).Head,(float**)&(x).Tail,sizeof((x).Buff))  
/* ���нṹ�嶨��,���岻ͬ��С�Ķ��� */
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[1+1];}    Queue1;
typedef struct
{
	unsigned char *Head; 
	unsigned char *Tail; 
	unsigned char Buff[4+1];
}Queue4;

typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[8+1];}    Queue8;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[16+1];}   Queue16; 
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[32+1];}   Queue32;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[64+1];}   Queue64;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[90+1];}   Queue90;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[120+1];}  Queue120;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[340+1];}  Queue340;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[745+1];}  Queue745;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[128+1];}  Queue128;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[248+1];}  Queue248;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[256+1];}  Queue256;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[512+1];}  Queue512;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[1024+1];} Queue1K;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[2048+1];} Queue2K;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[5120+1];} Queue5K;
typedef struct{unsigned char *Head; unsigned char *Tail; unsigned char Buff[10240+1];} Queue10K;

typedef struct{float *Head; float *Tail; float Buff[256+1];}   Queue64f;

typedef enum
{
	CPU_ENTER_CRITICAL,		//CPU�����ٽ�
	CPU_EXIT_CRITICAL,		//CPU�˳��ٽ�
}CPU_EA_TYPEDEF;

//����һ��CPU�жϿ��ƻص�����ָ��,����CPUInterrupt_CallBack_t,
typedef void (*CPUInterrupt_CallBack_t)(CPU_EA_TYPEDEF cmd,unsigned char *pSta);


//ϵͳ����ID
typedef enum
{
	OS_TASK1,
	OS_TASK2,
	OS_TASK3,
	OS_TASK4,
	OS_TASK5,
	OS_TASK6,
	OS_TASK7,
	OS_TASK8,
	OS_TASK_SUM	
}OS_TaskIDTypeDef;


//ϵͳ��������״̬,��ʱû�õ�
typedef enum
{
	OS_SLEEP,			//��������
	OS_RUN=!OS_SLEEP	//��������
}OS_TaskStatusTypeDef;

//ϵͳ����ṹ��
typedef struct
{
	void (*task)(void);				//������ָ��
	OS_TaskStatusTypeDef RunFlag;		//��������״̬
	unsigned short	RunPeriod;			//����Ƶ��
	unsigned short RunTimer;			//�����ʱ��
}OS_TaskTypeDef;


/*	�������� */ 
/*******************************************************************************/
void OS_CPUInterruptCBSRegister(CPUInterrupt_CallBack_t pCPUInterruptCtrlCBS);
void OS_ClockInterruptHandle(void);
void OS_TaskInit(void);
void OS_CreatTask(unsigned char ID, void (*proc)(void), unsigned short TimeDly, OS_TaskStatusTypeDef flag);
void OS_Start(void);
void OS_ClockInterruptHandle(void);
void OS_TaskGetUp(OS_TaskIDTypeDef taskID);	
void OS_TaskSleep(OS_TaskIDTypeDef taskID);


#endif



