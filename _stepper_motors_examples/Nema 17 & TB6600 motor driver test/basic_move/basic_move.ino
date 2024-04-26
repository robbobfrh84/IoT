/* 
👀 🚨! WARNING: delay() / delayMicroseconds() need to corrispond to 
Motor Driver MicroStep Settings. To short a delay will not work with big steps.
*/

int cnt = 0;
int reverse_step_mark = 1; // 200, 800, 3200 // ms
int delay_reverse_length = 1000; // ms
int dir = 1;

int stepPin = 2;
int dirPin = 3;
int enablePin = 4;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);


  digitalWrite(dirPin, dir);

  digitalWrite(stepPin, LOW);
  digitalWrite(stepPin, HIGH);
  delay(1000);
}

void loop() {
  cnt++;
  digitalWrite(stepPin, LOW);
  digitalWrite(stepPin, HIGH);

  /* 200 per rotation (Big Steps!)
     !👀 Driver Step Setting: Microstep = 1, Pulse/rev = 200 - ON, ON, OFF */
  // delay(5);

  /* 800 Steps per rotation
     !👀 Driver Step Setting: Microstep = 4, Pulse/rev = 800 - ON, OFF, OFF */
  delayMicroseconds(500);

  /* 3200 Steps per rotation
     !👀 Driver Step Setting: Microstep = 16, Pulse/rev = 3200 - OFF, OFF, ON */
  // delayMicroseconds(100);

  if (cnt > reverse_step_mark) {
    cnt = 0;
    dir = dir == 1 ? 0 : 1;
    digitalWrite(dirPin, dir);
    delay(delay_reverse_length);
  }
}
