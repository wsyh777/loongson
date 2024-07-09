#include "ls1x.h"
#include "Config.h"
#include "oled.h"
#include "ls1x_spi.h"
#include "ls1x_latimer.h"
#include "ls1x_printf.h"
#include "ls1x_gpio.h"
#include "dht11.h"
#include "key.h"
#include "beep.h"
#include "mq2.h"
// #include "fan.h"
#include "PCF8563.h"
#include "ls1c102_i2c.h"

int main(int arg, char *args[])
{
    gpio_pin_remap(GPIO_PIN_4, GPIO_FUNC_MAIN); // 引脚复用4：scl
    gpio_pin_remap(GPIO_PIN_5, GPIO_FUNC_MAIN); // 引脚复用5：sda
    I2C_InitTypeDef I2C_InitStruct0;
    I2C_StructInit(&I2C_InitStruct0);
    I2C_Init(I2C, &I2C_InitStruct0);

    uint8_t temp;
    uint8_t humi;
    uint8_t idht11;
    uint8_t TEthreshold = 38;
    uint8_t HUthreshold = 15;
    uint8_t sec, min, hour, day, month;
    uint16_t year;
    int data;
    int judge;
    int INA = 25;
    int INB = 26;

    /* 字符串数组变量 */
    char strTemp[16];
    char strHumi[16];
    char strAdc[20];
    char time_str[20];
    char time_str2[20];
    Spi_Init(SPI_DIV_2);
    OLED_Init(); // 初始化 OLED 模块
    MQ2_Init(7); // 初始化MQ2

    OLED_Clear(); // OLED 清屏
    delay_ms(100);
    PCF8563_Init();
    gpio_write_pin(INA, 1);
    gpio_write_pin(INB, 1);

    // 循环以持续更新显示
    // while (1)
    // {
    //     // 获取当前时间
    //     PCF8563_GetTime(&sec, &min, &hour, &day, &month, &year);

    //     // 格式化时间字符串

    //     sprintf(time_str, "Date:%02d-%02d-%04d", year, month, day);
    //     sprintf(time_str2, "Time:%02d:%02d:%02d", hour, min, sec);
    //     OLED_ShowString(0, 16, time_str);
    //     OLED_ShowString(0, 32, time_str2);
    // }
    // return 0;
    //}

    while (1)
    {
        idht11 = DHT11_Read_Data(&temp, &humi);
        data = MQ2_Measure(7);

        // switch (KEY_Scan(0)) // 扫描按键
        // {
        // case 1: // 如果KEY_SW3 按键被按下
        // {
            sprintf(strTemp, "%d", temp);
            sprintf(strHumi, "%d", humi);
            printf("temp:%d\r\n", temp);
            printf("humi:%d\r\n", humi);

            /* 显示温度 */
            OLED_ClearRow(2);
            OLED_ShowCHinese(20, 20, 4);
            OLED_ShowCHinese(36, 20, 5);
            OLED_ShowChar(52, 20, ':', 16);
            OLED_ShowString(68, 20, strTemp);
            OLED_ShowCHinese(84, 20, 7);

            /* 显示湿度 */
            OLED_ClearRow(3);
            OLED_ShowCHinese(20, 36, 6);
            OLED_ShowCHinese(36, 36, 5);
            OLED_ShowChar(52, 36, ':', 16);
            OLED_ShowString(68, 36, strHumi);
            OLED_ShowChar(84, 36, '%', 16);
            // OLED_ClearRow(2);
            // OLED_ShowString(0, 16, "BEEP:ON");

            /* 把adc数据格式化到字符串数组变量中 */
            sprintf(strAdc, "%d", data);

            /* 显示adc数据 */
            // OLED_ClearRow(2);
            OLED_ShowString(20, 1, "MQ2_ADC:");
            OLED_ShowString(84, 1, strAdc);
            // LED_ClearRow(3);
        // }
        // break;

        // case 2: // 如果KEY_SW2 按键被按下 显示时间
        // {
        //     OLED_Clear();
        //     /* 把adc数据格式化到字符串数组变量中 */
        //     sprintf(strAdc, "%d", data);

        //     /* 显示adc数据 */
        //     OLED_ClearRow(2);
        //     OLED_ShowString(13, 16, "happy birthday");
        //     // OLED_ShowString(84, 16, strAdc);
        //     OLED_ClearRow(3);
        //     // OLED_ShowString(0, 16, "BEEP:OFF");
        // }
        // break;
        // default:
        //     break;
        // }

        if (data > 100)
        {
            gpio_write_pin(24, 0);
        }
        else
        {
            gpio_write_pin(24, 1);
        }

        // if (humi > HUthreshold)
        // {
        //     // 洒水
        //
        // }
        // 按下sw2显示烟雾浓度

        if (temp >= TEthreshold)
        {
            gpio_write_pin(INB, 0);
        }
    }

    delay_ms(60);

    return 0;
}
