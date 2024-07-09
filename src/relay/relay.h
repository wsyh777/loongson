/*
 * relay.h
 *
 * created: 2024/2/21
 *  author: 
 */

#ifndef _RELAY_H
#define _RELAY_H

#ifdef __cplusplus
extern "C" {
#endif

void Relay_Init(int gpio); 
int  Relay_check(int gpio); 
void Relay_set(int gpio,int val); 

#ifdef __cplusplus
}
#endif

#endif // _RELAY_H




