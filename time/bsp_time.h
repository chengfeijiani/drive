#ifndef _BSP_TIME_H
#define _BSP_TIME_H

typedef enum
{
    TIMER_TYPE_HANDWARE = 0X01, /* Ӳ�� timer ��ʵʱ�Խ�ǿ����ʱ���Ƚϸߣ�ռ���ж�ʱ�� */
    TIMER_TYPE_SOFTWART ,       /* ��� timer ��ʵʱ�Խϲ��ʱ���Ƚϲ��ռ���ж�ʱ�� */
} BSP_TIMER_TYPE;

struct BSP_TIMER
{
    void (*timeout_callback)(void *user_data);  /* �ص����� */
    BSP_TIMER_TYPE type;                        /* timer ���� */
    uint8_t start           :1;                 /* ��ʼ��־λ */
    uint8_t timeout_flag    :1;                 /* ʱ�䵽���־λ */
    uint8_t                 :0;
    uint16_t period;                            /* �û�ָ��timer��ִ�д��� */
    uint16_t period_temp;                       /* �ݴ�ִ�д��� */
    uint32_t timeout;                           /* ��Ҫ������ʱ�䣬��λΪ ms */
    uint32_t time_temp;                         /* ���ڼ����ı��� */

    void *user_data;                            /* �û����� */

    struct BSP_TIMER    *next;   
}




#endif
