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

void DHT11_IO_OUT (void);    //温湿度模块输出函数
void DHT11_IO_IN (void);     //温湿度模块输入函数
void DHT11_RST (void);       //DHT11端口复位，发出起始信号（IO发送）
uint8_t DHT11_Check(void);	    //等待DHT11回应，返回1:未检测到DHT11，返回0:成功（IO接收）
uint8_t DHT11_Read_Bit(void);     //从DHT11读取一个位     //返回值：1/0
uint8_t DHT11_Read_Byte(void);    //从DHT11读取一个字节   //返回值：读到的数据

uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi);  //从DHT11读取一次数据 //temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败

#ifdef __cplusplus
}
#endif

#endif // _DHT11_H


