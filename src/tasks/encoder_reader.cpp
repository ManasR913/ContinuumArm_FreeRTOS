// encoder_reader.cpp
#include "encoder_reader.h"
#include <Arduino.h>

void encoderReaderTask(void *pvParameters) {
  while (true) {
    // TODO: Read encoder values, update shared state
    Serial.println("[Encoder] Reading encoder data");
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}