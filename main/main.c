#include <stdbool.h>
#include <stdint.h>

#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu6050.h"

#define I2C_MASTER_PORT I2C_NUM_0
#define I2C_MASTER_SDA_GPIO 8
#define I2C_MASTER_SCL_GPIO 9
#define I2C_MASTER_FREQUENCY_HZ 100000
#define SAMPLE_PERIOD_MS 1000

static const char *TAG = "mpu6050_app";

static esp_err_t i2c_master_init(void) {
  const i2c_config_t config = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = I2C_MASTER_SDA_GPIO,
      .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_io_num = I2C_MASTER_SCL_GPIO,
      .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = I2C_MASTER_FREQUENCY_HZ,
      .clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL,
  };

  esp_err_t error = i2c_param_config(I2C_MASTER_PORT, &config);
  if (error != ESP_OK) {
    return error;
  }

  return i2c_driver_install(I2C_MASTER_PORT, config.mode, 0, 0, 0);
}

void app_main(void) {
  ESP_LOGI(TAG, "Iniciando barramento I2C: SDA=GPIO%d, SCL=GPIO%d",
           I2C_MASTER_SDA_GPIO, I2C_MASTER_SCL_GPIO);
  ESP_ERROR_CHECK(i2c_master_init());

  mpu6050_handle_t sensor =
      mpu6050_create(I2C_MASTER_PORT, MPU6050_I2C_ADDRESS);
  if (sensor == NULL) {
    ESP_LOGE(TAG, "Nao foi possivel criar o sensor MPU6050");
    return;
  }

  ESP_ERROR_CHECK(mpu6050_config(sensor, ACCE_FS_4G, GYRO_FS_500DPS));
  ESP_ERROR_CHECK(mpu6050_wake_up(sensor));

  uint8_t device_id = 0;
  ESP_ERROR_CHECK(mpu6050_get_deviceid(sensor, &device_id));
  if (device_id != MPU6050_WHO_AM_I_VAL) {
    ESP_LOGE(TAG, "MPU6050 inesperado: WHO_AM_I=0x%02X", device_id);
    mpu6050_delete(sensor);
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_PORT));
    return;
  }

  ESP_LOGI(TAG, "MPU6050 iniciado corretamente (WHO_AM_I=0x%02X)", device_id);

  while (true) {
    mpu6050_acce_value_t acceleration = {0};
    mpu6050_gyro_value_t gyroscope = {0};
    mpu6050_temp_value_t temperature = {0};

    esp_err_t error = mpu6050_get_acce(sensor, &acceleration);
    if (error == ESP_OK) {
      error = mpu6050_get_gyro(sensor, &gyroscope);
    }
    if (error == ESP_OK) {
      error = mpu6050_get_temp(sensor, &temperature);
    }

    if (error == ESP_OK) {
      ESP_LOGI(TAG,
               "ACC[g] x=%6.2f y=%6.2f z=%6.2f | GYRO[dps] x=%7.2f y=%7.2f "
               "z=%7.2f | TEMP[C] %5.2f",
               acceleration.acce_x, acceleration.acce_y, acceleration.acce_z,
               gyroscope.gyro_x, gyroscope.gyro_y, gyroscope.gyro_z,
               temperature.temp);
    } else {
      ESP_LOGE(TAG, "Falha ao ler o MPU6050: %s", esp_err_to_name(error));
    }

    vTaskDelay(pdMS_TO_TICKS(SAMPLE_PERIOD_MS));
  }
}
