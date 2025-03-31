// feedback_loop.cpp
// Reserved for future implementation of sensor fusion or advanced feedback control.
// Currently unused — encoder-based closed-loop control is handled in motor_control.cpp.
#include "feedback_loop.h"
#include <Arduino.h>

void feedbackLoopTask(void *pvParameters) {
  TickType_t lastWakeTime = xTaskGetTickCount();
  const TickType_t frequency = 100 / portTICK_PERIOD_MS;

  while (true) {
    // Placeholder: run only every 100 ms
    vTaskDelayUntil(&lastWakeTime, frequency);
  }
}