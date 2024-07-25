const int P1_DOWN = 2;
const int P1_UP = 3;
const int P2_DOWN = 11;
const int P2_UP = 8; 

int p1DownState = 0;
int p1UpState = 0;
int p2DownState = 0;
int p2UpState = 0;

void setup() {
  Serial.begin(9600);

  pinMode(P1_DOWN, INPUT);
  pinMode(P1_UP, INPUT);
  pinMode(P2_DOWN, INPUT);
  pinMode(P2_UP, INPUT);
}

void loop() {
  p1DownState = digitalRead(P1_DOWN);
  p1UpState = digitalRead(P1_UP);
  p2DownState = digitalRead(P2_DOWN);
  p2UpState = digitalRead(P2_UP);

  // send data to the serial port which can be read
  // in through the C++ controller code
  
  if (p1DownState == HIGH) {
    Serial.println(1);
  }

  if (p1UpState == HIGH) {
    Serial.println(2);
  }

  if (p2DownState == HIGH) {
    Serial.println(3);
  }

  if (p2UpState == HIGH) {
    Serial.println(4);
  }
}
