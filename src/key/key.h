/*
 * key.h
 *
 * created: 2024/3/1
 *  author:
 */

#ifndef _KEY_H
#define _KEY_H

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_SW3    22
#define KEY_SW2    63

void KEY_Init(void);
unsigned char KEY_Scan(unsigned char mode);

#ifdef __cplusplus
}
#endif

#endif // _KEY_H


