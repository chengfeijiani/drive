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
 * @brief  �����û�����
 * @note   ��ѡ���Ҫ���ڻص����������û�������
 * @param[in]  timer: timer ����
 * @param[in]  user_data: �û�����
 * @retval None
 */
void bsp_timer_link_user_data(struct BSP_TIMER *timer, void *user_data)
{
    timer->user_data = user_data;
}

/**
 * @brief  ���� timer
 * @note   ������ timer ��̳���һ��״̬������ת
 * @param[in]  timer: timer ����
 * @retval None
 */
 void bsp_timer_start(struct BSP_TIMER *timer)
 {
    timer->start = 1;
 }
 
 /**
 * @brief  ���¿��� timer
 * @note   ���¿����Ὣ timer �Ĳ�����λ����ʼ״̬����ת���������ٴε��� BSP_Timer_Init
 * @param[in]  timer: timer ����
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
 * @brief  ��ͣ timer ����
 * @note   ֻ����ͣ�� timer ���������ϣ��ظ�ֻ����� BSP_Timer_Start �� BSP_Timer_Restart
 * @param[in]  timer: timer ����
 * @retval None
 */
void bsp_timer_pause(struct BSP_TIMER *timer)
{
    timer->start = 0;
    timer->time_temp = 0;

    return;
}

/**
 * @brief  ���� timer
 * @note   ������������и� timer ���ָ���Ҫ���µ��� BSP_Timer_Init
 * @param[in]  timer: timer ����
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
 * @brief  timer ������
 * @note   ���뱻ѭ�����ã���������жϺ�����
 * @param[in]  ms: �����õļ��ʱ�䣬��λ ms���Ƽ� 1ms ��
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
 * @brief  �����ʱ��������
 * @note   ʹ�ò�ѯ�ı�־λ��ʽ�����û��� timer ��ʼ��ʱѡ���� TIMER_TYPE_SOFTWARE ������뱻���ϵ���
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
 * @brief  ����ʱ��������ӽ���������
 * @note   
 * @param[in]  timer: timer ����
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
