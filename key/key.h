#ifndef _KEY_H
#define _KEY_H
#define KEY_TEST                            0

/* ���������� */
#define KEY_CLICK_EVENT_WHEN_DBLCLICK       0       /* �趨��˫������ʱ�Ƿ񻹴��������¼���1��˫��ʱ���ɴ��������¼���0��˫��ʱ�����������¼������ᴥ��˫���¼� */
#define KEY_DBLCLICK_PRESS_VALID            0       /* ����˫��ʱ��ѡ��ڶ��ΰ���ʱ���������¼������ǵڶ��ΰ���ʱ�ſ�������Ŵ����¼� */
                                                    /* 1���ڶ��ΰ���ʱ���������¼���0���ڶ��ΰ��²��ſ�������Ŵ����¼� */
#define KEY_LONG_PRESS_TIME                 FACTORY_FIRMWARE_BUTTON_TIME    /* �������ʱ�䣬��λ��ms */
#define KEY_DBLCLICK_TIME                   200     /* ˫�����ʱ�䡣��λ��ms */

/* �ǳ��������� */
#define KEY_USER_DEFINE_PRESS_TIME          0       /* �û������ÿ�������趨��ͬ�ĳ�������ʱ�䣬Ϊ 0 ʱ��ʾȫ�������ĳ�������ʱ��ʹ�� KEY_LONG_PRESS_TIME ���� */
                                                    /* Ϊ 1 ʱ��ʾ�û��뵥��Ϊÿ���������ó����¼��Ĵ���ʱ�� */
#define KEY_LONG_PRESS_CONTINU_TRIG_TIME    0       /* һֱ���������� KEY_LONG_PRESS_TIME ����λʱ��󣬴˲�����ʾ�����û��������°���ÿ��һ��ʱ�䴥��һ�� KEY_LONG_PRESS_HOLD �¼� */
                                                    /* Ϊ 0 ʱ��ʾ�����û�һֱ���°��������೤ʱ�䣬��ֻ����һ�� KEY_LONG_PRESS �¼���ֱ���û��ſ�����Ϊֹ�����ܼ����¸��¼��Ĳ��� */
#define KEY_CONSECUTIVE_READ_TIME           4       /* ������ȡ��ֵ�������˲�������ʵ�ַ�����ʽ�İ������������ֵ��8 */
                                                    /* ��ֵ��Ӱ���ȡ���ռ�ֵ�ʹ����¼���ʱ�� */
                                                    /* �����ĵ����¼�����ʱ�� = KEY_CONSECUTIVE_READ_TIME * ����BSP_Key_Handler�����Ĳ���ֵ����λ��ms */
                                                    /* ���������¼���������ʱ����� */

typedef enum
{
    KEY_PRESS_LOW = 0X00,
    KEY_PRESS_HIGH = 0XFF
} KEY_LEVEL;

typedef enum
{
    KEY_UP = 0,
    KEY_DOWN
} KEY_STATE;

typedef enum 
{
    KEY_PRESS           = 0,        /* �հ��£�ÿ�������¼����ᴥ�����¼����Ƿ�Ҫ������¼����û�ѡ���Ƿ�ע����¼��Ļص������� */
    KEY_CLICK           = 1,        /* ���� */
    KEY_DBLCLICK        = 2,        /* ˫�� */
    KEY_LONG_PRESS      = 3,        /* ���� */
    KEY_LONG_PRESS_HOLD = 4,        /* �������� */
    KEY_EVENT_NUM,                  /* �¼����� */
    KEY_NONE_EVENT                  /* Ĭ�����¼� */

} KEY_EVENT;

typedef void (*Key_EventCallback)(uint8_t id, KEY_EVENT  event);

struct BSP_KEY
{
    KEY_EVENT event;                /* �����¼���¼ */
    KEY_LEVEL press_level;          /* ��¼���°�����ƽ�ź� */
    KEY_STATE  key_state;      /* ��¼��ǰ����״̬�����»��� */

    uint8_t id;
    uint8_t state;                  /* ״̬�� */
    uint8_t continuous_value;       /* ���������������棬һ��8λ��ȣ����ڴ�ȡһ��������ͬʱ�̵İ���״̬�������8�� */
    uint16_t tick;                  /* ���ڼ�ʱ����ʱ���� */
    #if (KEY_USER_DEFINE_PRESS_TIME)
    uint16_t press_time;            /* �������ʱ�� */
    #endif
    
    uint8_t (*GetState)(void);                      /* ������ƽ״̬��ȡ��������Ҫ�û�ʵ�� */
    Key_EventCallback  Callback[ KEY_EVENT_NUM ];   /* �����ص��������ɰ����¼���������Ҫ�û�ʵ�� */
    
    struct BSP_KEY *next;        /* �򵥵ĵ������� */

};


#if (KEY_USER_DEFINE_PRESS_TIME)
int8_t BSP_Key_Init(struct BSP_KEY *key, uint8_t id, uint8_t (*KEY_GetState)(void), KEY_LEVEL press_level, uint16_t press_time);
#else
int8_t BSP_Key_Init(struct BSP_KEY *key, uint8_t id, uint8_t (*KEY_GetState)(void), KEY_LEVEL press_level);
#endif
int8_t BSP_Key_Start(struct BSP_KEY *key);
void   BSP_Key_Register(struct BSP_KEY *key, KEY_EVENT event, Key_EventCallback callback);
void   BSP_Key_Handler(uint8_t ms);

#if (KEY_TEST)
void Key_Test(void);
#endif


#endif