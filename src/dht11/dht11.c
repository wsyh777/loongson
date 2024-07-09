/*
 * dht11.c
 *
 * created: 2024/2/21
 *  author: 
 */



/*
 * DHT11.c
 *
 * created: 2023/11/29
 *  author:
 */
#include "ls1x.h"
#include "dht11.h"
#include "ls1x_gpio.h"
#include "ls1x_latimer.h"

//io = 1������� io = 0������
void DHT11_IO_OUT (void)  //��ʪ��ģ���������
{
    gpio_set_direction(DHT11_IO, GPIO_Mode_Out);
}

void DHT11_IO_IN (void)  //��ʪ��ģ�����뺯��
{
    gpio_set_direction(DHT11_IO, GPIO_Mode_In);
}

void DHT11_RST (void)
{
    //DHT11�˿ڸ�λ��������ʼ�źţ�IO���ͣ�
    DHT11_IO_OUT();							//�˿�Ϊ���
    gpio_write_pin(DHT11_IO, 0);	            //ʹ����Ϊ�͵�ƽ   1���ߵ�ƽ��0���͵�ƽ
    delay_ms(30);					//��������18ms
    gpio_write_pin(DHT11_IO, 1);		        //ʹ����Ϊ�ߵ�ƽ
    delay_us(30);					    //��������20~40us
}

uint8_t DHT11_Check(void)//�ȴ�DHT11��Ӧ��0Ϊ�ɹ���Ӧ
{
    //�ȴ�DHT11��Ӧ������1:δ��⵽DHT11������0:�ɹ���IO���գ�
    uint8_t retry=0;			//������ʱ����
    DHT11_IO_IN();		        //IO������״̬

    //���DHT11������������Ϊ�ߵ�ƽ���� retry С��100���� retry ��1������ʱ1΢�룬
    //�ظ��������ֱ�� retry ���ڵ���100 ����DHT11�������������ɵ͵�ƽ��
    while ((gpio_get_pin(DHT11_IO)== 0) && retry<105)	//DHT11������40~80us
    {
        retry++;
        delay_us(1);
    }
    if(retry>=105) return 1;            //��� retry ���ڵ���100����ʾ���ʧ�ܣ�����1�����򣬽� retry ����Ϊ0��
    else retry=0;
    //���DHT11������������Ϊ�͵�ƽ���� retry С��100���� retry ��1������ʱ1΢�룬�ظ��������ֱ�� retry ���ڵ���100 ����DHT11�������������ɸߵ�ƽ��
    while ((gpio_get_pin(DHT11_IO)== 1) && retry<105)  //DHT11���ͺ���ٴ�����40~80us
    {
        retry++;
        delay_us(1);
    }
    if(retry>=105)return 1;           //��� retry ���ڵ���100����ʾ���ʧ�ܣ�����1�����򣬷���0����ʾ���ɹ���
    return 0;
}
//��DHT11��ȡһ��λ
//����ֵ��1/0
uint8_t DHT11_Read_Bit(void)
{
    uint8_t retry = 0;
    while((gpio_get_pin(DHT11_IO)== 1) && retry < 105) //�ȴ���Ϊ�͵�ƽ
    {
        retry++;
        delay_us(1);
    }
    retry = 0;
    while((gpio_get_pin(DHT11_IO)== 0) && retry < 105) //�ȴ���ߵ�ƽ
    {
        retry++;
        delay_us(1);
    }
    delay_us(30); 					    //�ȴ�30us
    if(gpio_get_pin(DHT11_IO)== 1)       //�����жϸߵ͵�ƽ��������1��0
        return 1;
    else
        return 0;
}

//��DHT11��ȡһ���ֽ�
//����ֵ������������
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i, dat;
    dat = 0;
    for (i = 0; i < 8; i++)
    {
        dat <<= 1;					//���������,dat����1λ
        dat |= DHT11_Read_Bit();	//"|"��ʾ��λ�����
    }
    return dat;
}

//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~105��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5];
    uint8_t i;

    DHT11_RST();						//DHT11�˿ڸ�λ��������ʼ�ź�
    if (DHT11_Check() == 0)				//�ȴ�DHT11��Ӧ��0Ϊ�ɹ���Ӧ
    {
        for(i = 0; i < 5; i++) 			//��ȡ40λ����
        {
            buf[i] = DHT11_Read_Byte();	//��������
        }
        if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])	//����У��
        {
            *humi = buf[0];				//��ʪ��ֵ����ָ��humi
            *temp = buf[2];				//���¶�ֵ����ָ��temp
        }
        return 0;
    }

    return 1;
}





