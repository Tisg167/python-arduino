#include <Servo.h>
#include <Adafruit_MotorShield.h>

const int SERVO1_PIN = 9;
const int SERVO2_PIN = 10;
const int BAUD = 9600;
const int OUTPUT_LENGTH = 256;
const int DATA_LENGTH = 128;
const char PID[] = {"SERVO"};

// Global Vars
Servo servoA;
Servo servoB;
char output_buffer[OUTPUT_LENGTH];
char data_buffer[DATA_LENGTH];
int valA = 90;
int valB = 90;

void setup() {
  Serial.begin(BAUD);
  servoA.attach(SERVO1_PIN);
  servoB.attach(SERVO2_PIN);
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    int i = Serial.parseInt();
    switch (c) {
      case 'A':
        valA = i; break;
      case 'B':
        valB = i; break;
      default:
        break;
    }
  }
  while (Serial.available() > 0) {
    Serial.read();
  }
  servoB.write(valB);
  servoA.write(valA);
  sprintf(data_buffer, "{'servoA':%d,'servoB':%d}", valA, valB);
  int chksum = checksum(data_buffer);
  sprintf(output_buffer, "{'pid':'%s','data':%s,'chksum':%d}", PID, data_buffer,chksum);
  Serial.println(output_buffer);
}

int checksum(char* buf) {
  int sum = 0;
  for (int i = 0; i < DATA_LENGTH; i++) {
    sum = sum + buf[i];
  }
  return sum % 256;
}

