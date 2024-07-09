#include "ls1x.h"
#include "dht11.h"
#include "ls1x_gpio.h"
#include "ls1x_latimer.h"
#include "fan.h"

void fan_control(void)
{
    while(1)
    {
        gpio_write_pin(INA,0);
        gpio_write_pin(INB,1);
        delay_ms(1000);
    }
}
