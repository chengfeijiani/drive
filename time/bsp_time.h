#ifndef _BSP_TIME_H
#define _BSP_TIME_H

typedef enum
{
    TIMER_TYPE_HANDWARE = 0X01, /* 硬件 timer ，实时性较强，定时精度较高，占用中断时间 */
    TIMER_TYPE_SOFTWART ,       /* 软件 timer ，实时性较差，定时精度较差，不占用中断时间 */
} BSP_TIMER_TYPE;

struct BSP_TIMER
{
    void (*timeout_callback)(void *user_data);  /* 回调函数 */
    BSP_TIMER_TYPE type;                        /* timer 类型 */
    uint8_t start           :1;                 /* 开始标志位 */
    uint8_t timeout_flag    :1;                 /* 时间到达标志位 */
    uint8_t                 :0;
    uint16_t period;                            /* 用户指定timer的执行次数 */
    uint16_t period_temp;                       /* 暂存执行次数 */
    uint32_t timeout;                           /* 需要计数的时间，单位为 ms */
    uint32_t time_temp;                         /* 用于计数的变量 */

    void *user_data;                            /* 用户数据 */

    struct BSP_TIMER    *next;   
}




#endif
