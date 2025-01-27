/*
 * beep.c
 *
 * created: 2024/2/21
 *  author: 
 */

#include "ls1x_gpio.h"
#include "beep.h"

/*******************************************************************
* ������ : BEEP_Init
* ����   : ��ʼ��������
* ����   : gpio:���
* ���   : ��
* ����   : ��
* ע��   :
********************************************************************/

void BEEP_Init(int gpio)
{
    gpio_set_direction(gpio, GPIO_Mode_Out);  //Ҳ����  1������� 0������
}


/*******************************************************************
* ������ : BEEP_check
* ����   : ��÷�����״̬
* ����   : gpio:���
* ���   : ��
* ����   : 1���أ� 0����
* ע��   :
********************************************************************/
int BEEP_check(int gpio)
{
    return gpio_get_pin(gpio);
}

/*******************************************************************
* ������ : BEEP_set
* ����   : ���÷�����״̬
* ����   : gpio:���     val�� 1 ��  0 ��
* ���   : ��
* ����   :
* ע��   : 
*!! ���������Ϊ���߼���˫��ȡ�����������!! ��������һ��ִֵ�������߼��ǲ�������������ȷ�����շ��صĽ���� 0 �� 1��
********************************************************************/
void BEEP_set(int gpio,int val)
{ 
    gpio_write_pin(gpio, !!val);
}







