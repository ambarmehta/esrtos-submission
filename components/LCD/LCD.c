#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include <math.h>
#include <string.h>

void lcd_init();
void lcd_cmd(char);
void lcd_data(char);
void lcd_decode(char);
void lcd_string(char *);

int lcd_pins[11] = {12, 13, 14, 18, 25, 26, 27, 32, 33, 5, 19};
char msg[] = "Hello world!";

void lcd_display()
{
    while (1)
    {
        lcd_init();
    }
}
void lcd_init()
{
    for (int i = 0; i < 11; i++)
    {
        esp_rom_gpio_pad_select_gpio(lcd_pins[i]);
        gpio_set_direction(lcd_pins[i], GPIO_MODE_OUTPUT);
    }
    lcd_cmd(0x38);   
    lcd_cmd(0x01);   
    lcd_cmd(0x0E);   
    lcd_cmd(0x80);  
    lcd_string(msg); 
}
void lcd_decode(char info)
{
    char temp;
    for (int i = 0; i < 8; i++)
    {
        temp = pow(2, i);
        gpio_set_level(lcd_pins[i], (info & temp));
    }
}

void lcd_cmd(char cmd)
{
    lcd_decode(cmd);
    gpio_set_level(lcd_pins[8], 0);
    gpio_set_level(lcd_pins[9], 0);
    gpio_set_level(lcd_pins[10], 1);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(lcd_pins[10], 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void lcd_data(char data)
{
    lcd_decode(data);
    gpio_set_level(lcd_pins[8], 1);
    gpio_set_level(lcd_pins[9], 0);
    gpio_set_level(lcd_pins[10], 1);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(lcd_pins[10], 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void lcd_string(char *p)
{
    while (*p != '\0')
    {
        lcd_data(*p);
        p = p + 1;
    }
}