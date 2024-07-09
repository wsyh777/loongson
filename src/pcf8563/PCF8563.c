#include "ls1c102_i2c.h"
#include "PCF8563.h"

// 定义I2C设备，根据实际硬件定义

void PCF8563_Init(void)
{
        I2C_InitTypeDef I2C_InitStruct;
        I2C_StructInit(&I2C_InitStruct);
        I2C_InitStruct.I2C_ClockSpeed = 100000;    // 设置I2C时钟速度为100kHz
        I2C_InitStruct.I2C_Mode = I2C_Mode_Master; // 设置为I2C主模式
        I2C_InitStruct.I2C_OwnAddress1 = 0x00;     // 设置I2C拥有的地址
        I2C_Init(I2C, &I2C_InitStruct);            // 使用宏定义的设备初始化I2C
}

void PCF8563_SetTime(uint8_t sec, uint8_t min, uint8_t hour,
                     uint8_t day, uint8_t month, uint16_t year)
{
        // 确保I2C总线空闲
        I2C_BUSY(I2C);

        // 发送写入地址
        I2C_Send7bitAddress(I2C, PCF8563_ADDR_W, I2C_Direction_Transmitter);

        // 发送秒、分、时、日、月、年数据
        I2C_SendData(I2C, sec);
        I2C_SendData(I2C, min);
        I2C_SendData(I2C, hour);
        I2C_SendData(I2C, day);
        I2C_SendData(I2C, month);
        I2C_SendData(I2C, (uint8_t)(year % 100)); // PCF8563只存储年份的后两位

        // 生成停止条件
        I2C_GenerateSTOP(I2C, ENABLE);
        I2C_wait(I2C);
}

void PCF8563_GetTime(uint8_t *sec, uint8_t *min, uint8_t *hour, uint8_t *day, uint8_t *month, uint16_t *year)
{
        // 确保I2C总线空闲
        //I2C_BUSY(I2C);

        // 发送写入地址，准备发送命令
        I2C_Send7bitAddress(I2C, PCF8563_ADDR_W, I2C_Direction_Transmitter);
        I2C_wait(I2C);

        // 发送秒寄存器地址
        I2C_SendData(I2C, PCF8563_REG_SC);
        I2C_wait(I2C);

        // 生成停止条件，然后发送读取地址
        I2C_GenerateSTOP(I2C, ENABLE);
        I2C_wait(I2C);
        I2C_GenerateSTART(I2C, ENABLE);
        I2C_wait(I2C);
        I2C_Send7bitAddress(I2C, PCF8563_ADDR_R, I2C_Direction_Receiver);
        I2C_wait(I2C);

        // 接收秒、分、时、日、月、年数据
        *sec = I2C_ReadRegister(I2C, I2C_Register_DR);
        *min = I2C_ReadRegister(I2C, I2C_Register_DR);
        *hour = I2C_ReadRegister(I2C, I2C_Register_DR);
        *day = I2C_ReadRegister(I2C, I2C_Register_DR);
        *month = I2C_ReadRegister(I2C, I2C_Register_DR);
        *year = I2C_ReadRegister(I2C, I2C_Register_DR) + 2000; // 根据PCF8563年份范围调整

        // 清除中断标志
        I2C_ClearIT(I2C);
}