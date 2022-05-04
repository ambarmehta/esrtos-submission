#include <stdio.h>
#include "blink_led.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define PIN 2

static const char *TAG = "LED STATUS";


void blink(void)
{ 
    gpio_pad_select_gpio(PIN);
    esp_log_level_set("LOG", ESP_LOG_INFO);
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);

    bool isON = false;

    while (true)
    {
        gpio_set_level(PIN, isON);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, " LED %s!", isON == true ? "ON" : "OFF");
        isON = !isON;
    }
}
