#define R1 2
#define R2 3
#define L1 4
#define L2 5

void setup() {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);

  // Enable both motors through the L298N
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);

  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}

void loop() {
  // Motors continue running forward
}