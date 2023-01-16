#include "bsp_time.h"

#define TIMER_ONE_SHOT      0x04
#define TIMER_PERIODIC      0x08

static BSP_TIMER *_timer_head;
static _timer_add(struct BSP_TIMER *timer);

void bso_init(struct BSP_TIMER *timer,
              void (*timeout_callback)(void *user_data),
              uint32_t timeout,
              uint16_t period,  
              BSP_TIMER_TYPE timer_type)
{
    timer->period  = period;
    timer->timeout = timeout;
    timer->type    = timer_type;
    timer->timeout_callback = timeout_callback;

    timer->timer_temp = 0;
    timer->period_temp = period;
    if(period == 0)
        timer->type |= TIMER_ONE_SHOT;
    else
        timer->type |= TIMER_PERIODIC;
    _timer_add(timer);
}

/**
 * @brief  链接用户数据
 * @note   可选项，主要用于回调函数传递用户的数据
 * @param[in]  timer: timer 对象
 * @param[in]  user_data: 用户数据
 * @retval None
 */
void bsp_timer_link_user_data(struct BSP_TIMER *timer, void *user_data)
{
    timer->user_data = user_data;
}

/**
 * @brief  开启 timer
 * @note   开启后 timer 会继承上一个状态继续运转
 * @param[in]  timer: timer 对象
 * @retval None
 */
 void bsp_timer_start(struct BSP_TIMER *timer)
 {
    timer->start = 1;
 }
 
 /**
 * @brief  重新开启 timer
 * @note   重新开启会将 timer 的参数复位到初始状态后运转，而不必再次调用 BSP_Timer_Init
 * @param[in]  timer: timer 对象
 * @retval None
 */
 void bsp_timer_restart(struct BSP_TIMER *timer)
 {
    timer->start = 0;
    timer->time_temp = 0;
    timer->period = timer->period_temp;
    timer->start = 1;
 }

 /**
 * @brief  暂停 timer 运行
 * @note   只是暂停， timer 还在链表上，回复只需调用 BSP_Timer_Start 或 BSP_Timer_Restart
 * @param[in]  timer: timer 对象
 * @retval None
 */
void bsp_timer_pause(struct BSP_TIMER *timer)
{
    timer->start = 0;
    timer->time_temp = 0;

    return;
}

/**
 * @brief  分离 timer
 * @note   分离后，链表不再有该 timer ，恢复需要重新调用 BSP_Timer_Init
 * @param[in]  timer: timer 对象
 * @retval None
 */
void bsp_timer_detach(struct BSP_TIMER *timer)
{
    struct BSP_TIMER **now_target;
    struct BSP_TIMER *entry;

    for (now_target = &_timer_head; *now_target; )
    {
        entry = *now_target;

        if (entry == timer)
        {
            *now_target = entry->next;
            return;
        }
        else 
            now_target = &entry->next;         
    }

    return;
}

/**
 * @brief  timer 处理函数
 * @note   必须被循环调用，建议放在中断函数内
 * @param[in]  ms: 被调用的间隔时间，单位 ms（推荐 1ms ）
 * @retval None
 */
void bsp_handle_handler(uint8_t ms)
{
    struct BSP_TIMER *timer;

    for (timer = _timer_head; timer != NULL; timer = timer->next) 
    {
        if (timer->start)
        {
            timer->time_temp += ms;
            if (timer->time_temp >= timer->timeout)
            {
                timer->time_temp = 0;

                if ((timer->type & TIMER_TYPE_HARDWARE) != 0)
                {
                    if (timer->Timeout_Callback)
                        timer->Timeout_Callback( timer->user_data );
                    
                    if ((timer->type & TIMER_ONE_SHOT) != 0)
                    {
                        --timer->period;
                        if (timer->period == 0)
                            BSP_Timer_Pause(timer);
                    }
                }
                else
                    timer->timeout_flag = 1;
            }
        }
    }
}

/**
 * @brief  软件定时器处理函数
 * @note   使用查询的标志位方式，若用户对 timer 初始化时选择了 TIMER_TYPE_SOFTWARE ，则必须被不断调用
 * @retval None
 */
void bsp_timer_soft_timer_task(void)
{
    struct BSP_TIMER *timer;

    for (timer = _timer_head; timer != NULL; timer = timer->next) 
    {
        if (timer->timeout_flag)
        {
            timer->timeout_flag = 0;
            
            if (timer->Timeout_Callback)
                timer->Timeout_Callback( timer->user_data );

            if ((timer->type & TIMER_ONE_SHOT) != 0)
            {
                --timer->period;
                if (timer->period == 0)
                    BSP_Timer_Pause(timer);
            }
        }
    }
}
/**
 * @brief  将定时器对象添加进管理链表
 * @note   
 * @param[in]  timer: timer 对象
 * @retval None
 */
static void _timer_add(struct BSP_TIMER *timer)
{
    struct BSP_TIMER *target;
    
    for (target = _timer_head; target != NULL; target = target->next)
    {
        if (target == timer)
            return;
    }

    timer->next = _timer_head;
    _timer_head  = timer;
}
