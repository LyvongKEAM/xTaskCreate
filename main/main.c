#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "dht11.h"
#include "bmp180.h"

static const char * TAG1 = "LDR";
static const char * TAG2 = "DHT11";
static const char * TAG3 = "BMP180";

#define LDR_Pin (ADC1_CHANNEL_0)  // GPIO1
#define ADC_SIZE (ADC_WIDTH_BIT_12)

#define DHT11_Pin (GPIO_NUM_15)
#define REFERENCE_PPRESSURE 101325l
#define I2C_pin_SDA 8
#define I2C_pin_SCL 9

void LDR_task(void *pvParameter)
{
    adc1_config_width(ADC_SIZE);
    adc1_config_channel_atten(LDR_Pin, ADC_ATTEN_DB_11);
    while (1)
    {
        int adc_value = adc1_get_raw(LDR_Pin);

        ESP_LOGI(TAG1, "light intensity: %d", adc_value);
        vTaskDelay(1000/portTICK_PERIOD_MS);  //Delay for 1000ms
    }
    vTaskDelete(NULL);
}


void DHT11(void *pvParameter)
{
    DHT11_init(DHT11_Pin);
    while (1)
    {

        ESP_LOGI(TAG2, "Temperature is %d \n", DHT11_read().temperature);
        ESP_LOGI(TAG2, "Humidity is %d\n", DHT11_read().humidity);

        vTaskDelay(2000/portTICK_PERIOD_MS);  //Delay for 2000ms
    }
    vTaskDelete(NULL);
    
}

void bmp180_task(void *pvParameter)
{
    esp_err_t err = bmp180_init(I2C_pin_SDA,I2C_pin_SCL);
        if(err != ESP_OK){
            ESP_LOGE(TAG3, "Init bmp180 failed = %d", err);
            vTaskDelete(NULL);
            return;
        }
    while (1)
    {
        uint32_t pressure;
        float altitude;
        float temperature;

        err = bmp180_read_pressure(&pressure);
        if(err != ESP_OK){
            ESP_LOGE(TAG3, "Reading of pressure from BMP180 failed, err = %d", err);
        }
    
        err = bmp180_read_altitude(REFERENCE_PPRESSURE, &altitude);
        if(err != ESP_OK){
            ESP_LOGE(TAG3, "Reading of altitude from BMP180 failed, err = %d", err);
        }

        err = bmp180_read_temperature(&temperature);
        if(err != ESP_OK){
            ESP_LOGE(TAG3, "Reading of temperature from BMP180 failed, err = %d", err);
        }

        ESP_LOGI(TAG3, "Pressure %lu Pa, Altitute %.2f m, Temperature : %.1f C", pressure, altitude, temperature);
        vTaskDelay(3000/portTICK_PERIOD_MS);    //Delay for 3000ms
    }
    
}

void app_main(void)
{
    xTaskCreate(&LDR_task, "LDR Task", 2048, NULL, 5, NULL); 
    xTaskCreate(&DHT11, "DHT11 Task", 2048, NULL, 4, NULL);
    xTaskCreate(&bmp180_task, "BMP180 Task", 4096, NULL, 3, NULL);
}


