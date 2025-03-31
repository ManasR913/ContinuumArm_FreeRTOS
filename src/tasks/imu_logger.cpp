// imu_logger.cpp
#include "imu_logger.h"
#include <Arduino.h>

void imuLoggerTask(void *pvParameters) {
  TickType_t lastWakeTime = xTaskGetTickCount();
  const TickType_t frequency = 50 / portTICK_PERIOD_MS;

  while (true) {
    Serial.println("[IMU] Logging IMU data");
    // TODO: Read and log IMU data

    vTaskDelayUntil(&lastWakeTime, frequency);
  }
}
