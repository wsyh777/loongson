
/*
 * pcf8563.h
 *
 * created: 2024/7/7
 *  author: 
 */

#ifndef _PCF8563_H
#define _PCF8563_H

#ifdef __cplusplus
extern "C" {
#endif

#define I2C            ((I2C_TypeDef *)I2C_BASE)

#define PCF8563_ADDR_W           0xA2    // PCF8563的7位I2C地址加写入操作位
#define PCF8563_ADDR_R           0xA3    // PCF8563的7位I2C地址加读取操作位

// PCF8563寄存器定义
#define PCF8563_REG_SC           0x00    // 控制寄存器
#define PCF8563_REG_MIN          0x01    // 分寄存器
#define PCF8563_REG_HOUR         0x02    // 时寄存器
#define PCF8563_REG_DAY          0x03    // 日寄存器
#define PCF8563_REG_WEEKDAY      0x04    // 星期寄存器
#define PCF8563_REG_MONTH        0x05    // 月寄存器
#define PCF8563_REG_YEAR         0x06    // 年寄存器

void PCF8563_Init(void);
void PCF8563_GetTime(uint8_t *sec, uint8_t *min, uint8_t *hour,uint8_t *day, uint8_t *month, uint16_t *year);


#ifdef __cplusplus
}
#endif

#endif // _pcf8563