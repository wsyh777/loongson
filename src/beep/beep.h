/*
 * beep.h
 *
 * created: 2024/2/21
 *  author: 
 */

#ifndef _BEEP_H
#define _BEEP_H

#ifdef __cplusplus
extern "C" {
#endif

void BEEP_Init(int gpio);
int  BEEP_check(int gpio);
void BEEP_set(int gpio,int val);

#ifdef __cplusplus
}
#endif

#endif // _BEEP_H


