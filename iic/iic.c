/*
 * 描述：IIC总线属于半双工的通讯方式，抗干扰能力差，带宽要求高的场合不适合使用
 * 总线协议层：IIC的协议定义了通讯的 起始 和 停止信号 、数据有效性、响应、仲裁、时钟同步和地址广播等。
 * 物理层：
        SCL:时钟线用于收据收发同步，时钟信号始终由主设备发送
        SDA:数据线（双向串行）
        注意：1、IIC设备在空闲状态下，数据线会呈现高阻态，由上拉电阻把总线拉成高电平
        所有的设备都可以为主控设备，
        传输速率：标准模式传输速率为100kbit/s (脉冲为10us),快速模式为400kbit/s(脉冲为2.5us)
 */



#define SDA_HIGH    /* 数据引脚高 */
#define SDA_LOW     /* 数据引脚低 */
#define SCL_HIGH    /* 时钟引脚高 */
#define SCL_LOW     /* 时钟引脚低 */
#define SDA_IN      /* 设置SDA为输入模式 */
#define SDA_OUT     /* 设置SDA为输出模式 */
#define READ_SDA    /* 读取SDA电平 */


static void delay_1us(uint32_t num)
{
    for(int i=0;i<num;i++)
    {
        nop();
    }
}
/* 起始信号 */
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

/* 停止信号 */
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

/* 产生应答信号 */
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

/* 不产生应答信号 */
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

/* 应答信号
 * 返回 1应答失败 0应答成功
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