#define triggerPin1 12
#define echoPin1 11
#define triggerPin2 2
#define echoPin2 3

#define ledStatus 13

#define A 10
#define B 9
#define C 8
#define D 7
#define E 6
#define F 5
#define G 4

int currentPeople = 0;
int timeoutCounter = 0;
String sequence = "";

int maxPeople = 9;

int firstDistance1 = 0;
int firstDistance2 = 0;
int distance1 = 0;
int distance2 = 0;

void number0() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void number1() {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void number2() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void number3() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void number4() {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void number5() {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void number6() {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void number7() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void number8() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void number9() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void numberF() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void measureDistance1() {
  unsigned long duration1;

  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = int(duration1 / 2 / 29.412);
}

void measureDistance2() {
  unsigned long duration2;

  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = int(duration2 / 2 / 29.412);
}

void comparisonData() {
  if (distance1 < firstDistance1 && sequence.charAt(0) != '1') {
    sequence += "1";
  } else if (distance2 < firstDistance2 && sequence.charAt(0) != '2') {
    sequence += "2";
  }

  if (sequence.equals("12")) {
    currentPeople++;
    sequence = "";
    delay(500);
  } else if (sequence.equals("21") && currentPeople > 0) {
    currentPeople--;
    sequence = "";
    delay(500);
  }

  if (sequence.length() > 2 || sequence.equals("11") || sequence.equals("22") || timeoutCounter > 200) {
    sequence = "";
  }

  if (sequence.length() == 1) {  //
    timeoutCounter++;
  } else {
    timeoutCounter = 0;
  }
}

void displayData() {
  if (currentPeople == 0) {
    number0();
    delay(500);
  }
  if (currentPeople == 1) {
    number1();
    delay(500);
  }
  if (currentPeople == 2) {
    number2();
    delay(500);
  }
  if (currentPeople == 3) {
    number3();
    delay(500);
  }
  if (currentPeople == 4) {
    number4();
    delay(500);
  }
  if (currentPeople == 5) {
    number5();
    delay(500);
  }
  if (currentPeople == 6) {
    number6();
    delay(500);
  }
  if (currentPeople == 7) {
    number7();
    delay(500);
  }
  if (currentPeople == 8) {
    number8();
    delay(500);
  }
  if (currentPeople == 9) {
    number9();
    delay(500);
  }
  if (currentPeople > 9) {
    numberF();
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledStatus, OUTPUT);

  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  void measureDistance1();
  void measureDistance2();

  firstDistance1 = distance1;
  firstDistance2 = distance2;
}

void loop() {
  measureDistance1();
  measureDistance2();
  delay(200);
  comparisonData();
  displayData();
}
