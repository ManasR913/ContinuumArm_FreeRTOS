// main.cpp
#include <Arduino.h>
#include "motor_control.h"
#include "imu_logger.h"
#include "feedback_loop.h"
#include <Preferences.h>

Motor motors[3] = {
  {0, 0.0f, 0.0f, 0.0f, 0.0f},
  {1, 0.0f, 0.0f, 0.0f, 0.0f},
  {2, 0.0f, 0.0f, 0.0f, 0.0f}
};

const int motorPinsA[3] = {18, 16, 25};  // First pin for each motor (PWM A)
const int motorPinsB[3] = {18, 17, 26}; // Second pin for each motor (PWM B)
const int pwmChannelsA[3] = {0, 1, 2};
const int pwmChannelsB[3] = {3, 4, 5};

const int encoderPinsA[3] = {34, 36, 32}; // enca 
const int encoderPinsB[3] = {35, 39, 33}; // encb

volatile long encoderCounts[3] = {0, 0, 0};

void IRAM_ATTR encoderISR(bool isA, int motorId) {
  bool a = digitalRead(encoderPinsA[motorId]);
  bool b = digitalRead(encoderPinsB[motorId]);
  if (isA) {
    encoderCounts[motorId] += (a == b) ? 1 : -1;
  } else {
    encoderCounts[motorId] += (a != b) ? 1 : -1;
  }
}

void setup() {
  Serial.begin(115200);

  // Setup PWM for each motor direction
  for (int i = 0; i < 3; i++) {
    ledcSetup(pwmChannelsA[i], 5000, 8);
    ledcAttachPin(motorPinsA[i], pwmChannelsA[i]);

    ledcSetup(pwmChannelsB[i], 5000, 8);
    ledcAttachPin(motorPinsB[i], pwmChannelsB[i]);
  }

  // Create individual Motor Tasks
  xTaskCreate(motorTask, "Motor1", 2048, &motors[0], 3, NULL);
  xTaskCreate(motorTask, "Motor2", 2048, &motors[1], 3, NULL);
  xTaskCreate(motorTask, "Motor3", 2048, &motors[2], 3, NULL);

  // Create IMU Logger Task
  xTaskCreate(
    imuLoggerTask,
    "IMU Logger",
    2048,
    NULL,
    1,
    NULL
  );

  // Create Feedback Loop Task (Placeholder)
  xTaskCreate(
    feedbackLoopTask,
    "Feedback Loop",
    2048,
    NULL,
    1,
    NULL
  );
}
