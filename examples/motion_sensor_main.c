#define LOGNAME "Moses"

#include <hk.h>
#include <hk_fascade.h>

#include <esp_system.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <nvs_flash.h>
#include <esp_event.h>

#define IO_PIR 21
SemaphoreHandle_t guard = NULL;
bool app_sth_is_moving = false;
void *app_chr;
bool initialized = false;

void on_identify()
{
    ESP_LOGI(LOGNAME, "Identify");
}

esp_err_t on_write(hk_mem *request)
{
    app_sth_is_moving = *(bool *)request->ptr;
    ESP_LOGD(LOGNAME, "Write: %d\n", app_sth_is_moving);
    return ESP_OK;
}

esp_err_t on_read(hk_mem *response)
{
    ESP_LOGD(LOGNAME, "Read: %d", app_sth_is_moving);
    hk_mem_append_buffer(response, &app_sth_is_moving, sizeof(bool));
    return ESP_OK;
}

void IRAM_ATTR on_isr(void *arg)
{
    xSemaphoreGiveFromISR(guard, NULL);
}

void motion_handler(void *args_ptr)
{
    const TickType_t delay = 50;
    for (;;)
    {
        if (!app_chr)
        {
            vTaskDelay(delay);
        }
        else if (xSemaphoreTake(guard, delay) == pdTRUE)
        {
            bool sth_was_moving = app_sth_is_moving;
            app_sth_is_moving = gpio_get_level(IO_PIR);

            if (sth_was_moving != app_sth_is_moving)
            {
                ESP_LOGI(LOGNAME, "Something is moving: %d", app_sth_is_moving);
                hk_notify(app_chr);
            }
        }
    }
}

void app_main()
{
    ESP_LOGI(LOGNAME, "SDK version:%s\n", esp_get_idf_version());
    ESP_LOGI(LOGNAME, "Starting\n");

    // init homekit
    hk_setup_add_motion_sensor(
        "MotionSensor", "HomekitTest", "A motion sensor.", "0000001", "0.1.0",
        on_identify, on_read, &app_chr);
    // hk_reset();
    hk_init("Moses", HK_CAT_SENSOR, "111-22-222");

    // init worker task
    vSemaphoreCreateBinary(guard);
    xTaskCreate(motion_handler, "motion_handler", 3072, NULL, 10, NULL);

    // init io config
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.pin_bit_mask = 1ULL << IO_PIR;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 0;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);

    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(IO_PIR, on_isr, (void *)IO_PIR));
    initialized = true;
}