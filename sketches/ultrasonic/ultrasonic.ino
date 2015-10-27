/*
ultrasonic.ino
*/

// Contants
const int BAUD = 9600;
const int PIN_IN = 12;
const int PIN_OUT = 13;
const int LENGTH = 128;

// Variables
char output_buffer[LENGTH];
int var;

void setup(void) {
  Serial.begin(BAUD);
  pinMode(PIN_OUT, OUTPUT);
  pinMode(PIN_IN, INPUT);
}

void loop(void) {
  var = get_distance();
  sprintf(output_buffer, "{'pid':'%s', 'data':%d}", "PID", var);
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
