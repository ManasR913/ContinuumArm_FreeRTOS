// motor_control.cpp
#include "motor_control.h"
#include <Arduino.h>

extern const int pwmChannelsA[3];
extern const int pwmChannelsB[3];

void zmotorTask(void *pvParameters) {
  Motor* m = (Motor*)pvParameters;
  TickType_t lastWakeTime = xTaskGetTickCount();
  const TickType_t frequency = 10 / portTICK_PERIOD_MS;
  while (true) {
    unsigned long startMicros = micros();

    // --- Simulate control logic ---
    m->error = m->targetPosition - m->currentPosition;
    m->pwmOutput = constrain(m->error * 10.0f, -255, 255); // Simple proportional control

    int duty = abs((int)m->pwmOutput);
    bool direction = m->pwmOutput >= 0;

    // --- Drive motor with PWM in selected direction ---
    if (direction) {
      ledcWrite(pwmChannelsA[m->id], duty);
      ledcWrite(pwmChannelsB[m->id], 0);
    } else {
      ledcWrite(pwmChannelsA[m->id], 0);
      ledcWrite(pwmChannelsB[m->id], duty);
    }

    unsigned long duration = micros() - startMicros;
    Serial.print("[Motor");
    Serial.print(m->id);
    Serial.print("] PWM: ");
    Serial.print(duty);
    Serial.print(" Dir: ");
    Serial.print(direction ? "FWD" : "REV");
    Serial.print(" | Exec time (us): ");
    Serial.println(duration);

    vTaskDelayUntil(&lastWakeTime, frequency);
  }
}

