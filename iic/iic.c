/*
 * ������IIC�������ڰ�˫����ͨѶ��ʽ�����������������Ҫ��ߵĳ��ϲ��ʺ�ʹ��
 * ����Э��㣺IIC��Э�鶨����ͨѶ�� ��ʼ �� ֹͣ�ź� ��������Ч�ԡ���Ӧ���ٲá�ʱ��ͬ���͵�ַ�㲥�ȡ�
 * ����㣺
        SCL:ʱ���������վ��շ�ͬ����ʱ���ź�ʼ�������豸����
        SDA:�����ߣ�˫���У�
        ע�⣺1��IIC�豸�ڿ���״̬�£������߻���ָ���̬��������������������ɸߵ�ƽ
        ���е��豸������Ϊ�����豸��
        �������ʣ���׼ģʽ��������Ϊ100kbit/s (����Ϊ10us),����ģʽΪ400kbit/s(����Ϊ2.5us)
 */



#define SDA_HIGH    /* �������Ÿ� */
#define SDA_LOW     /* �������ŵ� */
#define SCL_HIGH    /* ʱ�����Ÿ� */
#define SCL_LOW     /* ʱ�����ŵ� */
#define SDA_IN      /* ����SDAΪ����ģʽ */
#define SDA_OUT     /* ����SDAΪ���ģʽ */
#define READ_SDA    /* ��ȡSDA��ƽ */


static void delay_1us(uint32_t num)
{
    for(int i=0;i<num;i++)
    {
        nop();
    }
}
/* ��ʼ�ź� */
void iic_start(void)
{
    SDA_OUT;
    SDA_HIGH;
    SCL_HIGH;
    delay_1us(2);
    SDA_LOW;
    delay_1us(2);
    SCL_LOW;
}

/* ֹͣ�ź� */
void iic_stop(void)
{
    SDA_OUT;
    SDA_LOW;
    SCL_HIGH;
    delay_1us(2);
    SDA_HIGH;
    delay_1us(2);
    SCL_LOW;
}

/* ����Ӧ���ź� */
void iic_ask(void)
{
    SDA_OUT;
    SCL_LOW;
    SDA_HIGH;
    delay_1us(2);
    SCL_HIGH;
    delay_1us(2);
    SCL_LOW;
    SDA_HIGH;
}

/* ������Ӧ���ź� */
void iic_not_ask(void)
{
    SDA_OUT;
    SCL_LOW;
    SDA_LOW;
    delay_1us(2);
    SCL_HIGH;
    delay_1us(2);
    SDA_HIGH;
}

/* Ӧ���ź�
 * ���� 1Ӧ��ʧ�� 0Ӧ��ɹ�
 */
uint8_t iic_wait_ask(void)
{
    static uint8_t time;
    SDA_IN;
    SCL_LOW;
    delay_1us(2);
    SCL_HIGH;
    while(READ_SDA)
    {
        time++;
        if(time > 250)
        {
            iic_stop();
            return 1;
        }
    }
    return 0;
}

void iic_send_byte(uint8_t data)
{
    uint8_t i;
    SDA_OUT;
    SCL_LOW;
    for(i=0; i<8; i++)
    {
        if((data & 0x80) == 0x80)
        {
            SDA_HIGH;
        }
        else
        {
            SDA_LOW;
        }
        data = data << 1;
        SCL_HIGH;
        delay_1us(2);
        SCL_LOW;
        delay_1us(2);
    }
}

uint8_t iic_read_btye(uint8_t *data,uint8_t ask)
{
    uint8_t i;
    for(i=0; i<8; i++)
    {
        SCL_LOW;
        delay_1us(2);
        SCL_HIGH;
        data << 1;
        if(READ_SDA)data++;
        delay_1us(2);
    }
    if(ask == 0)
    {
        iic_not_ask();
    }
    if(ask == 1)
    {
        iic_ask();
    }
}