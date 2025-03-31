// motor_control.h

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H


struct Motor {
  int id;
  float targetPosition;
  float currentPosition;
  float error;
  float pwmOutput;
  // Add PID gains, encoder readings, etc., as needed
};

// Task declaration
void motorTask(void *pvParameters);

#endif // MOTOR_CONTROL_H
