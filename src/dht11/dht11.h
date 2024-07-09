/*
 * dht11.h
 *
 * created: 2024/2/21
 *  author: 
 */

#ifndef _DHT11_H
#define _DHT11_H

#define  DHT11_IO   23

#ifdef __cplusplus
extern "C" {
#endif

void DHT11_IO_OUT (void);    //��ʪ��ģ���������
void DHT11_IO_IN (void);     //��ʪ��ģ�����뺯��
void DHT11_RST (void);       //DHT11�˿ڸ�λ��������ʼ�źţ�IO���ͣ�
uint8_t DHT11_Check(void);	    //�ȴ�DHT11��Ӧ������1:δ��⵽DHT11������0:�ɹ���IO���գ�
uint8_t DHT11_Read_Bit(void);     //��DHT11��ȡһ��λ     //����ֵ��1/0
uint8_t DHT11_Read_Byte(void);    //��DHT11��ȡһ���ֽ�   //����ֵ������������

uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi);  //��DHT11��ȡһ������ //temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��

#ifdef __cplusplus
}
#endif

#endif // _DHT11_H


