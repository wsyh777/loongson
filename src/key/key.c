/*
 * key.c
 *
 * created: 2024/3/1
 *  author:
 */
#include "ls1x_gpio.h"
#include "key.h"
#include "ls1x_latimer.h"

/*******************************************************************
* ������ : KEY_Init
* ����   : ��ʼ������
* ����   :
* ���   : ��
* ����   : ��
* ע��   :
********************************************************************/
void KEY_Init(void)
{
    gpio_set_direction(KEY_SW3, GPIO_Mode_In);// 1������� 0������
    gpio_set_direction(KEY_SW2, GPIO_Mode_In);// 1������� 0������

}

/*******************************************************************
* ������ : KEY_Scan
* ����   : ����ɨ��
* ����   :mode:0������֧����������1����֧��������
* ����   : 0û�а������£�1:KEY_SW2���£�2:SW2����
* ע��   :
********************************************************************/
unsigned char KEY_Scan(unsigned char mode)
{
    static unsigned char key_up = 1; // ���徲̬���� key_up�����ڸ��ٰ���״̬��Ĭ��Ϊ��������״̬

    if (mode)
    {
        key_up = 1; // ��� mode Ϊ�棬���������� key_up Ϊ��������״̬
    }

    if (key_up && ((gpio_get_pin(KEY_SW3) == 0) || (gpio_get_pin(KEY_SW2) == 0))) // ��ⰴ���Ƿ��²��� key_up Ϊ��
    {
        delay_ms(5); // ��ʱ 5 ���룬��ֹ��������

        key_up = 0; // ���� key_up Ϊ��������״̬

        if (gpio_get_pin(KEY_SW3) == 0)
        {
            return 1; // ���KEY_SW33 ���������£��򷵻� 1
        }
        else if (gpio_get_pin(KEY_SW2) == 0)
        {
            return 2; // ���KEY_SW22 ���������£��򷵻� 2
        }
    }
    else if ((gpio_get_pin(KEY_SW3) != 0) && (gpio_get_pin(KEY_SW2) != 0)) // �������������δ������
    {
        key_up = 1; // ���� key_up Ϊ��������״̬
    }


 	return 0;//
}


