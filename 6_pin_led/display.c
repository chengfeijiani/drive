void dis_C(int16_t num) // 400us
{
    static uint8_t i, num1, num2;
    static uint16_t cnt;
    cnt++;
	
    if (cnt >= 2000)
    {
        cnt = 0;
    }
    if (num < 0)
    {
        num2 =  - num;
    }
    else
    {
        num2 = num / 10;
        num1 = num % 10;
    }
    i++;
    if (i >= 20)
        i = 1;
    LCD_ALL_IN;
    if (i == 1)
    {
        if (num <= -1 || num >= 50)
        {
            LCD_ZHONG1_MODE;
            LCD_ZHONG1;
        }
        else
        {
            LCD_XIA1_MODE;
            LCD_XIA1;
        }
    }
    else if (i == 2)
    {
        if (num <= -1 || num >= 50)
        {
            LCD_ZHONG2_MODE;
            LCD_ZHONG2;
        }
        else
        {
//            LCD_YOUSHANG1_MODE;
//            LCD_YOUSHANG1;
        }
    }
    else if (i == 3)
    {
        if (num <= -1 || num >= 50)
        {
            LCD_ZHONG3_MODE;
            LCD_ZHONG3;
            i = 0;
            return;
        }
        else
        {
            LCD_YOUXIA1_MODE;
            LCD_YOUXIA1;
        }

    }
    else if (i == 4)
    {
        LCD_ZHONG1_MODE;
        LCD_ZHONG1;
    }
    else if (i == 5)
    {
        if (num >= 18)
        {
            if (cnt < 1000)
            {
                LCD_OP1_MODE;
                LCD_OP1;
            }
        }
        else
        {
            LCD_OP1_MODE;
            LCD_OP1;
        }
    }
    /* num1 */
    else if (i == 6) //上
    {
        if (num1 != 1 && num1 != 4 && num1 != 7)
        {
            LCD_SHANG2_MODE;
        }
    }
    else if (i == 7) //右上
    {
        if (num1 != 5 && num1 != 7 && num1 != 9 && num1 != 1 && num1 != 3 && num1 != 4)
        {
            LCD_YOUSHANG2_MODE;
        }
    }
    else if (i == 8) //右下
    {
        if (num1 != 3 && num1 != 1 && num1 != 7 && num1 != 2)
        {
            LCD_YOUXIA2_MODE;
        }
    }
    else if (i == 9) //下
    {
        if (num1 != 4 && num1 != 1)
        {
            LCD_XIA2_MODE;
        }
    }
    else if (i == 10) //左下
    {
        if (num1 != 5 && num1 != 6)
        {
            LCD_ZUOXIA2_MODE;
        }
    }
    else if (i == 11) //左上
    {
        if (num1 != 2)
        {
            LCD_ZUOSHANG2_MODE;
        }
    }
    else if (i == 12) //中
    {
        if (num1 != 1 && num1 != 7 && num1 != 0)
        {
            LCD_ZHONG2_MODE;
        }
    }

    /* num1 */
    else if (i == 13) //上
    {
        if (num2 != 1 && num2 != 4 && num2 != 7)
        {
            LCD_SHANG3_MODE;
        }
    }
    else if (i == 14) //右上
    {
        if (num2 != 5 && num2 != 7 && num2 != 9 && num2 != 1 && num2 != 3 && num2 != 4)
        {
            LCD_YOUSHANG3_MODE;
        }
    }
    else if (i == 15) //右下
    {
        if (num2 != 3 && num2 != 1 && num2 != 7 && num2 != 2)
        {
            LCD_YOUXIA3_MODE;
        }
    }
    else if (i == 16) //下
    {
        if (num2 != 4 && num2 != 1)
        {
            LCD_XIA3_MODE;
        }
    }
    else if (i == 17) //左下
    {
        if (num2 != 5 && num2 != 6)
        {
            LCD_ZUOXIA3_MODE;
        }
    }
    else if (i == 18) //左上
    {
        if (num2 != 2)
        {
            LCD_ZUOSHANG3_MODE;
        }
    }
    else if (i == 19) //中
    {
        if (num2 != 1 && num2 != 7 && num2 != 0)
        {
            LCD_ZHONG3_MODE;
        }
    }
}