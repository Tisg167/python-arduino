/*
ultrasonic.ino
*/

// Contants
const int BAUD = 9600;
const int PIN_IN = 12;
const int PIN_OUT = 13;
const int IO_PIN = 2;
const int OUTPUT_LENGTH = 256;
const int DATA_LENGTH = 128;

// Variables
char output_buffer[OUTPUT_LENGTH];
char data_buffer[DATA_LENGTH];

void setup(void) {
  Serial.begin(BAUD);
  pinMode(PIN_OUT, OUTPUT);
  pinMode(PIN_IN, INPUT);
  pinMode(IO_PIN, INPUT);
}

void loop(void) {
  int dist = get_distance();
  int pin = digitalRead(IO_PIN);
  sprintf(data_buffer, "{'dist':%d,'pin':%d}", dist, pin);
  int chksum = checksum(data_buffer);
  sprintf(output_buffer, "{'pid':'%s','data':%s,'chksum':%d}", "PID", data_buffer,chksum);
  Serial.println(output_buffer);
}

int get_distance(void) {
 long duration;
 long distance;
 digitalWrite(PIN_OUT, LOW); 
 delayMicroseconds(2); 
 digitalWrite(PIN_OUT, HIGH);
 delayMicroseconds(10); 
 digitalWrite(PIN_OUT, LOW);
 duration = pulseIn(PIN_IN, HIGH);
 distance = duration/58.2; //Calculate the distance (in cm) based on the speed of sound.
 return int(distance);
}

int checksum(char* buf) {
  int sum = 0;
  for (int i = 0; i < DATA_LENGTH; i++) {
    sum = sum + buf[i];
  }
  return sum % 256;
}
