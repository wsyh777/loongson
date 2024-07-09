/*
 * mq2.h
 *
 * created: 2024/2/21
 *  author: 
 */

#ifndef _MQ2_H
#define _MQ2_H

#ifdef __cplusplus
extern "C" {
#endif

void MQ2_Init(int ch);
unsigned short  MQ2_Measure(int gpio);
void MQ2_ADC_close(int ch);

#ifdef __cplusplus
}
#endif

#endif // _MQ2_H

